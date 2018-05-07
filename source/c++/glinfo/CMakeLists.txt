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

if("$ENV{CONDA_BUILD}" STREQUAL "1")
    install (TARGETS glinfo DESTINATION bin)
else("$ENV{CONDA_BUILD}" STREQUAL "1")
    include(Install)
    install_target(glinfo)
endif()

