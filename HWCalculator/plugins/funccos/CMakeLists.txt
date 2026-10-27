add_library(funccos MODULE cos.cpp)
target_include_directories(funccos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(funccos PROPERTIES PREFIX "" OUTPUT_NAME "funccos")