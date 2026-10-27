add_library(funcsqrt MODULE sqrt.cpp)
target_include_directories(funcsqrt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(funcsqrt PROPERTIES PREFIX "" OUTPUT_NAME "funcsqrt")