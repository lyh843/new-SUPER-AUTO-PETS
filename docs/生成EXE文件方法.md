# 生成EXE文件方法

Qt 项目要在没有 Qt 环境、没有 C++ 环境的机器上运行，需要**静态或动态部署 Qt**。通常采用 **动态部署（复制 Qt DLL）**，更稳定也更容易。以下是标准流程（适用于 Qt6，CMake 项目，MinGW-w64 编译链）：

------

步骤 1：生成 Release 版本
 在 Qt Creator 或 VS Code+CMake 下：

```
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

得到类似：

```
build/Release/your_app.exe
```

------

步骤 2：使用 windeployqt 自动收集依赖（推荐）
 Qt 给你准备了官方工具 **windeployqt.exe**，位于：

```
<Qt安装目录>/6.x.x/mingw_64/bin/windeployqt.exe
```

命令：

```
windeployqt.exe --release your_app.exe
```

执行后，会自动把所有需要的 Qt 模块拷贝到与 exe 同一目录，例如：

```
your_app.exe
Qt6Core.dll
Qt6Gui.dll
Qt6Widgets.dll
plugins/
qml/
platforms/
... 其他依赖
```

然后你就可以把这个目录整体压缩，给别人运行，不需要安装 Qt、不需要安装 C++ 环境。

------

步骤 3：确认 MinGW 运行库
 MinGW-w64 下，Qt 应用还依赖 MinGW runtime DLL：

- `libgcc_s_seh-1.dll`
- `libstdc++-6.dll`
- `libwinpthread-1.dll`

`windeployqt` 有时不会自动带这些，需要手动从 **mingw64/bin/** 拷贝到 exe 同目录。

------

若你坚持只给一个 exe（单文件）
 你只能选择 **Qt 静态编译**，但要注意：

1. Qt 的官方发布版本 **没有提供静态库**，必须**自己编译整个 Qt 源码**，耗时非常长（2–4 小时以上）。
2. 静态 Qt 生成的 exe 会非常大（几十 MB）。
3. 编译参数复杂，需要商业许可证才能合法静态链接某些模块。

除非你非常确定要这么做，否则不建议。

------

标准结论
 最可行、行业通用的做法：

**Release 构建 → windeployqt → 把 exe + DLL 打包成文件夹**
 这样就能在没有 Qt 环境、没有 C++ 环境的电脑上正常运行。