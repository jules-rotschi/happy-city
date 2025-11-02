cmake_minimum_required(VERSION 3.16)

project(HappyCity VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SRC_DIR src)

set (SOURCES
  ${SRC_DIR}/Main.cpp
  ${SRC_DIR}/AIController.cpp
  ${SRC_DIR}/Card.cpp
  ${SRC_DIR}/City.cpp
  ${SRC_DIR}/DeckOfCards.cpp
  ${SRC_DIR}/Game.cpp
  ${SRC_DIR}/Player.cpp
  ${SRC_DIR}/RealController.cpp
  ${SRC_DIR}/SetOfCards.cpp
)

set (HEADERS
  ${SRC_DIR}/AIController.h
  ${SRC_DIR}/Card.h
  ${SRC_DIR}/CardType.h
  ${SRC_DIR}/City.h
  ${SRC_DIR}/DeckOfCards.h
  ${SRC_DIR}/Game.h
  ${SRC_DIR}/Input.h
  ${SRC_DIR}/Player.h
  ${SRC_DIR}/PlayerController.h
  ${SRC_DIR}/Print.h
  ${SRC_DIR}/RealController.h
  ${SRC_DIR}/SetOfCards.h
)

add_executable (HappyCity ${SOURCES} ${HEADERS})

target_include_directories(HappyCity PRIVATE ${SRC_DIR})