set(LIBRARY_SOURCES "NodeCircle.cpp" "EdgeShape.cpp" "VisualText.cpp" "SelectableVisualObject.cpp" "VisualObject.cpp")
set(LIBRARY_HEADERS "NodeCircle.hpp" "EdgeShape.hpp" "VisualText.hpp" "SelectableVisualObject.hpp" "VisualObject.hpp")

add_library(
	${LIBRARY_VISUAL} STATIC
	${LIBRARY_SOURCES}
	${LIBRARY_HEADERS}
)

target_include_directories(
	${LIBRARY_VISUAL} PUBLIC
	"./"
)

target_link_libraries(
	${LIBRARY_VISUAL} PUBLIC
	sfml-graphics
	${LIBRARY_TOOLS}
	${LIBRARY_GRAPH}
)

if(ENABLE_ALL_WARNINGS)
	TARGET_SET_WARNINGS(${LIBRARY_VISUAL} on)
endif()
