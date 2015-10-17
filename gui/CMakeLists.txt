# Include qt basic functions
include(QtCommon)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

set(GUI_SOURCE_FILES
	main.cpp
	risk.cpp 
	risk.h
	myplayer.cpp
	myplayer.h
        player.h
        player.cpp
        soldier.h
        soldier.cpp
        country.h
        country.cpp
        card.h
        card.cpp
)

set(GUI_RESOURCE_FILES
	#risk.qrc
)

IF (APPLE)
	add_project_meta(GUI_META_FILES)
ENDIF (APPLE)

find_package(Qt5Widgets REQUIRED)
include_directories("${CMAKE_SOURCE_DIR}/lib")

add_executable(${PROJECT_NAME}-gui ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
	${GUI_SOURCE_FILES} ${GUI_META_FILES} ${GUI_RESOURCE_FILES}
)

fix_win_compiler(${PROJECT_NAME}-gui)

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME}-gui Qt5::Widgets)
target_link_libraries(${PROJECT_NAME}-gui lib${PROJECT_NAME})

if (APPLE)
	set_target_properties(${PROJECT_NAME}-gui PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/resources/MacOSXBundleInfo.plist.in)
endif (APPLE)
