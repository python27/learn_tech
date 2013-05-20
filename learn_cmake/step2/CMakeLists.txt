CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Tutorial)

SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

option(USE_MYMATH "Use tutorial provided math func" on)

CONFIGURE_FILE(
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_BINARY_DIR}/TutorialConfig.h"
    )

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

if (USE_MYMATH)
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/MathFunctions")
    ADD_SUBDIRECTORY(MathFunctions)
    SET (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

ADD_EXECUTABLE(Tutorial tutorial.cxx)
TARGET_LINK_LIBRARIES(Tutorial ${EXTRA_LIBS})
