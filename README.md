# Benchmarks

> [!NOTE]
> This repository is moved to [py-diffusionx](https://github.com/tangxiangong/py-diffusionx/tree/main/benchmark).

## Random Number Sampling (unit: ms, len: 10_000_000)

### Uniform distribution
| | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 12.848 | 11.963 | 25.771 |
| Rust | 1.641 | 1.628 | 1.655 |
| Julia | 4.198 | 4.030 | 33.727 |
| Python (Rust wrapper) | 4.51 | 4.04 | 7.27 |
| Python (NumPy / SciPy) | 26.22 | 25.84 | 26.61 |

### Normal distribution
| | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 50.348 | 45.629 | 134.988 |
| Rust | 6.701 | 6.631 | 6.810 |
| Julia | 12.831 | 12.393 | 43.719 |
| Python (Rust wrapper) | 6.33 | 5.94 | 7.36 |
| Python (NumPy / SciPy) | 108.83 | 107.12 | 142.16 |

### Exponential distribution
| | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 33.3436  | 28.1625 | 40.7075 |
| Rust | 7.010 | 6.978 | 7.048 |
| Julia | 13.545 | 13.312 | 26.987 |
| Python (Rust wrapper) | 6.77 | 6.10 | 37.00 |
| Python (NumPy / SciPy) | 88.54 | 87.66 | 95.07 |


### Stable distribution
| | mean | min | max |
|:---:|:---:|:---:|:---:|
| C++ | 145.7687 | 132.5238 | 187.3853 |
| Rust | 73.293  | 73.488 | 73.702 |
| Julia | 274.270 | 261.133 | 286.218 |
| Python (Rust wrapper) | 67.94 | 66.92 | 72.13 |
| Python (NumPy / SciPy) | 615.60 | 612.23 | 621.36 |
