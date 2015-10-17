set(LIBRARY_SOURCE_FILES
	debug.cpp debug.h
	GraphADT.cpp GraphADT.h
	continent.cpp continent.h
	country.cpp country.h
	map.cpp map.h
	librisk.cpp librisk.h
)

add_library(lib${PROJECT_NAME} STATIC ${LIBRARY_SOURCE_FILES})

set_target_properties(lib${PROJECT_NAME} PROPERTIES
	VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
	SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
)
