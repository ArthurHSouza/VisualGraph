set(LIBRARY_SOURCES "NodeCircle.cpp" "EdgeShape.cpp" "VisualObject.cpp")
set(LIBRARY_HEADERS "NodeCircle.hpp" "EdgeShape.hpp" "VisualObject.hpp")

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

if(ENABLE_ALL_WARNINGS)
	TARGET_SET_WARNINGS(${LIBRARY_GRAPH} on)
endif()
