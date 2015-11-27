set(LIBRARY_SOURCE_FILES
	ai/strategy.h ai/strategy.cpp
	ai/aggressive.h ai/aggressive.cpp
	ai/defensive.h ai/defensive.cpp
	ai/random.h ai/random.cpp
	continent.cpp continent.h
	country.cpp country.h
	debug.cpp debug.h
	graph_adt.cpp graph_adt.h
	game_modes.h
	game_driver.cpp game_driver.h
	game_state.cpp game_state.h
	librisk.cpp librisk.h
	observable.cpp observable.h observer.h
	player.cpp player.h
	risk_map.cpp risk_map.h
	war_referee.cpp war_referee.h
	computer_player.h computer_player.cpp
)

add_library(lib${PROJECT_NAME} STATIC ${LIBRARY_SOURCE_FILES})

set_target_properties(lib${PROJECT_NAME} PROPERTIES
	VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
	SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}"
)
