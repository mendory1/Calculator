add_library(funcdeg MODULE deg.cpp)
target_include_directories(funcdeg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(funcdeg PROPERTIES PREFIX "" OUTPUT_NAME "funcdeg")