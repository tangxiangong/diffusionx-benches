use diffusionx::simulation::{continuous::Bm, prelude::*};

const N: usize = 10_000;
const TAU: f64 = 0.01;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let now = std::time::Instant::now();
    let bm = Bm::default();
    let msds = (100..=1000)
        .step_by(100)
        .map(|t| bm.msd(t as f64, N, TAU).unwrap())
        .collect::<Vec<_>>();
    let elapsed = now.elapsed().as_secs_f64();
    println!("MSDs: {msds:#?}, elapsed time: {elapsed:.3} s");
    Ok(())
}
