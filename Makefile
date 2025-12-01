all: fresh

fresh:
	@echo "1. Removing old build artifacts..."
	rm -rf build/
	rm -rf src/bonsai/*.so
	rm -rf src/*.egg-info

	@echo "2. Syncing environment..."
	uv sync

	@echo "3. Compiling C Extension (inplace)..."
	uv run python setup.py build_ext --inplace

	@echo "4. Installing editable package..."
	uv pip install -e .
