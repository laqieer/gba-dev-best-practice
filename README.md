---
description: 从开发环境到第一个工程
---

# 第1章 Hello World

## 搭建GBA开发环境

安装 [devkitPro](https://devkitpro.org/wiki/Getting\_Started) 或者 [gba-toolchain](https://github.com/felixjones/gba-toolchain)

## GBA工程

### 创建

从模板创建：

* 开发环境自带的模板
* [devkitPro + libtonc 的模板](https://github.com/exelotl/libtonc-template)

### 构建

`make` 或者 [cmake](https://cmake.org/cmake/help/latest/)

### 运行

[mGBA](http://mgba.io) 或者烧录卡

### 调试

* [mGBA + printf](https://github.com/mgba-emu/mgba/tree/master/opt/libgba)
* [mGBA + gdb](https://simianzombie.com/posts/2018/11/12/debugging-with-mgba)
