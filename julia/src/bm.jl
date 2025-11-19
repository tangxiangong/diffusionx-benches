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

function displacement(bm::Bm, T::Float64, τ::Float64=0.01)
    n = ceil(Int, T / τ)
    sigma = sqrt(2 * bm.D * τ)
    noise = randn(n - 1) .* sigma
    delta_x = sum(noise)
    last_step = T - (n - 1) * τ
    delta_x += randn() * sqrt(2 * bm.D * last_step)
    delta_x
end


function msd(bm::Bm, T::Float64, N::Int=10_000, τ::Float64=0.01)::Float64
    displacements = ThreadsX.map(1:N) do _
        displacement(bm, T, τ)
    end
    sum(displacements .^ 2) / N
end

bm = StandardBm()
T = collect(100.0:100.0:1000.0)
@time m = [msd(bm, t) for t in T]
println(m)