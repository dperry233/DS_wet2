set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
cmake_minimum_required (VERSION 2.6)
project (DS_Wet2 CXX)
add_executable(DS_Wet2 MagiHash.h MagiHash.cpp test.cpp forTest.h animalUnionFind.h animalUnionFind.cpp avlTree.h library2.cpp magicManager.h RAVLTree.h RAVLNode.h)