cmake_minimum_required(VERSION 3.7)
project(libConnect)


set(CMAKE_CXX_STANDARD 14)

#do not append lib to library name
set(CMAKE_STATIC_LIBRARY_PREFIX "")


set(SOURCE_FILES ConStandAloneConnection.cpp ConStandAloneConnection.h ConThread.cpp ConThread.h ConTCPReceiver.cpp ConTCPReceiver.h ConCallback.h ConSocket.h ConServer.cpp ConServer.h ConThread2.cpp ConThread2.h)
add_library(libConnect ${SOURCE_FILES})

#Add liblogger
include_directories(/home/pbeerken/source/pkg/include)
link_directories(/home/pbeerken/source/pkg/lib)
target_link_libraries(libConnect Log Utils)

#installation
file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION ~/source/pkg/include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION ~/source/pkg/lib)
add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")


######## Unit Tests ##############
add_subdirectory(GTest)

######## Test Apps ################
add_subdirectory(TestApps)
