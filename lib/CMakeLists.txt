set(LIBRARY_SOURCE_FILES
	card.cpp card.h
	continent.cpp continent.h
	country.cpp country.h
        countrylost.cpp countrylost.h
        debug.cpp debug.h
        dices.cpp dices.h
        gameBoard.cpp gameBoard.h
	GraphADT.cpp GraphADT.h
	librisk.cpp librisk.h
	map.cpp map.h
	player.cpp player.h
        warreferee.cpp warreferee.h
)

add_library(lib${PROJECT_NAME} STATIC ${LIBRARY_SOURCE_FILES})

set_target_properties(lib${PROJECT_NAME} PROPERTIES
	VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
	SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
)
