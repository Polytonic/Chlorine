# [Chlorine]()
[![Build Status](http://img.shields.io/travis/Polytonic/Chlorine.svg?style=flat)](https://travis-ci.org/Polytonic/Chlorine)
[![Coverage Status](http://img.shields.io/coveralls/Polytonic/Chlorine.svg?style=flat)](https://coveralls.io/r/Polytonic/Chlorine)

## Summary
Chlorine is a collection of OpenCL utilities to help rapidly prototype parallel processing on graphics processing units.  Chlorine aims to provide a fully functional, generic host, enabling users to focus purely on writing kernels without having to worry about writing boilerplate to connect system and device memory.  Chlorine helpfully displays human-readable exceptions for when things do go horribly wrong.

## Getting Started
Download the [Latest Release](https://github.com/Polytonic/Chlorine/archive/master.zip).  Looking for an [Older Version](https://github.com/Polytonic/Chlorine/releases)?
  ↳ `git clone https://github.com/Polytonic/Chlorine.git`

```
make clean
make all
./bin/clinfo
```

## Dependencies
- C++11
- OpenCL 1.1+

Chlorine is in development.
