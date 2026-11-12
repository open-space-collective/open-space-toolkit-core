fn main() {
    let manifest_dir = std::path::PathBuf::from(std::env::var("CARGO_MANIFEST_DIR").unwrap());
    let deps = ostk_build::deps_prefix();
    let built = ostk_build::Library::new("core", "OpenSpaceToolkitCore")
        .cmake_define("FETCHCONTENT_SOURCE_DIR_MAGIC_ENUM", deps.join("src/magic_enum"))
        // Included by core's public headers.
        .export_include(deps.join("src/magic_enum/include"))
        // C++ headers for ostk-* shims (include/ostk_rs).
        .export_include(manifest_dir.join("include"))
        // Core links last, so this covers Boost for every crate.
        .link_static([
            "yaml-cpp",
            "boost_log_setup",
            "boost_log",
            "boost_thread",
            "boost_filesystem",
            "boost_url",
            "boost_date_time",
            "boost_chrono",
            "boost_atomic",
        ])
        .link_system(["stdc++", "dl", "pthread", "m"])
        .build();

    let mut bridge = cxx_build::bridges(["src/container/mod.rs", "src/test_support.rs"]);
    bridge.file("src/container/shim.cpp").file("src/test_support.cpp");
    built.configure(&mut bridge);
    bridge.compile("ostk-core-bridge");
    built.link();
    for f in ["src/container", "src/test_support.rs", "src/test_support.h", "src/test_support.cpp"] {
        println!("cargo:rerun-if-changed={f}");
    }
    println!("cargo:rerun-if-changed=include");
}
