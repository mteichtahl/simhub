# MPark.Variant

> __C++17__ `std::variant` as a standalone __C++14__ library.

[![stability][badge.stability]][stability]
[![travis][badge.travis]][travis]
[![appveyor][badge.appveyor]][appveyor]
[![license][badge.license]][license]
[![gitter][badge.gitter]][gitter]
[![wandbox][badge.wandbox]][wandbox]

[badge.stability]: https://img.shields.io/badge/stability-stable-brightgreen.svg
[badge.travis]: https://travis-ci.org/mpark/variant.svg?branch=master
[badge.appveyor]: https://ci.appveyor.com/api/projects/status/github/mpark/variant?branch=master&svg=true
[badge.license]: http://img.shields.io/badge/license-boost-blue.svg
[badge.gitter]: https://badges.gitter.im/mpark/variant.svg
[badge.wandbox]: https://img.shields.io/badge/try%20it-on%20wandbox-green.svg

[stability]: http://github.com/badges/stability-badges
[travis]: https://travis-ci.org/mpark/variant
[appveyor]: https://ci.appveyor.com/project/mpark/variant
[license]: https://github.com/mpark/variant/blob/master/LICENSE_1_0.txt
[gitter]: https://gitter.im/mpark/variant
[wandbox]: https://wandbox.org/permlink/b4NDy4VupqPWkjva

## Introduction

__MPark.Variant__ provides an implementation of __C++17__ `std::variant` as a standalone __C++14__ library.

The implementation is based on my [implementation of `std::variant` for __libc++__][libcxx-impl]
and is continously tested against __libc++__ `std::variant` test suite.

## Documentation

Refer to [`std::variant` - cppreference.com][cppreference] for the `std::variant`
components of __MPark.Variant__.

[cppreference]: http://en.cppreference.com/w/cpp/utility/variant

## CMake Variables

  -  __`MPARK_VARIANT_INCLUDE_TESTS`__:`STRING` (__default__: `""`)

      Semicolon-separated list of tests to build. Possible values are `mpark` and `libc++`.

      __NOTE__: The __libc++__ `std::variant` tests are built with `-std=c++1z`.

## Requirements

This library requires a standard conformant __C++14__ compiler.
The following compilers are continously tested:

| Compiler                               | Operating System                            | Version String                                                                          |
|----------------------------------------|---------------------------------------------|-----------------------------------------------------------------------------------------|
| GCC 5.4.1                              | Ubuntu 14.04.5 LTS                          | g++-5 (Ubuntu 5.4.1-2ubuntu1~14.04) 5.4.1 20160904                                      |
| GCC 6.2.0                              | Ubuntu 14.04.5 LTS                          | g++-6 (Ubuntu 6.2.0-3ubuntu11~14.04) 6.2.0 20160901                                     |
| Clang 3.5.2                            | Ubuntu 14.04.5 LTS                          | Ubuntu clang version 3.5.2-svn232544-1~exp1 (branches/release_35) (based on LLVM 3.5.2) |
| Clang 3.6.2                            | Ubuntu 14.04.5 LTS                          | Ubuntu clang version 3.6.2-svn240577-1~exp1 (branches/release_36) (based on LLVM 3.6.2) |
| Clang 3.7.1                            | Ubuntu 14.04.5 LTS                          | Ubuntu clang version 3.7.1-svn253742-1~exp1 (branches/release_37) (based on LLVM 3.7.1) |
| Clang 3.8.0                            | Ubuntu 14.04.5 LTS                          | clang version 3.8.0-2ubuntu3~trusty4 (tags/RELEASE_380/final)                           |
| Clang 3.9.1                            | Ubuntu 14.04.5 LTS                          | clang version 3.9.1-svn288847-1~exp1 (branches/release_39)                              |
| Clang Xcode 6.4                        | Darwin Kernel Version 14.5.0 (OS X 10.10.3) | Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)                      |
| Clang Xcode 7.3                        | Darwin Kernel Version 15.6.0 (OS X 10.10.5) | Apple LLVM version 7.3.0 (clang-703.0.31)                                               |
| Clang Xcode 8.2                        | Darwin Kernel Version 16.1.0 (OS X 10.12.1) | Apple LLVM version 8.0.0 (clang-800.0.42.1)                                             |
| Visual Studio 14 2015 (__Clang/LLVM__) | Visual Studio Community 2015 with Update 3  | Microsoft (R) Build Engine version 14.0.25420.1                                         |

__NOTE__: Enabling __libc++__ `std::variant` tests require `-std=c++1z` support.

## Unit Tests

Refer to [test/README.md](test/README.md).

[libcxx-impl]: https://reviews.llvm.org/rL288547
