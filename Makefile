SHELL=cmd.exe

all: fresh

fresh:
	@echo "1. Removing old build artifacts..."
	-rmdir /s /q build 2>nul
	-del /s /q src\bonsai\*.pyd 2>nul
	-del /s /q src\bonsai\*.so 2>nul
	-for /d %%i in (src\*.egg-info) do rmdir /s /q "%%i" 2>nul

	@echo "2. Syncing environment..."
	uv sync

	@echo "3. Compiling C Extension (inplace)..."
	uv run python setup.py build_ext --inplace

	@echo "4. Installing editable package..."
	uv pip install -e .