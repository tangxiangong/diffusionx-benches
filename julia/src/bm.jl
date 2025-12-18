using Random
using ThreadsX

include("utils.jl")

struct Bm{T<:AbstractFloat}
    x₀::T
    D::T
    function Bm{T}(x₀::T=0.0, D::T=0.5) where T<:AbstractFloat
        new{T}(x₀, D)
    end
end

function simulate(bm::Bm{T}, duration::T, τ::T=0.01) where T<:AbstractFloat
    σ = sqrt(2 * bm.D * τ)
    t = collect(zero(T):τ:duration)
    x = Vector{T}(undef, length(t))
    n = length(t) - 1
    ξ = randn(T, n - 1)
    xₙ = bm.x₀
    @inbounds for i in 1:(n-1)
        xₙ += ξ[i] * σ
        x[i] = xₙ
    end
    last_step = duration - (n - 1) * τ
    noise = randn(T) * sqrt(2 * bm.D * last_step)
    xₙ += noise
    x[end] = xₙ
    t, x
end

function displacement(bm::Bm{T}, duration::T, τ::T=0.01) where T<:AbstractFloat
    n = ceil(Int, duration / τ)
    σ = sqrt(2 * bm.D * τ)
    ξ = randn(T, n - 1)
    Δx = zero(T)
    @inbounds for i in 1:(n-1)
        Δx += ξ[i] * σ
    end
    last_step = duration - (n - 1) * τ
    Δx += randn(T) * sqrt(2 * bm.D * last_step)
    Δx
end


function msd(bm::Bm{T}, duration::T, N::Int=10_000, τ::T=0.01) where T<:AbstractFloat
    displacements = ThreadsX.map(1:N) do _
        displacement(bm, duration, τ)
    end
    sum(displacements .^ 2) / N
end

bm = Bm{Float64}()

simulate(bm, 1.0, 0.01)
msd(bm, 1.0, 100, 0.01)

bench("Brownian motion simulation", () -> simulate(bm, 100.0, 0.01))
bench("Brownian motion msd", () -> msd(bm, 100.0, 10_000, 0.01))
