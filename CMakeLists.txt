CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(OpenTickDatabase)
    
set (CTEST_PROJECT_NAME "OpenTickDatabase")
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "-g3 -fno-inline -O0 -Wall -DQS_LOG_LINE_NUMBERS")

# BOOST Handling
set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_MULTITHREADED     ON)
FIND_PACKAGE(Boost COMPONENTS date_time REQUIRED)
MESSAGE("Boost information:") 
MESSAGE("  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}") 
MESSAGE("  Boost_LIBRARIES: ${Boost_LIBRARIES}") 
MESSAGE("  Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}") 

# QT4 Handling
FIND_PACKAGE(Qt4 REQUIRED)
SET( QT_USE_QTSQL TRUE )
INCLUDE(${QT_USE_FILE})
MESSAGE( "QT information: ")
MESSAGE( "  QT_INCLUDE_DIRS: ${QT_INCLUDE_DIRS}")
MESSAGE( "  QT_LIBRARIES: ${QT_LIBRARIES}" )
MESSAGE( "  QT_LIBRARY_DIRS: ${QT_LIBRARY_DIRS}")

# GTEST Handling
find_package( GTEST REQUIRED )
MESSAGE("GTEST information:")
MESSAGE("  GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
MESSAGE("  GTEST_LIBRARIES: ${GTEST_LIBRARIES}")

SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}" ${Boost_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/lib" "${PROJECT_SOURCE_DIR}/libOTD")
# compile the main library
# build Logging static library
add_subdirectory ( Logging )
add_subdirectory ( libOTD )
add_subdirectory ( unit_tests ) 

# Add Test
ENABLE_TESTING()
INCLUDE(CTest)
ADD_TEST( utest_main "${PROJECT_SOURCE_DIR}/bin/utest_main" )
add_test(class_Tick_create_delete "${PROJECT_SOURCE_DIR}/bin/class_Tick_create_delete")
add_test(class_Instrument_create_delete "${PROJECT_SOURCE_DIR}/bin/class_Tick_create_delete")
#set_tests_properties (UTest_Runs PROPERTIES PASS_REGULAR_EXPRESSION "Chen")
