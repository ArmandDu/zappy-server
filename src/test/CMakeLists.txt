project(Test)

include(CTest)
enable_testing()

#set(gtest_disable_pthreads on) #needed in MinGW
include(./DownloadProject.cmake)
download_project(
        PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        UPDATE_DISCONNECTED 1
)


set(test_SRCS
        world/RectTest.cpp
        parser/ParserTest.cpp
        game/GameTest_GetRelativePosition.cpp
        game/GameTest_FindEntitiesTest.cpp
        player/PlayerTest.cpp
        player/actions/IncantationTest.cpp
        player/actions/BroadcastTest.cpp
        player/actions/ExpelTest.cpp)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests gtest gmock zappy_game tcp_server)
add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.