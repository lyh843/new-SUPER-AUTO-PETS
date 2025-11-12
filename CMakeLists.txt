cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(SuperAutoPets LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt Kit Dir. Please create your own `CMakePresets.json` as `README.md` said and set the Qt installation path.
set(CMAKE_PREFIX_PATH "" CACHE PATH "Qt installation path (configure in CMakePresets.json)")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS

# Specify MSVC UTF-8 encoding
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 设置编译警告（区分编译器）
if(MSVC)
    add_compile_options(/W3 /Zc:__cplusplus)
else()
    add_compile_options(-Werror=delete-non-virtual-dtor
                        -Werror=deprecated-declarations)
endif()

# 收集源文件
set(SOURCES
    src/main.cpp
    src/model/Pet.cpp
    src/model/Player.cpp
    src/model/Shop.cpp
    src/model/Food.cpp
    src/model/Skill.cpp
    src/ui/ShopView.cpp
    src/ui/BattleView.cpp
    src/engine/BattleEngine.cpp
)

# 收集头文件
set(HEADERS
    src/model/Pet.hpp
    src/model/Player.hpp
    src/model/Shop.hpp
    src/model/Food.hpp
    src/model/Skill.hpp
    src/ui/ShopView.hpp
    src/ui/BattleView.hpp
    src/engine/BattleEngine.hpp
)

add_executable(${PROJECT_NAME}
    WIN32 # If you need a terminal for debug, please comment this statement
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets) # Qt6 Shared Library