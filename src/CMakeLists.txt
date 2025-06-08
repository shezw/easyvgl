# SRC directory

if (NOT LVGL_INCLUDE_DIR)
    set(LVGL_INCLUDE_DIR "${PROJ_DIR}/include")
endif ()

include_directories(
        ${LVGL_INCLUDE_DIR}
        ${PROJ_DIR}/include
)

include_directories(
        ${PROJ_DIR}/src
        ${PROJ_DIR}/src/modules
        ${PROJ_DIR}/src/uikit
        ${PROJ_DIR}/src/utils
        ${PROJ_DIR}/src/styles
)

# SRC files
file(GLOB_RECURSE EVG_SRC_FILES
        "${PROJ_DIR}/src/utils/*.c"
        "${PROJ_DIR}/src/uikit/*.c"
        "${PROJ_DIR}/src/modules/*.c"
        "${PROJ_DIR}/src/styles/.c"
)

add_library(easyvgl STATIC
        ${EVG_SRC_FILES}
)