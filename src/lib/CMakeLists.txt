include_directories("${OpenJoystick_SOURCE_DIR}/include" PUBLIC)

file(GLOB_RECURSE SRC_FILES
    "${MAIN_FOLDER}/lib/*.cpp"
)

add_library(OpenJoystickLib ${SRC_FILES})
set_target_properties(OpenJoystickLib PROPERTIES FOLDER ${MAIN_FOLDER})