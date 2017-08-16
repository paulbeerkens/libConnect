set(GTEST_ROOT /usr)
find_package(GTest REQUIRED)
set(UnitTest_SOURCE_FILES Main.cpp ConThreadTest.cpp)

add_executable(UnitTest ${UnitTest_SOURCE_FILES})
target_link_libraries(UnitTest GTest::GTest GTest::Main)