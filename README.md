# CppFunAndLearn

### This repository contains some fun and learn code for different functionality presented in various C++ standards

  

1. Curly brackets initialization

Presents how below code gave different results in different versions of GCC compiler (4.X against 5.X and later)
`auto x {1};`

2. Recursive iteration over tuple using SFINAE

My idea (with hint of Marcin you know who) how to implement recursive iteration over tuple elements.
First version uses C++11 functionality std::enable_if
Iteration backward and forward are implemented with possibility to invoke custom function for every tuple element

3. Interface and implementation inheritance separation

How to distinguish inheritance of interfaces and their implementaion using virtual base classes

4. Sufixes _t and _v in template metaprogramming in different c++ versions

How small syntax sugar can make code a little bit more readable