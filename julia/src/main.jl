include("stable.jl")
stable_rands(0.7, 1.0, 1.0, 0.0, 10)

N = 10_000_000;

elapsed = @elapsed stable_rands(0.7, 0.0, 1.0, 0.0, N);

println("Time taken by Julia: $elapsed s")

