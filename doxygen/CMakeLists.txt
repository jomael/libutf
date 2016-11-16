cmake_minimum_required(VERSION 2.6)

find_package(Doxygen)
if (DOXYGEN_EXECUTABLE)
	add_custom_target("doxygen" ALL
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating doxygen files")
	if (WIN32)
		install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/html"
			DESTINATION "documentation")
	endif (WIN32)
	if (UNIX)
		install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/man"
			DESTINATION "share")
	endif (UNIX)
endif (DOXYGEN_EXECUTABLE)

