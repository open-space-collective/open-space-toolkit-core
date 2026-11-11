//! Test-only bridge exercising `include/ostk_rs/core/`.

#[cxx::bridge(namespace = "ostk_rs::core::test_support")]
pub(crate) mod ffi {
    unsafe extern "C++" {
        include!("ostk-core/src/test_support.h");

        fn path_round_trip(path: &str) -> Result<String>;
        fn file_round_trip(path: &str) -> Result<String>;
        fn directory_round_trip(path: &str) -> Result<String>;
        fn f64_array_round_trip(values: &[f64]) -> Vec<f64>;
        fn string_array_lengths(values: &[String]) -> Vec<usize>;
    }
}

#[cfg(test)]
mod tests {
    use super::ffi;

    #[test]
    fn paths_round_trip_through_ostk() {
        for p in ["/tmp/a/b.txt", "/tmp/dir", "relative/file.txt"] {
            assert_eq!(ffi::path_round_trip(p).unwrap(), p);
        }
        assert_eq!(ffi::file_round_trip("/tmp/a/b.txt").unwrap(), "/tmp/a/b.txt");
        assert_eq!(ffi::directory_round_trip("/tmp/dir").unwrap(), "/tmp/dir");
    }

    #[test]
    fn value_arrays_round_trip() {
        assert_eq!(ffi::f64_array_round_trip(&[1.0, -2.5, 3.0]), vec![1.0, -2.5, 3.0]);
        assert_eq!(ffi::f64_array_round_trip(&[]), Vec::<f64>::new());
    }

    #[test]
    fn arrays_convert_elements() {
        let strings = vec!["a".to_string(), "bcd".to_string(), String::new()];
        assert_eq!(ffi::string_array_lengths(&strings), vec![1, 3, 0]);
    }
}
