include_directories(${PROJECT_SOURCE_DIR})
set(APP_SRC 源.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stltest ${APP_SRC})