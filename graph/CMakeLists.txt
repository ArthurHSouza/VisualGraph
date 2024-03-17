set(LIBRARY_SOURCES "test.cpp")
set(LIBRARY_HEADERS "test.hpp")

add_library(
	${LIBRARY_NAME} STATIC
	${LIBRARY_SOURCES}
	${LIBRARY_HEADERS}
)

target_link_libraries(
	${LIBRARY_NAME} PUBLIC
	sfml-graphics
)