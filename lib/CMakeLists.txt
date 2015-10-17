set(LIBRARY_SOURCE_FILES
<<<<<<< HEAD
	librisk.cpp
	GraphADT.cpp
        risk_map.cpp
=======
	card.cpp card.h
	continent.cpp continent.h
	country.cpp country.h
	debug.cpp debug.h
	GraphADT.cpp GraphADT.h
	librisk.cpp librisk.h
	player.cpp player.h
>>>>>>> a53aafe9d2f22e3aa9152d712d1290b5f75b6802
)

add_library(lib${PROJECT_NAME} STATIC ${LIBRARY_SOURCE_FILES})

set_target_properties(lib${PROJECT_NAME} PROPERTIES
	VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
	SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
)
