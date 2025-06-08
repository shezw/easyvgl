# This is a cmake file to check if the options # are set correctly for the project

# check PROJ_DIR is set

if(NOT DEFINED PROJ_DIR)
  message(FATAL_ERROR "PROJ_DIR is not set. Please set it to the path of your project directory.")
endif()

# check CC_PLATFORM
set(PROJ_VALID_PLATFORMS "linux" "windows" "mac" "wasm" "linux-fb" "linux-sdl" "linux-x11" "linux-wayland")

if(NOT DEFINED CC_PLATFORM)
  message(FATAL_ERROR "CC_PLATFORM is not set. Please set it to the platform you are targeting (e.g., 'linux', 'windows', 'mac').")

elseif(NOT CC_PLATFORM IN_LIST PROJ_VALID_PLATFORMS)
    message(FATAL_ERROR "CC_PLATFORM '${CC_PLATFORM}' is not a valid platform. Valid platforms are: ${PROJ_VALID_PLATFORMS}.")
endif()

message(STATUS "PROJ_DIR is set to: ${PROJ_DIR}")
message(STATUS "CC_PLATFORM is set to: ${CC_PLATFORM}")
