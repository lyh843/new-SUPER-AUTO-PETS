# 在 Qt Creator 中打开 Super Auto Pets 项目

## 方法一：直接打开 CMakeLists.txt（推荐）

### 步骤：

1. **启动 Qt Creator**
   - 双击桌面的 Qt Creator 图标
   - 或从开始菜单启动

2. **打开项目**
   - 点击菜单栏：`文件` → `打开文件或项目...`
   - 或使用快捷键：`Ctrl + O`
   - 或点击欢迎页面的 `Open Project` 按钮

3. **选择 CMakeLists.txt**
   - 浏览到项目文件夹：`C:\Users\bruce\Desktop\super_auto_pets\`
   - 选择 `CMakeLists.txt` 文件
   - 点击 `打开`

4. **配置项目（Configure Project）**
   
   Qt Creator 会弹出 "Configure Project" 对话框：

   **选项 A - 使用已有的 build 文件夹（推荐）**：
   - 取消勾选所有默认的构建目录
   - 点击 `Browse...` 按钮
   - 选择现有的 `build` 文件夹：`C:\Users\bruce\Desktop\super_auto_pets\build`
   - 确保选择 **Desktop Qt 6.10.0 MinGW 64-bit** Kit
   - 点击 `Configure Project` 按钮

   **选项 B - 创建新的构建目录**：
   - 确保选择了 **Desktop Qt 6.10.0 MinGW 64-bit** Kit
   - 构建目录默认为：`../build-SuperAutoPets-Desktop_Qt_6_10_0_MinGW_64_bit-Debug`
   - 点击 `Configure Project` 按钮

5. **等待 CMake 配置**
   - Qt Creator 会自动运行 CMake 配置
   - 在底部的 `Compile Output` 窗口可以看到配置过程
   - 等待显示 "Configuration completed" 或类似信息

6. **项目配置完成！**
   - 左侧会显示项目文件树
   - 现在可以编辑、编译和运行项目了

## 方法二：从最近项目打开

如果之前已经在 Qt Creator 中打开过：

1. 启动 Qt Creator
2. 在欢迎页面的 `Recent Projects` 列表中找到 `SuperAutoPets`
3. 点击项目名称即可打开

## 项目配置说明

### Kit 选择

确保选择正确的 Kit：
- ✅ **Desktop Qt 6.10.0 MinGW 64-bit**
- ❌ 不要选择 MSVC 版本（会导致链接错误）

### 构建配置

Qt Creator 通常会创建两种配置：
- **Debug**：用于开发调试（推荐）
- **Release**：用于发布版本

切换配置：
- 点击左下角的 `Debug` 或 `Release` 按钮
- 或使用左侧工具栏的构建配置选择器

## 编译和运行

### 编译项目

有以下几种方式：

1. **快捷键**：
   - `Ctrl + B`：构建整个项目
   - `Ctrl + R`：运行（会自动先构建）

2. **菜单栏**：
   - `构建` → `构建项目 "SuperAutoPets"`
   - `构建` → `重新构建项目 "SuperAutoPets"`（清理后重建）

3. **工具栏**：
   - 点击左下角的 🔨 锤子图标（构建）
   - 点击左下角的 ▶️ 播放图标（运行）

### 运行项目

1. **方式一**：
   - 按 `Ctrl + R`
   - 或点击左下角的绿色 ▶️ 三角形按钮

2. **方式二**：
   - 菜单栏：`构建` → `运行`

3. **方式三**：
   - 按 `F5`（调试运行）

### 查看输出

- **编译输出**：底部的 `Compile Output` 窗口
- **应用程序输出**：底部的 `Application Output` 窗口
- **问题列表**：底部的 `Issues` 窗口（显示编译错误和警告）

## Qt Creator 界面说明

### 左侧面板

1. **欢迎**：显示最近项目和示例
2. **编辑**：代码编辑模式（默认）
3. **设计**：UI 设计模式（.ui 文件）
4. **调试**：调试模式
5. **项目**：项目配置
6. **帮助**：文档和帮助

### 项目文件树（左侧）

展开后可以看到：
```
SuperAutoPets/
├── src/
│   ├── main.cpp
│   ├── model/
│   │   ├── Pet.hpp
│   │   ├── Pet.cpp
│   │   ├── Player.hpp
│   │   ├── Player.cpp
│   │   ├── Shop.hpp
│   │   ├── Shop.cpp
│   │   ├── Food.hpp
│   │   ├── Food.cpp
│   │   ├── Skill.hpp
│   │   └── Skill.cpp
│   ├── ui/
│   │   ├── ShopView.hpp
│   │   ├── ShopView.cpp
│   │   ├── BattleView.hpp
│   │   └── BattleView.cpp
│   └── engine/
│       ├── BattleEngine.hpp
│       └── BattleEngine.cpp
├── CMakeLists.txt
└── CMakePresets.json
```

### 编辑器（中间）

- 支持代码高亮
- 支持代码补全（`Ctrl + Space`）
- 支持跳转到定义（`F2` 或 `Ctrl + 鼠标左键`）
- 支持查找和替换（`Ctrl + F`）

### 底部面板

- **Issues**：编译错误和警告
- **Search Results**：搜索结果
- **Application Output**：程序输出
- **Compile Output**：编译输出
- **Debugger Console**：调试控制台

## 常用快捷键

### 编辑
- `Ctrl + Space`：代码补全
- `Ctrl + /`：注释/取消注释
- `Ctrl + F`：查找
- `Ctrl + Shift + F`：全局查找
- `F2`：跳转到定义
- `Shift + F2`：在头文件和源文件之间切换
- `Alt + Enter`：快速修复

### 构建和运行
- `Ctrl + B`：构建
- `Ctrl + R`：运行
- `F5`：调试运行
- `Shift + F5`：停止调试

### 导航
- `Ctrl + K`：快速打开文件
- `Alt + ←/→`：前进/后退
- `Ctrl + Tab`：切换打开的文件

### 窗口
- `Alt + 1-9`：切换左侧面板
- `Esc`：返回编辑器
- `F4`：切换头文件/源文件

## 调试功能

### 设置断点

1. 点击代码行号左侧的空白处
2. 或将光标放在该行，按 `F9`
3. 红点表示断点已设置

### 开始调试

1. 按 `F5` 或点击左下角的调试按钮（有虫子图标）
2. 程序会在断点处暂停

### 调试控制

- `F5`：继续执行
- `F10`：单步跳过（Step Over）
- `F11`：单步进入（Step Into）
- `Shift + F11`：单步跳出（Step Out）
- `Shift + F5`：停止调试

### 查看变量

- 在 `Locals` 窗口查看局部变量
- 在 `Expressions` 窗口添加监视表达式
- 鼠标悬停在变量上查看值

## 项目配置（Project Settings）

点击左侧的 `Projects` 按钮（或按 `Ctrl + 5`）可以配置：

### Build & Run 设置

1. **Build Steps**（构建步骤）
   - CMake 配置参数
   - Make 参数

2. **Run Settings**（运行设置）
   - 可执行文件路径
   - 工作目录
   - 命令行参数
   - 运行环境变量

### Code Style（代码风格）

- 设置缩进、空格等
- 位置：`工具` → `选项` → `C++` → `Code Style`

## 常见问题解决

### 问题 1：找不到 Qt 库

**解决方案**：
1. 点击 `工具` → `选项` → `Kits`
2. 检查 Qt 版本路径是否正确
3. 确保选择了 MinGW 64-bit 版本

### 问题 2：CMake 配置失败

**解决方案**：
1. 删除 `build` 文件夹
2. 在 Qt Creator 中右键项目
3. 选择 `Run CMake`
4. 或选择 `Clean`，然后重新构建

### 问题 3：中文乱码

**解决方案**：
1. 确保文件编码为 UTF-8
2. 菜单：`工具` → `选项` → `Text Editor` → `Behavior`
3. 设置 Default encoding 为 `UTF-8`

### 问题 4：编译错误

**解决方案**：
1. 检查 `Issues` 窗口中的错误信息
2. 确保所有依赖的头文件都正确包含
3. 清理并重新构建：`构建` → `清理项目` → `构建项目`

### 问题 5：MOC 文件找不到

**解决方案**：
1. Qt Creator 会自动处理 MOC
2. 确保类定义中有 `Q_OBJECT` 宏
3. 重新运行 CMake：右键项目 → `Run CMake`

## 实用技巧

### 1. 快速打开文件
- 按 `Ctrl + K`，输入文件名
- 支持模糊搜索

### 2. 查找用法
- 右键符号 → `Find References to Symbol at Cursor`
- 或按 `Ctrl + Shift + U`

### 3. 重构
- 右键符号 → `Refactor` → `Rename Symbol Under Cursor`
- 或按 `Ctrl + Shift + R`

### 4. 分屏编辑
- 拖动文件标签到编辑器的边缘
- 可以同时查看多个文件

### 5. 书签
- `Ctrl + M`：添加/移除书签
- `Ctrl + .`：下一个书签

### 6. TODO 标记
- 在代码中添加 `// TODO: 描述`
- 在 `Projects` 面板可以看到所有 TODO

## 推荐设置

### 编辑器设置

1. **启用代码折叠**
   - `工具` → `选项` → `Text Editor` → `Display`
   - 勾选 `Display folding markers`

2. **显示行号**
   - `工具` → `选项` → `Text Editor` → `Display`
   - 勾选 `Display line numbers`

3. **自动保存**
   - `工具` → `选项` → `Environment` → `System`
   - 勾选 `Auto-save modified files`

### 代码风格设置

1. **C++ 代码风格**
   - `工具` → `选项` → `C++` → `Code Style`
   - 选择或自定义代码风格

2. **Qt Quick 代码风格**
   - `工具` → `选项` → `Qt Quick` → `Code Style`

## 总结

使用 Qt Creator 打开项目非常简单：
1. 打开 `CMakeLists.txt`
2. 选择 MinGW 64-bit Kit
3. 配置项目
4. 按 `Ctrl + R` 运行

现在你可以开始愉快地开发了！🎉

## 附加资源

- Qt Creator 官方文档：https://doc.qt.io/qtcreator/
- Qt 6 文档：https://doc.qt.io/qt-6/
- C++ 参考：https://en.cppreference.com/

如有问题，欢迎随时询问！

