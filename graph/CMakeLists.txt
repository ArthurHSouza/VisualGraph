set(LIBRARY_SOURCES "NodeCircle.cpp")
set(LIBRARY_HEADERS "NodeCircle.hpp")

add_library(
	${LIBRARY_GRAPH} STATIC
	${LIBRARY_SOURCES}
	${LIBRARY_HEADERS}
)

target_include_directories(
	${LIBRARY_GRAPH} PUBLIC
	"./"
)

target_link_libraries(
	${LIBRARY_GRAPH} PUBLIC
	sfml-graphics
	${LIBRARY_TOOLS}
)

