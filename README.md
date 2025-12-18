# Benchmarks

This document compares the performance of different implementations (C++, Rust, Julia, Python via Rust wrapper, and Python with NumPy/SciPy/Numba) for random number generation and stochastic process simulation.

> **Note:** Lower values are faster. All visualizations below are generated from the `mean` values.

---

## Random Number Sampling

**Unit:** ms &nbsp;|&nbsp; **Length:** `10_000_000`

### Uniform distribution

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 12.848 | 11.963 | 25.771 |
| **Rust** | **1.641** | **1.628** | **1.655** |
| Julia | 4.198 | 4.030 | 33.727 |
| Python (Rust wrapper) | 4.51 | 4.04 | 7.27 |
| Python (NumPy / SciPy) | 26.22 | 25.84 | 26.61 |

### Normal distribution

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 50.348 | 45.629 | 134.988 |
| **Rust** | **6.701** | **6.631** | **6.810** |
| Julia | 12.831 | 12.393 | 43.719 |
| Python (Rust wrapper) | 6.33 | 5.94 | 7.36 |
| Python (NumPy / SciPy) | 108.83 | 107.12 | 142.16 |

### Exponential distribution

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 33.3436  | 28.1625 | 40.7075 |
| **Rust** | **7.010** | **6.978** | **7.048** |
| Julia | 13.545 | 13.312 | 26.987 |
| Python (Rust wrapper) | 6.77 | 6.10 | 37.00 |
| Python (NumPy / SciPy) | 88.54 | 87.66 | 95.07 |

### Stable distribution

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 145.7687 | 132.5238 | 187.3853 |
| Rust | 73.293  | 73.488 | 73.702 |
| Julia | 274.270 | 261.133 | 286.218 |
| **Python (Rust wrapper)** | **67.94** | **66.92** | **72.13** |
| Python (NumPy / SciPy) | 615.60 | 612.23 | 621.36 |

---

## Stochastic Process Simulation (Apple Silicon M3 (8-core CPU))

### Brownian Motion

**Setup:** time = 100, time step = 0.01, num samples = 10,000

#### Simulation

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 355.05 μs | 318.708 μs | 424.750 μs |
| Rust | 44.526 μs | 43.727 μs | 45.427 μs |
| **Julia** | **38.425 μs** | **27.042 μs** | **1138 μs** |
| Python (Rust wrapper) | 61.14 μs | 40.71 μs | 109.83 μs |
| Python (NumPy / Numba) | 125.66 μs | 119.25 μs | 151.83 μs |

#### MSD

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 838.710 ms | 833.522 ms | 848.472 ms |
| Rust | 70.148 ms | 69.122 ms | 70.806 ms |
| **Julia** | **61.153 ms** | **59.512 ms** | **80.264 ms** |
| Python (Rust wrapper) | 80.67 ms | 77.66 ms | 95.97 ms |
| Python (NumPy / Numba) | 344.29 ms | 311.43 ms | 448.81 ms |
