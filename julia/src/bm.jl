using Random
using ThreadsX

struct Bm
    x₀::Float64
    D::Float64
    function Bm(x₀::Float64=0.0, D::Float64=1.0)
        new(x₀, D)
    end
end
StandardBm() = Bm(0.0, 0.5)

function simulate(bm::Bm, T::Float64, τ::Float64=0.01)
    sigma = sqrt(2 * bm.D * τ)
    t = collect(0:τ:T)
    n = length(t) - 1
    noise = randn(n) .* sigma
    x = cumsum(vcat(bm.x₀, noise))
    t, x
end

function msd(bm::Bm, T::Float64, N::Int=10_000, τ::Float64=0.01)::Float64
    displacements = ThreadsX.map(1:N) do _
        _, x = simulate(bm, T, τ)
        (x[end] - x[1])^2
    end
    return sum(displacements) / N
end

bm = StandardBm()
T = collect(100.0:100.0:1000.0)
@time m = [msd(bm, t) for t in T]
println(m)