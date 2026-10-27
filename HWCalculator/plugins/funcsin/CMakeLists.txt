add_library(funcsin MODULE sin.cpp)
target_include_directories(funcsin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(funcsin PROPERTIES PREFIX "" OUTPUT_NAME "funcsin")