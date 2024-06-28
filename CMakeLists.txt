cmake_minimum_required(VERSION 3.27)

project(eisgenerator VERSION "1.0")

if(SKBUILD)
	execute_process(
		COMMAND "${PYTHON_EXECUTABLE}" -c
		"import pybind11; print(pybind11.get_cmake_dir())"
		OUTPUT_VARIABLE _tmp_dir
		OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT)
	list(APPEND CMAKE_PREFIX_PATH "${_tmp_dir}")
endif()

find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(eisgenerator)

pybind11_add_module(_core MODULE src/main.cpp)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
add_dependencies(_core eisgenerator_static)
target_link_libraries(_core PUBLIC eisgenerator_static tbb)
install(TARGETS _core DESTINATION .)



