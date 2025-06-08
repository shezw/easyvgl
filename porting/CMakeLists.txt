include(${PROJ_DIR}/porting/macro.cmake)

include(${PORTING_DIR}/porting.cmake)

set(PORTING_SRCS
    ${PORTING_SRCS}
    ${PROJ_DIR}/porting/common/mutex.c
)
