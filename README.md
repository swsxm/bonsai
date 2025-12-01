# 🌳 Bonsai

**A lightweight, high-performance DataFrame implementation written in C.**

![Python](https://img.shields.io/badge/python-3.13%2B-blue)
![Build](https://img.shields.io/badge/build-native%20C-green)
![License](https://img.shields.io/badge/license-MIT-purple)

A native C-extension implementing a bare-metal DataFrame for Python. Bonsai manages its own memory lifecycle and data layout, bypassing high-level Python abstractions to achieve direct interaction with the CPython interpreter.

> **Note:** This is a playground project created for learning C-Extensions and CPython internals.
>  *WIP*

- - -


##  Installation

### Prerequisites
* **C-Compiler** (GCC, Clang, or MSVC)
* **Python 3.13+**
* **[uv](https://github.com/astral-sh/uv)**

### Development Setup

```bash
make
```

- - -

## Usage

To run the library, start the Python interpreter within the `uv` environment:

```bash
uv run python
```

### Basic Example

```python
>>> import bonsai

>>> df = bonsai.DataFrame({
... "id": [1, 2, 3, 4],
... "value": [10.5, 20.0, 30.5, 40.0],
... "label": ["A", "B", "C", "D"],
... "is_valid": [True, False, True, True]
... })
```
