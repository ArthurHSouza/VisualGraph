set(LIBRARY_SOURCES "Graph.cpp" "Heap.cpp")
set(LIBRARY_HEADERS "Graph.hpp" "Heap.hpp")

add_library(
	${LIBRARY_GRAPH} STATIC
	${LIBRARY_SOURCES}
	${LIBRARY_HEADERS}
)

target_include_directories(
	${LIBRARY_GRAPH} PUBLIC
	"./"
)

if(ENABLE_ALL_WARNINGS)
	TARGET_SET_WARNINGS(${LIBRARY_GRAPH} on)
endif()
