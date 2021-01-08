cmake_minimum_required( VERSION 2.8 )

project( test-iostream )

set( SOURCES
    implementation/main.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)
