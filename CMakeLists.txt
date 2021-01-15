CMAKE_MINIMUM_REQUIRED (VERSION 3.16)
PROJECT(uise-desktop VERSION 0.0.1 LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)

FIND_PACKAGE(Qt6 COMPONENTS Widgets REQUIRED)

IF (UISE_DESKTOP_STATIC)
    ADD_LIBRARY(${PROJECT_NAME} STATIC)
ELSE (UISE_DESKTOP_STATIC)    
    ADD_LIBRARY(${PROJECT_NAME} SHARED)
ENDIF(UISE_DESKTOP_STATIC)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC Qt6::Widgets)

SET (HEADERS
    include/uise/desktop/version.hpp
)
