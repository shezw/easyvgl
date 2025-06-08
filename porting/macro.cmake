include_directories(${LOCAL_DIR}/include)

include_directories(
        ${PROJ_DIR}
        ${PROJ_DIR}/porting
        ${PROJ_DIR}/porting/api
)

if (CC_PLATFORM STREQUAL x86 OR CC_PLATFORM STREQUAL x86_64)
    if (USE_X11)
        add_compile_definitions(USE_X11=1)
    else()
        add_compile_definitions(USE_SDL=1)
    endif ()
endif ()

if (CC_PLATFORM STREQUAL mac)
    add_compile_definitions(USE_SDL=1)
endif ()

if (CC_PLATFORM STREQUAL wasm)
    add_compile_definitions(USE_SDL=1)
endif ()

set(PORTING_DIR ${PROJ_DIR}/porting/${CC_PLATFORM})

link_libraries(lvgl cjson)