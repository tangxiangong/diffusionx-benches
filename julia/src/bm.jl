using Random
using Base.Threads

struct Bm
    x₀::Float64
    D::Float64
    function Bm(x₀::Float64=0.0, D::Float64=1.0)
        new(x₀, D)
    end
end
function StandardBm()
    return Bm(0.0, 0.5)
end

function simulate(bm::Bm, T::Float64, τ::Float64=0.01)
    sigma = sqrt(2 * bm.D * τ)
    t = collect(0:τ:T)
    n = length(t) - 1
    noise = randn(n) .* sigma
    x = cumsum(vcat(bm.x₀, noise))
    t, x
end


function msd(bm::Bm, T::Float64, N::Int=10_000, τ::Float64=0.01)::Float64
    val = 0.0
    @threads for _ in 1:N
        _, x = simulate(bm, T, τ)
        val += (x[end] - x[1])^2
    end
    val / N
end

bm = StandardBm()
T = collect(100.0:100.0:1000.0)
@time m = [msd(bm, t) for t in T]
println(m)