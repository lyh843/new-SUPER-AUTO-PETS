# 构建

## 安装 Qt 环境

安装 Qt 时需要安装一个配套编译器（如 MinGW ，其他编译器 MSVC、Clang 应该也可行，可以自己探究一下）。

> 我自己安装 Qt 时因为计算机上已经有三大编译器 MSVC 2022、MinGW v13.3.1、Clang v21.1.0 ，以为可以直接用了就没安装 Qt 配套编译器，结果 CMake 配置不通，尝试半天也无法使用自己的编译器（因为缺失 Qt 在其配套编译器中才提供的 `Qt6Config.cmake` ）。最后通过运行 `Path/To/My/Qt/MaintenanceTool.exe` 补上配套的 MinGW 编译器才配置成功。

## CMake

在自己的项目根目录下创建一个 `CMakePresets.json` 文件，内容如下：

``` json
{
    "version": 3,
    "cmakeMinimumRequired": {
        "major": 3,
        "minor": 21
    },
    "configurePresets": [
        {
            "name": "default",
            "hidden": false,
            "binaryDir": "${sourceDir}/build",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "CMAKE_PREFIX_PATH": "Path/To/Your/Qt/6.10.0/InstalledCompiler" // 注意修改这里
                // 示例键值："CMAKE_PREFIX_PATH": "D:/Qt/6.10.0/mingw_64"
            }
        }
    ],
    "buildPresets": [
        {
            "name": "debug",
            "configurePreset": "default"
        }
    ]
}
```

然后命令行运行

``` Powershell
cmake --preset default
```

正确配置后，`CMake/生成` 的输出最后一行应该是 `[build] 生成已完成，退出代码为 1` 。如果确是如此，那么恭喜环境配置成功！

# 代码规范

## 头文件

对于项目 C++ ，每个头文件都要有 `#ifndef` 一套“丝滑小连招”，这样交叉 include 时可以防止重复定义，加速编译和链接。具体来讲，例如，对于 `FooBar.hpp` 文件，应该这么写：

``` C++
#ifndef __FOO_BAR_HPP__
#define __FOO_BAR_HPP__

// Your code here...

#endif // __FOO_BAR_HPP__
```

当然对于三大编译器，下面这种写法理论上也没问题：

``` C++
#pragma once

// Your code here...
```

为了简便还是采用 `#pragma once` 写法吧。

## 命名

类使用大驼峰，类的实例对象、公开成员、公开函数使用小驼峰，类的私有成员、私有函数使用单个下划线开头的小驼峰；模板元接口使用蛇形 *（假如我们真的有写模板元的需求的话（）* 。

零散函数、变量、常量等不作严格规定。
