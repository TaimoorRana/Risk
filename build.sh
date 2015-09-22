pushd build/osx
CMAKE_PREFIX_PATH=$(brew --prefix qt5) cmake ../../
popd
