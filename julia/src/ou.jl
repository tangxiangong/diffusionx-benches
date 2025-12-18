using Random
using ThreadsX

struct OU{T<:AbstractFloat}
    x₀::T
    θ::T
    σ::T
    function OU{T}(θ::T=one(T), σ::T=one(T), x₀::T=zero(T)) where T<:AbstractFloat
        new{T}(x₀, θ, σ)
    end
end

function simulate(eq::OU{T}, duration::T, τ::T=0.01) where T<:AbstractFloat
    t = collect(0:τ:duration)
    n = length(t) - 1
    x = zeros(n + 1)
    noise = randn(T, n - 1)
    x[1] = eq.x₀
    scale = eq.σ * sqrt(τ)
    @inbounds for i in 1:n-1
        dw = scale * noise[i]
        x[i+1] = x[i] - eq.θ * x[i] * τ + dw
    end
    last_step = duration - (n - 1) * τ
    dw = eq.σ * sqrt(last_step) * randn(T)
    x[end] = x[end-1] - eq.θ * x[end-1] * last_step + dw
    t, x
end

function displacement(eq::OU{T}, duration::T, τ::T=0.01) where T<:AbstractFloat
    n = ceil(Int, duration / τ)
    current_x = eq.x₀
    current_t = zero(T)
    noise = randn(T, n - 1)
    scale = eq.σ * sqrt(τ)
    @inbounds for i in 1:n-1
        dw = scale * noise[i]
        current_x += -eq.θ * current_x * τ + dw
        current_t += τ
    end
    last_step = duration - current_t
    dw = eq.σ * sqrt(last_step) * randn(T)
    current_x += -eq.θ * current_x * last_step + dw
    current_x - eq.x₀
end


function msd(eq::OU{T}, duration::T, N::Int=10_000, τ::T=0.01) where T<:AbstractFloat
    displacements = ThreadsX.map(1:N) do _
        displacement(eq, duration, τ)^2
    end
    return sum(displacements) / N
end

include("utils.jl")

ou = OU{Float64}()

simulate(ou, 1.0, 0.01)
msd(ou, 1.0, 100, 0.01)

bench("Ornstein-Uhlenbeck simulation", () -> simulate(ou, 100.0, 0.01))
bench("Ornstein-Uhlenbeck msd", () -> msd(ou, 100.0, 10_000, 0.01))
