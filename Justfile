cpp-build:
    cd cpp && rm -rf build && mkdir build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON  -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

build:
    cd cpp && rm -rf build && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
    cd rust && cargo clean && cargo build --release
    cd python && uv sync && source .venv/bin/activate

bench:
    cd cpp/bin && ./random_bench
    cd rust/ && cargo run --release
    cd julia && julia --project=. -t 8 src/main.jl
    cd python && uv run main.py

