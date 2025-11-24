from setuptools import setup, Extension

bonsai_module = Extension("bonsai._core", sources=[], include_dirs=["src"])

setup(
    name="bonsai",
    version="0.1.0",
    description="A toy DataFrame implementation in C",
    package_dir={"": "src"},
    packages=["bonsai"],
    ext_modules=[bonsai_module],
)
