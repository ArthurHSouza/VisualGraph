set(EXE_SOURCE "main.cpp")
set(EXE_INCLUDES "./")
add_executable(
	${EXECUTABLE_NAME}
	${EXE_SOURCE}
)

target_include_directories(
	${EXECUTABLE_NAME} PUBLIC
    ${EXE_INCLUDES}
)

target_link_libraries(
	${EXECUTABLE_NAME} PUBLIC
	${LIBRARY_NAME}
	sfml-graphics
)

if(WIN32)
    add_custom_command(
        TARGET ${EXECUTABLE_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        VERBATIM)

endif()
 
install(TARGETS ${EXECUTABLE_NAME})