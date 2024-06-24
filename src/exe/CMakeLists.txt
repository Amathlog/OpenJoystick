include_directories("${OpenJoystick_SOURCE_DIR}/include" PUBLIC)

file(GLOB_RECURSE EXE_SRC_FILES
    "${MAIN_FOLDER}/exe/*.cpp"
)

add_executable(OpenJoystickExe ${EXE_SRC_FILES})
target_link_libraries(OpenJoystickExe OpenJoystickLib)
set_target_properties(OpenJoystickExe PROPERTIES FOLDER ${MAIN_FOLDER})