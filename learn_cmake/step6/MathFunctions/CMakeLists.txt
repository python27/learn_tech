INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(MakeTable MakeTable.cxx)
ADD_CUSTOM_COMMAND (
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable) 

ADD_LIBRARY(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)
INSTALL (TARGETS MathFunctions DESTINATION bin)
INSTALL (FILES MathFunctions.h DESTINATION include)
