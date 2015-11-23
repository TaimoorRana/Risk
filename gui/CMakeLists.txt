# Include qt basic functions
include(QtCommon)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

set(GUI_SOURCE_FILES
	enum_tooltype.h
	country_name_dialog.cpp country_name_dialog.h country_name_dialog.ui
	main.cpp
	mainscreen.cpp mainscreen.h mainscreen.ui
	gameboardview.cpp gameboardview.h
	game_error_dialog.cpp game_error_dialog.h game_error_dialog.ui
	map_editor.cpp map_editor.h map_editor.ui
	map_scene.cpp map_scene.h
	map_renderer.cpp map_renderer.h
	playerinfowidget.cpp playerinfowidget.h playerinfowidget.ui
	fortify_dialog.cpp fortify_dialog.h fortify_dialog.ui
	playernamedialog.cpp playernamedialog.h playernamedialog.ui
	qgraphics_country_item.cpp qgraphics_country_item.h
	qgraphics_country_edge_item.cpp qgraphics_country_edge_item.h
)

set(GUI_RESOURCE_FILES
	style_sheet.qss
	../assets/risk.qrc
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/style_sheet.qss DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

IF (APPLE)
	add_project_meta(GUI_META_FILES)
ENDIF (APPLE)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
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

add_custom_target(Qt5CopyBinaries
	# todo: check if debug and release folder exist
	# debug version
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGLd.dll          ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2d.dll       ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Cored.dll         ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Guid.dll          ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Declaratived.dll  ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Networkd.dll      ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGLd.dll       ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Scriptd.dll       ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sqld.dll          ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgetsd.dll      ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xmld.dll          ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatternsd.dll  ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuin54.dll          ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuuc54.dll          ${CMAKE_CURRENT_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icudt54.dll          ${CMAKE_CURRENT_BINARY_DIR}/Debug

	# release version
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGL.dll           ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2.dll        ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Core.dll          ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Gui.dll           ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Declarative.dll   ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Network.dll       ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGL.dll        ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Script.dll        ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sql.dll           ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgets.dll       ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xml.dll           ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatterns.dll   ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuin54.dll          ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuuc54.dll          ${CMAKE_CURRENT_BINARY_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icudt54.dll          ${CMAKE_CURRENT_BINARY_DIR}/Release

	# Output Message
	COMMENT "Copying Qt binaries from '${Qt5Core_DIR}/../../bin/' to '${CMAKE_BINARY_DIR}'" VERBATIM
)

IF (WIN32)
	add_dependencies(${PROJECT_NAME}-gui Qt5CopyBinaries)
ENDIF (WIN32)
