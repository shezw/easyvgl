
add_executable(simple-demo simple-demo.c)

if (CC_ENABLE_CURL)
    add_executable(curl-http curl-http.c)
endif ()

target_link_libraries(simple-demo PRIVATE easyVGL)