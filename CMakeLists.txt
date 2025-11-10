cmake_minimum_required (VERSION 3.8)
project ("kex")

add_executable (kex "main.cpp" "kex.cpp" )

target_compile_definitions(kex 
    PRIVATE 
        UNICODE
        _UNICODE
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET kex PROPERTY CXX_STANDARD 23)
endif()
