关于编译
- clang++ main.cpp 在M1的MacOS上出来的是x86，如果需要arm则需要指定arch, `clang++ -arch arm64`