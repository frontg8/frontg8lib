The core frontg8 library
========================

[![Build Status](https://travis-ci.org/frontg8/frontg8lib.svg?branch=master)](https://travis-ci.org/frontg8/frontg8lib) [![Coverage Status](https://coveralls.io/repos/github/frontg8/frontg8lib/badge.svg?branch=master)](https://coveralls.io/github/frontg8/frontg8lib?branch=master)[![Documentation Status](https://readthedocs.org/projects/libfrontg8/badge/?version=latest)](http://libfrontg8.readthedocs.io/en/latest/?badge=latest)


***NOTE: This library is under heavy development***

This repository contains the core components of frontg8

Build requirements
------------------

* A reasonably modern compiler (GCC 6 / Clang 3.8)
* Conan (https://conan.io)
* CMake 3.2
* Some form of Linux

We currently test and develop solely under Linux. If you are interested in
helping out testing on/porting to other systems, please open an issue.

Building
--------

```bash
$ git clone https://github.com/frontg8/frontg8lib.git
$ cd frontg8lib
$ git submodule update --init
$ cd build
$ conan install .. --build=missing
$ cmake ..
$ cmake --build . -- -j$(nproc)
```

The API
=======

The frontg8 core library is built as a pure C API. This makes it easy to create
bindings for a wide variety of other languages. For information on the current
API, please browse the header files in `include/frontg8`. For an example on the
usage, check out the API unit tests and the demos in `src/demo`.
