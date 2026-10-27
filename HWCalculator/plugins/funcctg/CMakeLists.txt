add_library(funcctg MODULE ctg.cpp)
target_include_directories(funcctg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(funcctg PROPERTIES PREFIX "" OUTPUT_NAME "funcctg")