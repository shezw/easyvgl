# SRC directory

if (NOT LVGL_INCLUDE_DIR)
    set(LVGL_INCLUDE_DIR "${PROJ_DIR}/include")
endif ()

include_directories(
        ${LVGL_INCLUDE_DIR}
        ${PROJ_DIR}/include
)

include_directories(
        modules
        ui-kit
        utils
)