from scipy.stats import levy_stable
import time
import numpy as np
import sys
import os
from diffusionx.random import stable_rand, uniform as rand, randn


def timeit(func, bench_size):
    result = np.zeros(bench_size)
    for i in range(bench_size):
        result[i] = time.time()
        func()
        result[i] = time.time() - result[i]
    return result


def show_timeit(result, log_file):
    mean_v = np.mean(result)
    stddev_v = np.std(result)
    min_v = np.min(result)
    max_v = np.max(result)
    print(
        f"mean: {mean_v:.4f}, stddev: {stddev_v:.4f}, min: {min_v:.4f}, max: {max_v:.4f}",
        file=log_file,
    )
    print(file=log_file)


def numpy_bench(N, bench_size, log_file):
    print("===============Python (NumPy / SciPy)==================", file=log_file)
    print(file=log_file)

    def uniform():
        return np.random.rand(N)

    print("-------------uniform random number sampling------------", file=log_file)
    show_timeit(timeit(uniform, bench_size), log_file)

    def normal():
        return np.random.randn(N)

    print("-------------normal random number sampling-------------", file=log_file)
    show_timeit(timeit(normal, bench_size), log_file)

    print("-------------stable random number sampling-------------", file=log_file)

    def stable():
        dist = levy_stable(alpha=0.7, beta=0.0, loc=0.0, scale=1.0)
        return dist.rvs(size=N)

    show_timeit(timeit(stable, bench_size), log_file)

    print("=======================================================", file=log_file)
    print(file=log_file)


def pyo3_bench(N, bench_size, log_file):
    print("===============Python (Rust by PyO3)===================", file=log_file)
    print(file=log_file)

    def uniform():
        return rand(N)

    print("-------------uniform random number sampling------------", file=log_file)
    show_timeit(timeit(uniform, bench_size), log_file)

    def normal():
        return randn(N)

    print("-------------normal random number sampling-------------", file=log_file)
    show_timeit(timeit(normal, bench_size), log_file)

    print("-------------stable random number sampling-------------", file=log_file)

    def stable():
        return stable_rand(0.7, 0.0, size=N)

    show_timeit(timeit(stable, bench_size), log_file)

    print("=======================================================", file=log_file)
    print(file=log_file)


def main():
    bench_size = 20 if len(sys.argv) <= 1 else int(sys.argv[1])
    N = 10_000_000

    # 创建log目录（如果不存在）
    os.makedirs("../log", exist_ok=True)

    # 打开日志文件
    with open("../log/python.log", "w") as log_file:
        print(f"bench size: {bench_size}, length of random vectors: {N}", file=log_file)
        print("unit: second", file=log_file)
        print(file=log_file)

        pyo3_bench(N, bench_size, log_file)
        numpy_bench(N, bench_size, log_file)


if __name__ == "__main__":
    main()
