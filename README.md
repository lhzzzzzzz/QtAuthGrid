# 登录系统 (Login System)

## 项目简介
这是一个基于Qt框架开发的登录系统，提供了用户登录界面和登录结果反馈功能。系统支持中文界面，并具有简洁美观的用户界面设计。

## 功能特性
- 用户登录界面
- 登录成功/失败反馈
- 中文界面支持
- 响应式界面设计

## 环境要求
- Qt 6.8.2
- MinGW 64-bit
- CMake 3.16或更高版本
- C++17或更高版本

## 构建说明
1. 确保已安装所需环境
2. 克隆项目到本地
3. 在项目根目录下创建build文件夹
4. 使用CMake构建项目：
   ```bash
   cd build
   cmake ..
   cmake --build .
   ```

## 项目结构
```
firstDemo/
├── main.cpp          # 程序入口
├── mainwindow.cpp    # 主窗口实现
├── mainwindow.h      # 主窗口头文件
├── mainwindow.ui     # 主窗口UI设计
├── table.cpp         # 表格相关实现
├── table.h          # 表格相关头文件
├── table.ui         # 表格UI设计
├── success.cpp      # 成功界面实现
├── success.h        # 成功界面头文件
├── success.ui       # 成功界面UI设计
├── fail.cpp         # 失败界面实现
├── fail.h          # 失败界面头文件
├── fail.ui         # 失败界面UI设计
└── CMakeLists.txt  # CMake构建配置
```

## 版本信息
- 当前版本：1.0.0
- 发布日期：2024-03-26

## 作者
- 作者：Lhzzzzz
