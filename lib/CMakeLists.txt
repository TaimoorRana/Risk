set(LIBRARY_SOURCE_FILES
	continent.cpp continent.h
	country.cpp country.h
	debug.cpp debug.h
	GraphADT.cpp GraphADT.h
	librisk.cpp librisk.h
	player.cpp player.h
	playerobserver.h
	playersubject.h
	playerview.cpp playerview.h
	risk_map.cpp risk_map.h
	warreferee.cpp warreferee.h
)

add_library(lib${PROJECT_NAME} STATIC ${LIBRARY_SOURCE_FILES})

set_target_properties(lib${PROJECT_NAME} PROPERTIES
	VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
	SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
)
