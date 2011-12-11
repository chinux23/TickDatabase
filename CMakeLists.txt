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
SET( OTD_Qt4_SRC "${PROJECT_SOURCE_DIR}/Logging/QsLog.h" "${PROJECT_SOURCE_DIR}/Logging/QsDebugOutput.h" "${PROJECT_SOURCE_DIR}/QsLogDest.h" "${PROJECT_SOURCE_DIR}/include/libOTD.h" )
SET( OTD_Qt4_UI )
SET( OTD_Qt4_RES )
QT4_WRAP_CPP(OTD_QT_MOC_CPP ${OTD_Qt4_SRC})
QT4_WRAP_UI(OTD_QT_UI_CPP ${OTD_Qt4_UI})
QT4_ADD_RESOURCES(OTD_QT_RES_H ${OTD_Qt4_RES})

# GTEST Handling
find_package( GTEST REQUIRED )
MESSAGE("GTEST information:")
MESSAGE("  GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
MESSAGE("  GTEST_LIBRARIES: ${GTEST_LIBRARIES}")

INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}" ${Boost_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/lib" )
# Logging
SET( OTD_LOG "${PROJECT_SOURCE_DIR}/Logging/QsLog.cpp" "${PROJECT_SOURCE_DIR}/Logging/QsDebugOutput.cpp" "${PROJECT_SOURCE_DIR}/Logging/QsLogDest.cpp" )
# General
# SET( OTD_SRC utest_main.cpp ${OTD_LOG} )
SET( OTD_LIB ${QT_LIBRARIES} ${Boost_LIBRARIES} )

# compile the main library
include_directories ("${PROJECT_SOURCE_DIR}/libOTD")
add_subdirectory ( libOTD )
# add_library ( OTD ./libOTD/libOTD.cpp )
# SET( OTD_LIB ${OTD_LIB} OTD )

# Compile Unit Tests
#SET( OTD_UNIT_TESTS_DIR ./unit_tests )
#ADD_EXECUTABLE(utest_main ${OTD_UNIT_TESTS_DIR}/utest_main.cpp ${OTD_LOG} )
#TARGET_LINK_LIBRARIES(utest_main ${OTD_LIB} ) 
#ADD_EXECUTABLE(class_Tick_create_delete ${OTD_UNIT_TESTS_DIR}/class_Tick_create_delete.cpp ${OTD_LOG} )
#TARGET_LINK_LIBRARIES(class_Tick_create_delete OTD ${OTD_LIB} )

# Move Binary around
SET( CMAKE_INSTALL_PREFIX . )
add_subdirectory ( unit_tests ) 
# INSTALL ( TARGETS utest_main DESTINATION bin )
# INSTALL ( TARGETS class_Tick_create_delete DESTINATION bin )
# INSTALL ( TARGETS OTD DESTINATION lib ) 

# Add Test
ENABLE_TESTING()
INCLUDE(CTest)
ADD_TEST( utest_main "${PROJECT_SOURCE_DIR}/bin/utest_main" )
add_test(class_Tick_create_delete "${PROJECT_SOURCE_DIR}/bin/class_Tick_create_delete")
#set_tests_properties (UTest_Runs PROPERTIES PASS_REGULAR_EXPRESSION "Chen")
