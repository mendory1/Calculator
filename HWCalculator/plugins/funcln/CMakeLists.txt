add_library(funcln MODULE ln.cpp)
target_include_directories(funcln PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(funcln PROPERTIES PREFIX "" OUTPUT_NAME "funcln")