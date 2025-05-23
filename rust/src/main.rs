use std::time;
use diffusionx::random::stable::sym_standard_rands;

fn main() {
    let start_time = time::Instant::now();
    let _rnds = sym_standard_rands(0.7, 100_000_000).unwrap();
    let elapsed = start_time.elapsed().as_secs_f64();
    println!("Time taken by Rust: {elapsed} s");
}
