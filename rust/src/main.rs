use diffusionx::random::normal;
use diffusionx::random::{stable, uniform};
use std::env;
use std::fs::{File, create_dir_all};
use std::io::Write;
use std::time;

fn timeit<F>(func: F, bench_size: usize) -> Vec<f64>
where
    F: Fn() -> i32,
{
    (0..bench_size)
        .map(|_| {
            let start_time = time::Instant::now();
            let _ = func();
            start_time.elapsed().as_secs_f64()
        })
        .collect()
}

fn show_timeit(result: Vec<f64>, log_file: &mut File) {
    let mean = result.iter().sum::<f64>() / result.len() as f64;
    let stddev =
        (result.iter().map(|x| (x - mean).powi(2)).sum::<f64>() / result.len() as f64).sqrt();
    let min = *result
        .iter()
        .reduce(|a, b| if *a < *b { a } else { b })
        .expect("Failed to find minimum value");
    let max = *result
        .iter()
        .reduce(|a, b| if *a > *b { a } else { b })
        .expect("Failed to find maximum value");
    writeln!(
        log_file,
        "mean: {mean:.4}, stddev: {stddev:.4}, min: {min:.4}, max: {max:.4}"
    )
    .expect("Failed to write to log file");
    writeln!(log_file).expect("Failed to write to log file");
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let bench_size = args.get(1).map(|s| s.parse().unwrap_or(20)).unwrap_or(20);

    let len = 10_000_000;

    // 创建log目录（如果不存在）
    create_dir_all("../log").expect("Failed to create log directory");

    // 打开日志文件
    let mut log_file = File::create("../log/rust.log").expect("Failed to create log file");

    writeln!(
        log_file,
        "=========================Rust=========================="
    )
    .expect("Failed to write to log file");
    writeln!(log_file).expect("Failed to write to log file");

    writeln!(
        log_file,
        "bench size: {}, length of random vectors: {}",
        bench_size, len
    )
    .expect("Failed to write to log file");
    writeln!(log_file, "unit: second").expect("Failed to write to log file");
    writeln!(log_file).expect("Failed to write to log file");

    let uniform = || {
        let _rnds = uniform::range_rands(0.0..1.0, len).unwrap();
        0
    };
    writeln!(
        log_file,
        "------------uniform random number sampling------------"
    )
    .expect("Failed to write to log file");
    show_timeit(timeit(uniform, bench_size), &mut log_file);

    let normal = || {
        let _rands = normal::standard_rands::<f64>(len);
        0
    };
    writeln!(
        log_file,
        "------------normal random number sampling------------"
    )
    .expect("Failed to write to log file");
    show_timeit(timeit(normal, bench_size), &mut log_file);

    let stable = || {
        let _rnds = stable::sym_standard_rands(0.7, len).unwrap();
        0
    };
    writeln!(
        log_file,
        "------------stable random number sampling------------"
    )
    .expect("Failed to write to log file");
    show_timeit(timeit(stable, bench_size), &mut log_file);

    writeln!(
        log_file,
        "======================================================="
    )
    .expect("Failed to write to log file");
    writeln!(log_file).expect("Failed to write to log file");
}
