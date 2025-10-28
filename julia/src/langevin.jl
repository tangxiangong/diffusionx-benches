using Random
using ThreadsX

struct Langevin{F,G}
    x₀::Float64
    f::F
    g::G
    function Langevin(f::F, g::G; x₀::Float64=0.0) where {F,G}
        new{F,G}(x₀, f, g)
    end
end

function simulate(eq::Langevin, T::Float64, τ::Float64=0.01)
    t = collect(0:τ:T)
    n = length(t) - 1
    x = zeros(n + 1)
    noise = randn(n)
    x[1] = eq.x₀
    @inbounds for i in 1:n
        dw = eq.g(x[i], t[i+1]) * sqrt(τ) * noise[i]
        x[i+1] = x[i] + eq.f(x[i], t[i+1]) * τ + dw
    end
    t, x
end

function msd(eq::Langevin, T::Float64, N::Int=10_000, τ::Float64=0.01)::Float64
    displacements = ThreadsX.map(1:N) do _
        _, x = simulate(eq, T, τ)
        (x[end] - x[1])^2
    end
    return sum(displacements) / N
end

eq = Langevin((x, t) -> -x, (x, t) -> 1.0)
T = collect(100.0:100.0:1000.0)
@time m = [msd(eq, t) for t in T]
println(m)
