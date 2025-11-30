from setuptools import setup, Extension
import glob

source_files = glob.glob("src/core/**/*.c", recursive=True)
bonsai_module = Extension(
    "bonsai._core",
    sources=source_files,
    include_dirs=["src/core"],
)

setup(
    name="bonsai",
    ext_modules=[bonsai_module],
)
