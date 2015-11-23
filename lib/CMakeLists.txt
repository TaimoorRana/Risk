set(LIBRARY_SOURCE_FILES
	continent.cpp continent.h
	country.cpp country.h
	debug.cpp debug.h
	graph_adt.cpp graph_adt.h
	game_driver.cpp game_driver.h
	game_state.cpp game_state.h
	librisk.cpp librisk.h
	observable.cpp observable.h observer.h
	player.cpp player.h
	player_view.cpp player_view.h
	risk_map.cpp risk_map.h
	war_referee.cpp war_referee.h
)

add_library(lib${PROJECT_NAME} STATIC ${LIBRARY_SOURCE_FILES})

set_target_properties(lib${PROJECT_NAME} PROPERTIES
	VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
	SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
)
