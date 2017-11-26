cmake_minimum_required(VERSION 2.8.11)

project(ScalaSimulator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets 3DCore 3DExtras 3DRender 3DInput)

set(INCLUDE_DIR include)
set(HEADERS
    ${INCLUDE_DIR}/ScalaMoveController.h
    ${INCLUDE_DIR}/SimulatorSceneEntity.h
    ${INCLUDE_DIR}/RayCastBuffer.h
    ${INCLUDE_DIR}/RayCastEffect.h
    ${INCLUDE_DIR}/SimulatorRenderer.h
    ${INCLUDE_DIR}/ComputeEffect.h
    ${INCLUDE_DIR}/ComputeEntity.h
    ${INCLUDE_DIR}/ComputeRenderBrunch.h
    ${INCLUDE_DIR}/ScalaEntity.h
   )

include_directories(${INCLUDE_DIR})

set(SOURCE_DIR src)
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/ScalaMoveController.cpp
    ${SOURCE_DIR}/SimulatorSceneEntity.cpp
    ${SOURCE_DIR}/RayCastBuffer.cpp
    ${SOURCE_DIR}/RayCastEffect.cpp
    ${SOURCE_DIR}/SimulatorRenderer.cpp
    ${SOURCE_DIR}/ComputeEffect.cpp
    ${SOURCE_DIR}/ComputeEntity.cpp
    ${SOURCE_DIR}/ComputeRenderBrunch.cpp
    ${SOURCE_DIR}/ScalaEntity.cpp
   )

set(RESOURCE_DIR resources)
set(RESOURCES
    ${RESOURCE_DIR}/ScalaSimulator.qrc
   )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES})

target_link_libraries(${PROJECT_NAME}
                        Qt5::Core
                        Qt5::Gui
                        Qt5::Widgets
                        Qt5::3DCore
                        Qt5::3DExtras
                        Qt5::3DRender
                        Qt5::3DInput
                      )
