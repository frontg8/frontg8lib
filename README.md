The frontg8 core library
========================

[![Build Status](https://travis-ci.org/frontg8/frontg8lib.svg?branch=master)](https://travis-ci.org/frontg8/frontg8lib) [![Coverage Status](https://coveralls.io/repos/github/frontg8/frontg8lib/badge.svg?branch=master)](https://coveralls.io/github/frontg8/frontg8lib?branch=master) [![Documentation Status](https://readthedocs.org/projects/libfrontg8/badge/?version=latest)](http://libfrontg8.readthedocs.io/en/latest/?badge=latest)

***NOTE: This library is under heavy development***

Introduction
------------

libfrontg8 (a.k.a frontg8lib) is a new foundation for the
[frontg8](https://www.frontg8.ch) project. It contains all components required
to build client and server applications and exposes a generic C API. This API
makes it easy to implement frontends for other languages like C++, Python, Rust
and Java.

The library provides all required functionality like message- and error
handling, cryptographic operations and network connectivity.

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
