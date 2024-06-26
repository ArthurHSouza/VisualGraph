﻿cmake_minimum_required (VERSION 3.8)

project ("VisualGraph" VERSION 1.0.0 DESCRIPTION "Think on this later" LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXECUTABLE_NAME ${PROJECT_NAME})
set(LIBRARY_TOOLS "tools")
set(LIBRARY_GRAPH "graph")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
option(ENABLE_ALL_WARNINGS ON)
option(ENABLE_ADRESS_SANITIZER OFF)

if(ENABLE_ALL_WARNINGS)
	include(Warnings)
endif()

if(ENABLE_ADRESS_SANITIZER)
	include(AdressSanitizer)
	add_adress_sanitizer_flags()
endif()

if (POLICY CMP0141 AND NOT ENABLE_ADRESS_SANITIZER)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SFML)

file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(tools)
add_subdirectory(graph)
add_subdirectory(app)

