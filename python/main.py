from scipy.stats import levy_stable
import time
from diffusionx.random import stable_rand

def main():
    start_time = time.time()
    _ = stable_rand(0.7, 0.0, size=100_000_000)
    elapsed = time.time() - start_time
    print(f"Time taken by Python/Rust(PyO3 Wrapped): {elapsed} s")

    stable = levy_stable(alpha=0.7, beta = 0.0, loc = 0.0, scale = 1.0)
    start_time = time.time()
    _ = stable.rvs(size=100_000_000)
    elapsed = time.time() - start_time
    print(f"Time taken by Python/SciPy: {elapsed} s")


if __name__ == "__main__":
    main()
