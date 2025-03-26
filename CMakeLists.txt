cmake_minimum_required(VERSION 3.16)

project(firstDemo VERSION 0.1 LANGUAGES CXX)

# 移除 MSVC 强制要求
# 添加 MinGW 支持
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using MinGW compiler...")
    # 确保启用 C++17 支持
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    # 添加链接选项，解决MySQL库与MinGW的兼容性问题
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# 修改 MySQL Connector/C++ 配置为使用MariaDB C Connector（更兼容MinGW）
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # 设置MariaDB Connector C路径（需要单独安装）
    # 注意：这里假设您已安装或将安装MariaDB C Connector
    set(MARIADB_DIR "C:/Program Files/MariaDB/MariaDB Connector C 64-bit")
    include_directories("${MARIADB_DIR}/include")
    link_directories("${MARIADB_DIR}/lib")
    
    # 可选：保留MySQL路径以便同时支持
    set(MYSQL_DIR "C:/Program Files/MySQL/MySQL Connector C++ 9.2")
    include_directories("${MYSQL_DIR}/include")
else()
    # MSVC 路径配置
    set(MYSQL_DIR "C:/Program Files/MySQL/MySQL Connector C++ 9.2")
    include_directories("${MYSQL_DIR}/include")
    link_directories("${MYSQL_DIR}/lib64/vs14")
endif()

set(TS_FILES firstDemo_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        success.cpp
        success.h
        success.ui
        fail.cpp
        fail.h
        fail.ui
        table.cpp
        table.h
        table.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(firstDemo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(firstDemo ${PROJECT_SOURCES})
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# 根据编译器类型选择不同的数据库连接库
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # MinGW 使用 MariaDB C Connector
    target_link_libraries(firstDemo PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        libmariadb
        # 如果需要SSL支持，可能还需要：
        # libssl
        # libcrypto
    )
else()
    # MSVC 使用 MySQL Connector C++
    find_library(MYSQLCPPCONN_LIB mysqlcppconn PATHS "${MYSQL_DIR}/lib64/vs14")
    find_library(MYSQLCPPCONN_STATIC_LIB mysqlcppconn-static PATHS "${MYSQL_DIR}/lib64/vs14")
    
    target_link_libraries(firstDemo PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        ${MYSQLCPPCONN_LIB}
        ${MYSQLCPPCONN_STATIC_LIB}
    )
endif()

set_target_properties(firstDemo PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS firstDemo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(firstDemo)
endif()
