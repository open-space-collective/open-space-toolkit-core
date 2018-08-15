import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="LibraryCorePy",
    version="0.0.8", # [TBI]
    author="Open Space Collective",
    author_email="contact@open-space-collective.org",
    description="Fundamental types, containers and utilities.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url = "https://github.com/open-space-collective/library-core",
    classifiers=(
        "Development Status :: 3 - Alpha",
        "Programming Language :: Python :: 3",
        # "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX :: Linux"
    ),
    keywords="open-space-collective core",
    packages=setuptools.find_packages(),
    # package_dir={'': './LibraryCorePy'},
    package_data={'': ['LibraryCorePy.so', 'liblibrary-core.so.0']}
)




# from setuptools import setup, Extension

# setup(
#     ext_modules = [Extension("edlib",
#                              ["edlib.bycython.c", "edlib/src/edlib.cpp"],
#                              include_dirs=["edlib/include"])]
# )