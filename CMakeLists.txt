CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(OpenTickDatabase)
    
set (CTEST_PROJECT_NAME "OpenTickDatabase")
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "-g3 -fno-inline -O0 -Wall -DQS_LOG_LINE_NUMBERS")

# BOOST Handling
set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_MULTITHREADED     ON)
FIND_PACKAGE(Boost REQUIRED)
MESSAGE("Boost information:") 
MESSAGE("  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}") 
MESSAGE("  Boost_LIBRARIES: ${Boost_LIBRARIES}") 
MESSAGE("  Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}") 

# QT4 Handling
FIND_PACKAGE(Qt4 REQUIRED)
SET( QT_USE_QTSQL TRUE )
INCLUDE(${QT_USE_FILE})
SET( OTD_Qt4_SRC ./Logging/QsLog.h ./Logging/QsDebugOutput.h ./QsLogDest.h ./libOTD.h )
SET( OTD_Qt4_UI )
SET( OTD_Qt4_RES )
QT4_WRAP_CPP(OTD_QT_MOC_CPP ${OTD_Qt4_SRC})
QT4_WRAP_UI(OTD_QT_UI_CPP ${OTD_Qt4_UI})
QT4_ADD_RESOURCES(OTD_QT_RES_H ${OTD_Qt4_RES})

INCLUDE_DIRECTORIES( . ${Boost_INCLUDE_DIRS} )
# Logging
SET( OTD_LOG ./Logging/QsLog.cpp ./Logging/QsDebugOutput.cpp ./Logging/QsLogDest.cpp )
# General
# SET( OTD_SRC utest_main.cpp ${OTD_LOG} )
SET( OTD_LIB ${QT_LIBRARIES} )

# compile the main library
add_library ( OTD ./libOTD/libOTD.cpp )

# Compile Unit Tests
SET( OTD_UNIT_TESTS_DIR ./unit_tests )
ADD_EXECUTABLE(utest_main ${OTD_UNIT_TESTS_DIR}/utest_main.cpp ${OTD_LOG} )
TARGET_LINK_LIBRARIES(utest_main ${OTD_LIB} ${Boost_LIBRARIES} ) 
        
# Move Binary around
SET( CMAKE_INSTALL_PREFIX . )     
INSTALL ( TARGETS utest_main DESTINATION bin )

# Add Test
ENABLE_TESTING()
INCLUDE(CTest)
ADD_TEST( UTest_Runs utest_main )
set_tests_properties (UTest_Runs PROPERTIES PASS_REGULAR_EXPRESSION "Chen")
