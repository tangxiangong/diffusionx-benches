use diffusionx::simulation::{continuous::Levy, prelude::*};

const N: usize = 10_000;
const TAU: f64 = 0.01;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let sp = Levy::new(0.0, 0.7)?;
    let now = std::time::Instant::now();
    let means = (100..=1000)
        .step_by(100)
        .map(|t| sp.mean(t as f64, N, TAU).unwrap())
        .collect::<Vec<_>>();
    let elapsed = now.elapsed().as_secs_f64();
    println!("Means: {means:#?}, elapsed time: {elapsed:.3} s");
    Ok(())
}
