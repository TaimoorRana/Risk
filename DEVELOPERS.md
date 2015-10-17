# Qt Creator
To get Qt Creator working with the CMake build system, do the following:
1. Install Qt Creator from http://www.qt.io/ide/
2. Open Qt Creator and select Preferences (or Tools > Options in Windows)
3. Go to Build & Run on the left, then the CMake tab on the far right
4. Add a new CMake location called "Homebrew" and click "Choose..." for the Path entry
5. Browse to /usr/local/opt/cmake/bin/cmake and press OK (the Homebrew entry in the list of CMake installations should now be bold)
6. *Manually* change the Path field to /usr/local/opt/cmake/bin (the text should change to black when typed correctly
6. Switch to the Qt Versions tab and press Add...
5. Browse to /usr/local/opt/qt5/bin/qmake
6. Press OK
7. Re-open Preferences (or Tools > Options in Windows) and switch to the Kits tab
8. Edit the default kit ("Desktop") and choose the now available Qt 5 version
9. Click to Open a project and select CMakeLists.txt from the Risk project
10. Change the build directory from /path/to/repo/Risk-build to /path/to/repo/Risk/build/qtc
11. Click "Run CMake"
12. You're good to go! Remember to select the correct target (GUI vs CLI) when building.
