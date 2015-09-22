# Qt Creator
To get Qt Creator working with the CMake build system, do the following:
1. Install Qt Creator from http://www.qt.io/ide/
2. Open Qt Creator and select Preferences (or Tools > Options in Windows)
3. Go to Build & Run on the left, then the CMake tab on the far right
4. Add a new CMake location called "Homebrew" and *manually* enter /usr/local/opt/cmake/bin into the Path field (do not click "Choose...", as it will resolve the symlink and break if you ever upgrade cmake)
5. Press OK
6. Click to Open a project and select CMakeLists.txt from the Risk project
7. Run CMake
8. You're good to go! Remember to select the correct target (GUI vs CLI) when building.
