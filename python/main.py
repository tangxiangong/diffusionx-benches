from scipy.stats import levy_stable
import time
import diffusionx

def main():
    stable = levy_stable(alpha=0.7, beta = 0.0, loc = 0.0, scale = 1.0)
    start_time = time.time()
    _ = stable.rvs(size=10_000_000)
    elapsed = time.time() - start_time
    print(f"Time taken by Python: {elapsed} s")


if __name__ == "__main__":
    main()
