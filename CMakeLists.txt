cmake_minimum_required(VERSION 3.0)

project(risc_v_simulation_cpu)

set(SYSTEMC_HOME /home/rayane/systemc/install)
set(SYSTEMC_INCLUDE_DIR ${SYSTEMC_HOME}/include)
set(SYSTEMC_LIBRARY_DIR ${SYSTEMC_HOME}/lib)

add_executable(risc_v_simulation_cpu 
    src/main.cpp
)

target_include_directories(risc_v_simulation_cpu PRIVATE ${SYSTEMC_INCLUDE_DIR})
target_link_libraries(risc_v_simulation_cpu ${SYSTEMC_LIBRARY_DIR}/libsystemc.so)
target_include_directories(risc_v_simulation_cpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
