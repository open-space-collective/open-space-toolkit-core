//! `build.rs` support for the `ostk-*` crates: builds the crate's OSTK library
//! statically with CMake and links it.
//!
//! ```ignore
//! let built = ostk_build::Library::new("physics", "OpenSpaceToolkitPhysics")
//!     .cmake_define("SOFA_ROOT_DIR", ostk_build::deps_prefix())
//!     .link_static(["sofa_c"])
//!     .build();
//! built.configure(&mut bridge); // compile the cxx shim with matching flags
//! built.link();
//! ```
//!
//! Lower OSTK libraries are found through the `links` metadata of the crate's
//! direct `ostk-*` dependencies. Third-party archives come from
//! `OSTK_DEPS_PREFIX[_<target>]`; cross builds use `CMAKE_TOOLCHAIN_FILE_<target>`.

use std::collections::BTreeMap;
use std::env;
use std::ffi::OsString;
use std::path::PathBuf;

/// Flags every TU including OSTK headers must share with the libraries (ODR).
pub const CXX_FLAGS: &[&str] = &[
    "-std=c++17", // forced on aarch64 upstream; used everywhere for identical headers
    "-DNDEBUG",   // the libraries are Release builds
];

/// Third-party dependency prefix for the current target.
pub fn deps_prefix() -> PathBuf {
    let prefix = target_env("OSTK_DEPS_PREFIX").map(PathBuf::from).unwrap_or_else(|| {
        panic!(
            "OSTK_DEPS_PREFIX_{t} (or OSTK_DEPS_PREFIX) is not set: point it at a prefix of static, \
             PIC third-party dependencies for {t}",
            t = env::var("TARGET").unwrap().replace('-', "_")
        )
    });
    assert!(
        prefix.join("include/boost/version.hpp").exists(),
        "{} does not look like an OSTK dependency prefix (no Boost headers)",
        prefix.display()
    );
    prefix
}

/// The OSTK library of the repository containing the calling crate.
#[derive(Debug, Clone)]
pub struct Library {
    name: String,
    package: String,
    cmake_defines: Vec<(String, OsString)>,
    static_libs: Vec<String>,
    system_libs: Vec<String>,
    exported_includes: Vec<PathBuf>,
}

impl Library {
    /// `Library::new("core", "OpenSpaceToolkitCore")` builds `libopen-space-toolkit-core.a`.
    pub fn new(name: &str, package: &str) -> Self {
        Self {
            name: name.to_string(),
            package: package.to_string(),
            cmake_defines: Vec::new(),
            static_libs: Vec::new(),
            system_libs: Vec::new(),
            exported_includes: Vec::new(),
        }
    }

    /// Extra CMake cache entry, e.g. a find-module hint.
    pub fn cmake_define(mut self, key: &str, value: impl Into<OsString>) -> Self {
        self.cmake_defines.push((key.to_string(), value.into()));
        self
    }

    /// Third-party archives this library needs, in link order.
    pub fn link_static<I: IntoIterator<Item = S>, S: Into<String>>(mut self, libs: I) -> Self {
        self.static_libs.extend(libs.into_iter().map(Into::into));
        self
    }

    /// System libraries this library needs.
    pub fn link_system<I: IntoIterator<Item = S>, S: Into<String>>(mut self, libs: I) -> Self {
        self.system_libs.extend(libs.into_iter().map(Into::into));
        self
    }

    /// Include directory that consumers also need (e.g. one its headers include).
    pub fn export_include(mut self, dir: impl Into<PathBuf>) -> Self {
        self.exported_includes.push(dir.into());
        self
    }

    fn lib_name(&self) -> String {
        format!("open-space-toolkit-{}", self.name)
    }

