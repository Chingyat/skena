cmake_minimum_required(VERSION 3.8)

project(Skena CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(Readline REQUIRED)

add_subdirectory(source bin)

include(GNUInstallDirs)

include(GenerateExportHeader)

include(CMakePackageConfigHelpers)

generate_export_header(stdlib)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/skena-config-version.cmake"
	VERSION 0.1.0
	COMPATIBILITY AnyNewerVersion)


install(TARGETS skena stdlib EXPORT skena
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/skena")

export(EXPORT skena FILE "${CMAKE_CURRENT_BINARY_DIR}/skena-targets.cmake" NAMESPACE skena::)

install(EXPORT skena NAMESPACE skena:: DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/skena" FILE skena-targets.cmake)

install(FILES
	cmake/skena-config.cmake
	"${CMAKE_CURRENT_BINARY_DIR}/skena-config-version.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/skena")
