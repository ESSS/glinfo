#find_package(GLEW REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
find_package(Qt5 COMPONENTS Core Gui OpenGL REQUIRED)
include_directories(
    ${Qt5Gui_INCLUDE_DIRS}
)

add_executable(
    glinfo
    main.cpp
)

target_link_libraries (
    glinfo
    ${ALL_LIBS}
    PUBLIC
        Qt5::Core
        Qt5::Gui
)
include(Install)
install_target(glinfo)
#install (TARGETS glinfo DESTINATION bin)

