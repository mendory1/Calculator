add_library(functg MODULE tg.cpp)
target_include_directories(functg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set_target_properties(functg PROPERTIES PREFIX "" OUTPUT_NAME "functg")