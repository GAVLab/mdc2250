cmake_minimum_required(VERSION 2.8.3)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(mdc2250)

find_package(catkin REQUIRED COMPONENTS
  serial
  serial_utils
)

find_package(cmake_modules REQUIRED)

catkin_package(
    LIBRARIES ${PROJECT_NAME}
    INCLUDE_DIRS include
    CATKIN_DEPENDS serial serial_utils
    DEPENDS system_lib
)

## Sources
set(mdc2250_SRCS
    src/mdc2250.cc
    include/mdc2250/decode.h
    include/mdc2250/mdc2250.h
)



add_library(${PROJECT_NAME} ${mdc2250_SRCS} ${catkin_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

## Uncomment for example
add_executable(mdc2250_example examples/mdc2250_example.cc)
add_dependencies(mdc2250_example ${PROJECT_NAME})
target_link_libraries(mdc2250_example ${PROJECT_NAME})

## Include headers
include_directories(
	include
	include/${PROJECT_NAME}
	${catkin_INCLUDE_DIRS}
)

## Install executable
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

## Install headers
install(FILES include/mdc2250/mdc2250.h include/mdc2250/decode.h
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/mdc2250)

## Tests
# if(CATKIN_ENABLE_TESTING)
#     add_subdirectory(tests)
# endif()