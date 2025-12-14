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

```mermaid
bar
    title: Uniform RNG (mean, ms)
    xAxisTitle: ms (lower is better)
    yAxisTitle: Implementation
    orientation: horizontal
    xMin: 0
    xMax: 30
    series Rust: 1.641
    series Julia: 4.198
    series Python (Rust wrapper): 4.51
    series C++: 12.848
    series Python (NumPy / SciPy): 26.22
```

### Normal distribution

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 50.348 | 45.629 | 134.988 |
| **Rust** | **6.701** | **6.631** | **6.810** |
| Julia | 12.831 | 12.393 | 43.719 |
| Python (Rust wrapper) | 6.33 | 5.94 | 7.36 |
| Python (NumPy / SciPy) | 108.83 | 107.12 | 142.16 |

```mermaid
bar
    title: Normal RNG (mean, ms)
    xAxisTitle: ms (lower is better)
    yAxisTitle: Implementation
    orientation: horizontal
    xMin: 0
    xMax: 120
    series Python (Rust wrapper): 6.33
    series Rust: 6.701
    series Julia: 12.831
    series C++: 50.348
    series Python (NumPy / SciPy): 108.83
```

### Exponential distribution

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 33.3436  | 28.1625 | 40.7075 |
| **Rust** | **7.010** | **6.978** | **7.048** |
| Julia | 13.545 | 13.312 | 26.987 |
| Python (Rust wrapper) | 6.77 | 6.10 | 37.00 |
| Python (NumPy / SciPy) | 88.54 | 87.66 | 95.07 |

```mermaid
bar
    title: Exponential RNG (mean, ms)
    xAxisTitle: ms (lower is better)
    yAxisTitle: Implementation
    orientation: horizontal
    xMin: 0
    xMax: 100
    series Python (Rust wrapper): 6.77
    series Rust: 7.010
    series Julia: 13.545
    series C++: 33.3436
    series Python (NumPy / SciPy): 88.54
```

### Stable distribution

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 145.7687 | 132.5238 | 187.3853 |
| Rust | 73.293  | 73.488 | 73.702 |
| Julia | 274.270 | 261.133 | 286.218 |
| **Python (Rust wrapper)** | **67.94** | **66.92** | **72.13** |
| Python (NumPy / SciPy) | 615.60 | 612.23 | 621.36 |

```mermaid
bar
    title: Stable RNG (mean, ms)
    xAxisTitle: ms (lower is better)
    yAxisTitle: Implementation
    orientation: horizontal
    xMin: 0
    xMax: 650
    series Python (Rust wrapper): 67.94
    series Rust: 73.293
    series C++: 145.7687
    series Julia: 274.270
    series Python (NumPy / SciPy): 615.60
```

---

## Stochastic Process Simulation

### Brownian Motion

**Setup:** time = 100, time step = 0.01, num samples = 10,000

#### Simulation

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 355.05 μs | 318.708 μs | 424.750 μs |
| Rust | 66.683 μs | 65.882 μs | 67.487 μs |
| **Julia** | **38.006 μs** | **26.875 μs** | **1062 μs** |
| Python (Rust wrapper) | 61.14 μs | 40.71 μs | 109.83 μs |
| Python (NumPy / Numba) | 125.66 μs | 119.25 μs | 151.83 μs |

```mermaid
bar
    title: Brownian Motion Simulation (mean, μs)
    xAxisTitle: μs (lower is better)
    yAxisTitle: Implementation
    orientation: horizontal
    xMin: 0
    xMax: 400
    series Julia: 38.006
    series Python (Rust wrapper): 61.14
    series Rust: 66.683
    series Python (NumPy / Numba): 125.66
    series C++: 355.05
```

#### MSD

| Language | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 838.710 ms | 833.522 ms | 848.472 ms |
| Rust | 77.077 ms | 76.666 ms | 79.639 ms |
| **Julia** | **47.914 ms** | **44.865 ms** | **68.910 ms** |
| Python (Rust wrapper) | 80.67 ms | 77.66 ms | 95.97 ms |
| Python (NumPy / Numba) | 344.29 ms | 311.43 ms | 448.81 ms |

```mermaid
bar
    title: Brownian Motion MSD (mean, ms)
    xAxisTitle: ms (lower is better)
    yAxisTitle: Implementation
    orientation: horizontal
    xMin: 0
    xMax: 900
    series Julia: 47.914
    series Rust: 77.077
    series Python (Rust wrapper): 80.67
    series Python (NumPy / Numba): 344.29
    series C++: 838.710
```
