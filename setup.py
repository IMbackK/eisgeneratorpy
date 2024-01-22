import sys

try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise

from setuptools import find_packages

setup(
    name="eisgenerator",
    version="1.0.0",
    description="",
    author="Carl Philipp Klemm",
    license="LGPL-3.0",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    cmake_install_dir="src/eisgenerator",
    include_package_data=True,
    python_requires=">=3.8",
)
