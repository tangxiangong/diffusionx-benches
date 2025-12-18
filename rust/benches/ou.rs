use criterion::{Criterion, criterion_group, criterion_main};
use diffusionx::simulation::{continuous::OrnsteinUhlenbeck, prelude::*};
use std::hint::black_box;

fn criterion_benchmark(_c: &mut Criterion) {
    let ou = OrnsteinUhlenbeck::default();
    let duration = 100.0;
    let time_step = 0.01;
    let particles = 10000;
    let mut criterion = Criterion::default().sample_size(10);
    criterion.bench_function("Ornstein-Uhlenbeck process simulation", |b| {
        b.iter(|| {
            let _ = ou.simulate(black_box(duration), black_box(time_step));
        })
    });
    criterion.bench_function("Ornstein-Uhlenbeck process msd", |b| {
        b.iter(|| {
            let _ = ou.msd(
                black_box(duration),
                black_box(particles),
                black_box(time_step),
            );
        })
    });
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);
