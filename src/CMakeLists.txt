
set(TAGLIB 
  "cpp.cc" 
  "print.cc"
  "foreach.cc"
  "if.cc"
  "else.cc"
  "include.cc"
  "page.cc"
  "root.cc"
  "tag.cc"
  "tagfactory.cc"
  )

set(CSPLIB
  "parser.cc"
  "POPEN1.cpp"
  "regex.cc"
)

set(CSP
  "main.cc"
  )

file(GLOB HEADERS "*.hh")

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
  message(STATUS "GCC detected, enabling pedantic mode and warnings")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

# Generate config.h
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Libraries

# An example of how to use a library. You'll need FindExampleLibrary.cmake for this to work
# Put that file in trunk/cmake/Modules/ and also look inside the file for further instructions.
#find_package(ExampleLibrary REQUIRED)
#include_directories(${ExampleLibrary_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${ExampleLibrary_LIBRARIES})

# Assumes the project generates only one executable. If you need more, you'll need to alter
# the script and replace ${PROJECT_SHORT_NAME} by executable name.
add_library(taglib SHARED ${TAGLIB})
add_library(csplib SHARED ${CSPLIB})
add_executable("${PROJECT_SHORT_NAME}" ${CSP})
target_link_libraries("${PROJECT_SHORT_NAME}" taglib csplib ${LIBS})
install(TARGETS "${PROJECT_SHORT_NAME}" DESTINATION bin)
install(TARGETS taglib DESTINATION lib)
install(TARGETS csplib DESTINATION lib)

