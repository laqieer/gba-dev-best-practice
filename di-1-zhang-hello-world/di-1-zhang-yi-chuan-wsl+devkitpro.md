---
description: 加速Windows上的工程构建
---

# 第1章异传 WSL+devkitPro

{% embed url="https://www.bilibili.com/video/BV1hm4y1o7hm" %}

devkitPro官方提供的Windows安装程序是基于[MSYS2](https://www.msys2.org)的，性能不如[WSL2](https://docs.microsoft.com/zh-cn/windows/wsl/)

{% embed url="https://www.bilibili.com/video/BV1La41127X7" %}
Benchmark for devkitPro: MSYS2 vs WSL2
{% endembed %}

电脑型号: Surface Book 3 Model 1899 i7

测试工程：

{% embed url="https://github.com/laqieer/fe7-jp-stunning-tribble" %}

测试结果：

* MSYS2: 14'35"
* WSL2: 0'42"

测试结论：WSL2 比 MSYS2 快20倍 (WSL2 is 20x faster than MSYS2)

如果构建大型工程，推荐WSL2环境，可以显著节省构建时间。
