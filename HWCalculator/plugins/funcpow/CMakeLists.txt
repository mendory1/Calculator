add_library(funcpow MODULE pow.cpp)
target_include_directories(funcpow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(funcpow PROPERTIES PREFIX "" OUTPUT_NAME "funcpow")