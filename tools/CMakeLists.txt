set(LIBRARY_SOURCES "AssetManager.cpp" "InputManager.cpp" "Camera.cpp")
set(LIBRARY_HEADERS "AssetManager.hpp" "InputManager.hpp" "Camera.hpp")

add_library(
	${LIBRARY_TOOLS} STATIC
	${LIBRARY_SOURCES}
	${LIBRARY_HEADERS}
)

target_include_directories(
	${LIBRARY_TOOLS} PUBLIC
	"./"
)

target_link_libraries(
	${LIBRARY_TOOLS} PUBLIC
	sfml-graphics
	${LIBRARY_GRAPH} 
)

if(ENABLE_ALL_WARNINGS)
	TARGET_SET_WARNINGS(${LIBRARY_TOOLS} on)
endif()

