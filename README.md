# obfusimg

This is an application for obfuscating images through algorithm-generated permutations.

## Features

Please see [the official documentation](https://github.com/PetalAdrift/obfusimg/tree/main/doc/obfusimg-doc.pdf) for a slightly verbose explanation on what the application does. (Alternatively, we provide a LLM-translated, human-vetted copy of [the official documentation in Chinese](https://github.com/PetalAdrift/obfusimg/tree/main/doc/obfusimg-doc-zh.pdf).)

TL;DR: This application takes an image (and sometimes a seed/password) and makes it impossible for humans to read in an invertible manner.

## How-To

With `GCC` or other C++ compilers installed, you simply need to clone the repo and call `make all` in the directory. (I used MSYS2 MINGW64 on my local machine. [![works on my machine badge](https://cdn.jsdelivr.net/gh/nikku/works-on-my-machine@v0.4.0/badge.svg)](https://github.com/nikku/works-on-my-machine)) (Windows users need an additional step of installing [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm) and adding it to the system PATH.)

The syntax for the actual software is `./obfusimg(.exe) path/to/image algorithm_id algorithm_seed`.

Alternatively, you may choose to use the [web-version](https://obfusimg.netlify.app/).