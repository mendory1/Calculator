cmake_minimum_required(VERSION 3.16)
project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(calc
    main.cpp
    Calculator.cpp
    Operations.cpp
    PluginManager.cpp
)

target_include_directories(calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(plugins/funcsin)
add_subdirectory(plugins/funccos)
add_subdirectory(plugins/funcln)
add_subdirectory(plugins/funcdeg)
add_subdirectory(plugins/functg)
add_subdirectory(plugins/funcctg)
add_subdirectory(plugins/funcsqrt)
add_subdirectory(plugins/funcpow)

add_custom_target(copy_plugins ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:funcsin> $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:funccos> $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:funcln> $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:funcdeg> $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:functg> $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:funcctg> $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:funcsqrt> $<TARGET_FILE_DIR:calc>/plugins
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:funcpow> $<TARGET_FILE_DIR:calc>/plugins
    DEPENDS funcsin funccos funcln funcdeg functg funcctg funcsqrt funcpow calc
    COMMENT "Копируются плагины в <bin>/plugins"
)