cmake_minimum_required(VERSION 3.7)
project(libConnect)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES ConStandAloneConnection.cpp ConStandAloneConnection.h ConThread.cpp ConThread.h ConTCPReceiver.cpp ConTCPReceiver.h ConConnectionCallback.h)
add_library(libConnect ${SOURCE_FILES})

#Add liblogger
include_directories(/home/pbeerken/source/pkg/include)
link_directories(/home/pbeerken/source/pkg/lib)
target_link_libraries(libConnect libLog)

file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION ~/source/pkg/include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION ~/source/pkg/lib)

add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")


######## Unit Tests ##############
set (GTEST_ROOT /usr)
find_package(GTest REQUIRED)
set(UnitTest_SOURCE_FILES GTest/Main.cpp GTest/ConThreadTest.cpp)
add_executable(UnitTest ${UnitTest_SOURCE_FILES})
#target_link_libraries(UnitTest ClionLibWithUnitTest)
target_link_libraries(UnitTest GTest::GTest GTest::Main)

######## Test Apps ################
add_executable (ConThreadApp TestApps/ConThreadTestApp.cpp)
add_executable(ConSimpleServer TestApps/ConSimpleServer.cpp)
add_executable(ConStandAloneClient TestApps/ConStandAloneTestClient.cpp)
target_link_libraries(ConStandAloneClient libConnect pthread)
