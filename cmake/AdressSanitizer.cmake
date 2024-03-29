function(add_adress_sanitizer_flags)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options("-fno-omit-frame-pointer")
        add_link_options("fno-omit-frame-pointer")

        add_compile_options("-fsanitize=address")
        add_link_options("-fsanitize=address")
        
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
            add_compile_options("/fsanitize=address")
    else()
        message(STATUS "Sanitizer not supported in this environment!")
    endif()
endfunction(add_sanitizer_flags)