    /// Builds and installs the library into `OUT_DIR`.
    pub fn build(self) -> Built {
        let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
        let repo = manifest_dir.join("../..").canonicalize().expect("repository root");
        let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
        let deps = deps_prefix();
        let lower = lower_libraries();

        // Every ostk-* crate builds on core.
        if self.name != "core" && !lower.iter().any(|l| l.package == "OpenSpaceToolkitCore") {
            panic!("ostk-core metadata not found: add ostk-core as a dependency of this crate");
        }

        let mut extra_includes: Vec<PathBuf> = lower.iter().flat_map(|l| l.include_dirs.iter().cloned()).collect();
        extra_includes.extend(self.exported_includes.iter().cloned());
        extra_includes.push(deps.join("include"));
        dedup(&mut extra_includes);

        let mut cfg = cmake::Config::new(&repo);
        cfg.profile("Release")
            .define("BUILD_SHARED_LIBRARY", "OFF")
            .define("BUILD_STATIC_LIBRARY", "ON")
            .define("BUILD_UNIT_TESTS", "OFF")
            .define("BUILD_PYTHON_BINDINGS", "OFF")
            .define("BUILD_WITH_DEBUG_SYMBOLS", "OFF")
            .define("BUILD_WITH_BOOST_STACKTRACE", "OFF")
            .define("BUILD_WITH_CXX_17", "ON")
            .define("CMAKE_POSITION_INDEPENDENT_CODE", "ON")
            // Keep outputs out of the source tree (OSTK defaults to <repo>/lib).
            .define("CMAKE_ARCHIVE_OUTPUT_DIRECTORY", out_dir.join("out/lib"))
            .define("CMAKE_LIBRARY_OUTPUT_DIRECTORY", out_dir.join("out/lib"))
            .define("CMAKE_RUNTIME_OUTPUT_DIRECTORY", out_dir.join("out/bin"))
            .define("CMAKE_PREFIX_PATH", &deps)
            .define("Boost_ROOT", &deps)
            // OSTK libraries rely on /usr/local/include for their dependencies' headers.
            .define("CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES", join_cmake_list(&extra_includes));
        // Point CMake at lower libraries directly: a cross toolchain re-roots find_*.
        for l in &lower {
            let pkg = &l.package;
            cfg.define(format!("{pkg}_DIR"), l.root.join("lib/cmake").join(pkg))
                .define(format!("{pkg}_ROOT_DIR"), &l.root)
                .define(format!("{pkg}_INCLUDE_DIR"), l.root.join("include"))
                .define(format!("{pkg}_LIBRARY"), l.root.join(format!("lib/lib{}.a", l.lib)));
        }
        for (key, value) in &self.cmake_defines {
            cfg.define(key, value);
        }
        let install = cfg.build();

        for p in ["CMakeLists.txt", "include", "src", "tools/cmake"] {
            println!("cargo:rerun-if-changed={}", repo.join(p).display());
        }

        // Metadata for crates built on this one (DEP_OSTK_<NAME>_*).
        let mut published = vec![install.join("include")];
        published.extend(self.exported_includes.iter().cloned());
        println!("cargo:root={}", install.display());
        println!("cargo:package={}", self.package);
        println!("cargo:lib={}", self.lib_name());
        println!("cargo:include_dirs={}", env::join_paths(&published).unwrap().to_str().expect("UTF-8 path"));

        let mut include_dirs = vec![install.join("include")];
        include_dirs.extend(extra_includes);
        Built {
            include_dirs,
            cxx_flags: CXX_FLAGS.iter().map(|s| s.to_string()).collect(),
            lib: self,
            install,
            deps,
        }
    }
}

/// A built OSTK library.
#[derive(Debug, Clone)]
pub struct Built {
    pub include_dirs: Vec<PathBuf>,
    pub cxx_flags: Vec<String>,
    lib: Library,
    install: PathBuf,
    deps: PathBuf,
}

impl Built {
    /// Configures a shim's `cc::Build` with the libraries' headers and flags.
    pub fn configure(&self, build: &mut cc::Build) {
        for dir in &self.include_dirs {
            build.flag("-isystem").flag(dir.to_str().expect("UTF-8 include path"));
        }
        for flag in &self.cxx_flags {
            build.flag(flag);
        }
    }

    /// Emits the link line. Call after compiling the shim, which must link first.
    pub fn link(&self) {
        println!("cargo:rustc-link-search=native={}", self.install.join("lib").display());
        println!("cargo:rustc-link-search=native={}", self.deps.join("lib").display());
        println!("cargo:rustc-link-lib=static:-bundle={}", self.lib.lib_name());
        for a in &self.lib.static_libs {
            println!("cargo:rustc-link-lib=static:-bundle={a}");
        }
        for s in &self.lib.system_libs {
            println!("cargo:rustc-link-lib=dylib={s}");
        }
    }
}

/// An OSTK library published by a direct dependency.
struct LowerLibrary {
    package: String,
    lib: String,
    root: PathBuf,
    include_dirs: Vec<PathBuf>,
}

/// The OSTK libraries published by direct dependencies (`DEP_OSTK_*`), sorted.
fn lower_libraries() -> Vec<LowerLibrary> {
    let vars: BTreeMap<String, String> = env::vars().filter(|(k, _)| k.starts_with("DEP_OSTK_")).collect();
    vars.iter()
        .filter_map(|(k, v)| k.strip_suffix("_PACKAGE").map(|key| (key, v)))
        .map(|(key, package)| {
            let get = |field: &str| {
                vars.get(&format!("{key}_{field}"))
                    .unwrap_or_else(|| panic!("{key}_{field} not set (crate publishing {package} is out of date?)"))
            };
            LowerLibrary {
                package: package.clone(),
                lib: get("LIB").clone(),
                root: PathBuf::from(get("ROOT")),
                include_dirs: env::split_paths(get("INCLUDE_DIRS")).collect(),
            }
        })
        .collect()
}

fn target_env(key: &str) -> Option<String> {
    let target = env::var("TARGET").unwrap().replace('-', "_");
    for k in [format!("{key}_{target}"), key.to_string()] {
        println!("cargo:rerun-if-env-changed={k}");
        if let Ok(v) = env::var(&k) {
            return Some(v);
        }
    }
    None
}

fn dedup(dirs: &mut Vec<PathBuf>) {
    let mut seen = std::collections::HashSet::new();
    dirs.retain(|d| seen.insert(d.clone()));
}

fn join_cmake_list(dirs: &[PathBuf]) -> String {
    dirs.iter().map(|d| d.display().to_string()).collect::<Vec<_>>().join(";")
}

