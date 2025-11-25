# 🌳 Bonsai

**A lightweight DataFrame implementation written in C.**

![Python](https://img.shields.io/badge/python-3.13%2B-blue)
![Build](https://img.shields.io/badge/build-native%20C-green)
![License](https://img.shields.io/badge/license-MIT-purple)

Bonsai is a project designed to understand how Python C-Extensions work. It implements a basic DataFrame structure using C to explore manual memory management and the Python C-API.

> **Note:** This is a playground project created for learning and experimentation.
            *WIP*

---

## 🚀 Installation

### Prerequisites
- A C-Compiler
- Python 3.13
- [uv](https://github.com/astral-sh/uv)

### Setup

```bash
# 1. Clone the repository
git clone git@github.com:swsxm/bonsai.git
cd bonsai

# 2. Initialize the environment
uv sync

# 3. Compile and install in editable mode
uv run python setup.py build_ext --inplace
uv pip install -e .
