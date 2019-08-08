cmake_minimum_required(VERSION 3.10)

project(janucaria-boost-python-example)

include(ExternalProject)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

ExternalProject_Add(Boost_Python
  PREFIX Boost
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/externs/boost
  CONFIGURE_COMMAND ./bootstrap.sh
    --with-libraries=python
    --with-python=${Python3_EXECUTABLE}
  BUILD_COMMAND ./b2 install
    --prefix=${CMAKE_SOURCE_DIR}/install
    variant=release
    link=static
    -d0
    -j8
  INSTALL_COMMAND ""
  BUILD_IN_SOURCE 1
)

set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/install/lib)
set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/install/include/boost)
set(Boost_LIBRARIES -lboost_python36 -lboost_numpy36)

add_library(janucaria-python src/hello_world.cpp)
add_dependencies(janucaria-python Boost_Python)
target_link_libraries(janucaria-python PUBLIC ${Boost_LIBRARIES} Python3::Python)
target_include_directories(janucaria-python PUBLIC ${Boost_INCLUDE_DIR})
target_link_directories(janucaria-python PUBLIC ${Boost_LIBRARY_DIR})
set_target_properties(janucaria-python PROPERTIES PREFIX "")
set_target_properties(janucaria-python PROPERTIES OUTPUT_NAME "janucaria")
set_target_properties(janucaria-python PROPERTIES SUFFIX ".so")
target_compile_definitions(janucaria-python PUBLIC BOOST_PYTHON_STATIC_LIB)
# set_property(TARGET janucaria-python PROPERTY POSITION_INDEPENDENT_CODE ON)
add_custom_command(TARGET janucaria-python
  POST_BUILD
  COMMAND touch __init__.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
)

