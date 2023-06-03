# NEAT-CPP-PY

## Description

This is a NEAT implementation in C++ with Python interface, intended to be used for speed improvement over pure Python implementation.  
This is repo is work in progress and under active development.  
The implementation is based on the paper [Evolving Neural Networks through Augmenting Topologies](http://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf) by Kenneth O. Stanley and Risto Miikkulainen.  

Other languages support C++ binding is planned to be added in the future.

## Usage

This project is still under development and is not ready for use.  

- Currently C++ direct usage is supported. The implementation has been tested against the XOR problem, dynamic pole balancing problem is planned to be tested next.
- C++ direct usage is expected to be completed in late June 2023.
- Python direct usage is expected to be completed in late July to late August 2023.

## Road map

- [x] C++ implementation
  - [x] Node class implementation
  - [x] Edge class implementation
  - [x] Genome class implementation
  - [x] Memory management test for above classes
  - [x] Species class implementation
  - [x] SpeciesHandler class implementation
  - [x] Memory management test for above classes
  - [x] Population class
  - [x] Memory management test for above classes
- [x] Testing
  - [x] Test Handler class
  - [x] Basic XOR test
  - [ ] Dynamic Pole Balancing problem test
- [ ] Python interface
  - [ ] C API
  - [ ] Python interface for Node class
  - [ ] Python interface for Edge class
  - [ ] Python interface for Genome class
  - [ ] Python interface for SpeciesHandler class
  - [ ] Python interface for Population class
- [ ] Pip package
- [ ] Documentation
- [ ] Examples
- [ ] Threading support

## Build

This project uses Makefile for building.  
To build the project run `make` in the root directory.

Language version used for development:

- python 3.9.5  
- g++ C++17
