from math import ceil, sqrt

import numpy as np
from numba import (  # pyright: ignore [reportMissingTypeStubs]
    njit,  # pyright: ignore [reportUnknownVariableType]
    prange,
)


class PyBm:
    def __init__(self, starting_point: float = 0.0, diffusivity: float = 0.5):
        self.starting_point: float = starting_point
        self.diffusivity: float = diffusivity

    def simulate(self, duration: float, time_step: float = 0.01):
        num_steps = ceil(duration / time_step)
        sigma = sqrt(2 * self.diffusivity * time_step)
        noises = np.random.standard_normal(num_steps) * sigma
        last_step = duration - (num_steps - 1) * time_step
        noises[-1] = noises[-1] * sqrt(last_step / time_step)
        noises = np.insert(noises, 0, self.starting_point)
        t = np.arange(0, duration, time_step)
        if t[-1] != duration:
            t = np.append(t, duration)
        x = np.cumsum(noises)
        return t, x

    def displacement(self, duration: float, time_step: float = 0.01):
        num_steps = ceil(duration / time_step)
        sigma = sqrt(2 * self.diffusivity * time_step)
        noises = np.random.standard_normal(num_steps) * sigma
        last_step = duration - (num_steps - 1) * time_step
        noises[-1] = noises[-1] * sqrt(last_step / time_step)
        return np.sum(noises)

    def msd(
        self,
        duration: float,
        N: int = 10_000,
        tau: float = 0.01,
    ):
        return _msd(
            duration,
            self.diffusivity,
            N,
            tau,
        )


@njit(parallel=True)  # pyright: ignore [reportUntypedFunctionDecorator]
def _msd(
    duration: float,
    diffusivity: float = 0.5,
    N: int = 10_000,
    time_step: float = 0.01,
):
    total = 0.0
    for _ in prange(N):
        num_steps = ceil(duration / time_step)
        sigma = sqrt(2 * diffusivity * time_step)
        noises = np.random.standard_normal(num_steps) * sigma
        last_step = duration - (num_steps - 1) * time_step
        noises[-1] = noises[-1] * sqrt(last_step / time_step)
        total += np.sum(noises) ** 2
    return total / N


if __name__ == "__main__":
    from utils import bench

    bench_size = 100

    duration = 100.0
    time_step = 0.01
    particles = 10000

    py_bm = PyBm()

    def py_simulate():
        return py_bm.simulate(duration, time_step)

    def py_msd():
        return py_bm.msd(duration, particles, time_step)

    bench("Brownian motion simulation", py_simulate, bench_size)
    bench("Brownian motion msd", py_msd, bench_size)

    from diffusionx.simulation import Bm

    rs_bm = Bm()

    def rs_simulate():
        return rs_bm.simulate(duration, time_step)

    def rs_msd():
        return rs_bm.msd(duration, particles=particles, time_step=time_step)

    bench("Brownian motion simulation (PyO3)", rs_simulate, bench_size)
    bench("Brownian motion msd (PyO3)", rs_msd, bench_size)
