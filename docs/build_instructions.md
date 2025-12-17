# Super Auto Pets - 编译和运行说明

## 重要提示

当前使用的 Qt 版本是 **MinGW** 版本，但是 Visual Studio 默认使用 **MSVC** 编译器。这会导致链接错误。

## 解决方案

### 方案 1：使用 MinGW 编译器（推荐）

1. 确保已安装 MinGW（Qt 自带的在 `D:\Qt\Tools\mingw1310_64\bin`）
2. 删除 `build` 文件夹
3. 在 PowerShell 中运行以下命令：

```powershell
# 设置环境变量
$env:PATH = "D:\Qt\Tools\mingw1310_64\bin;D:\Qt\6.10.0\mingw_64\bin;" + $env:PATH

# 创建 build 文件夹
mkdir build
cd build

# 配置项目（使用 MinGW）
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..

# 编译
mingw32-make
```

### 方案 2：使用 MSVC 版本的 Qt

1. 安装 MSVC 版本的 Qt（例如 `msvc2019_64`）
2. 修改 `CMakePresets.json` 中的 `CMAKE_PREFIX_PATH` 为 MSVC 版本的路径
3. 删除 `build` 文件夹
4. 在 Visual Studio Developer Command Prompt 中重新配置和编译

## 运行程序

编译成功后，可执行文件位于：
- MinGW: `build\SuperAutoPets.exe`
- MSVC: `build\Debug\SuperAutoPets.exe`

直接双击运行即可！

## 功能说明

### 已实现的功能

1. **商店系统**
   - 购买宠物（3 金币）
   - 购买食物（价格不同）
   - 刷新商店（1 金币）
   - 出售宠物（获得 1 金币）

2. **宠物系统**
   - 8 种不同的宠物（猫、蚂蚁、鱼、蟋蟀、天鹅、火烈鸟、刺猬、孔雀）
   - 宠物升级系统（相同宠物会合并升级）
   - 宠物属性显示（生命值、攻击力、等级、经验）

3. **食物系统**
   - 9 种不同的食物
   - 不同的食物效果（加生命、加攻击、特殊效果）

4. **玩家系统**
   - 金币管理
   - 生命值系统
   - 回合系统
   - 宠物阵容管理（最多5只）

5. **UI 界面**
   - 玩家信息栏（金币、生命、回合、奖杯）
   - 宠物阵容展示区
   - 商店宠物展示区
   - 商店食物展示区
   - 操作按钮（刷新、结束回合）

### 待实现的功能

- 战斗系统
- 宠物技能效果
- 更多宠物和食物
- 联机对战
- 音效和动画

## 注意事项

- 确保 Qt 版本与编译器匹配
- 如果遇到中文乱码，确保使用 UTF-8 编码
- 编译时需要 C++20 支持

