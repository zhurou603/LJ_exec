#!/bin/bash

# 准备环境
prefix=`dirname "$0"`
prefix=`cd "$prefix"; pwd`

echo $prefix
mkdir -p ${prefix}/lib
mkdir -p ${prefix}/include

cd build

# 解压
tar -xzf googletest-release-1.8.0.tar.gz

# 安装
#   googltest
cd googletest-release-1.8.0/googletest
g++ -isystem ./include -I. -pthread -c ./src/gtest-all.cc
ar -rv libgtest.a gtest-all.o
cp -r ./include/* ${prefix}/include/    # cp head files
cp ./libgtest.a ${prefix}/lib/          # cp compiled static library


