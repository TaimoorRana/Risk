# Qt Creator
To get Qt Creator working with the CMake build system, do the following:
1. Install Qt Creator from http://www.qt.io/ide/
2. Open Qt Creator and select Preferences (or Tools > Options in Windows)
3. Go to Build & Run on the left, then the CMake tab on the far right
4. Add a new CMake location called "Homebrew" and click "Choose..." for the Path entry
5. Browse to /usr/local/opt/cmake/bin/cmake and press OK (the Homebrew entry in the list of CMake installations should now be bold)
6. *Manually* change the Path field to /usr/local/opt/cmake/bin (the text should change to black when typed correctly
5. Press OK
6. Click to Open a project and select CMakeLists.txt from the Risk project
7. Change the build directory from /path/to/repo/Risk-build to /path/to/repo/Risk/build/qtc
7. Click "Run CMake"
8. You're good to go! Remember to select the correct target (GUI vs CLI) when building.
