PROJECT( TEST )

ADD_EXECUTABLE(utest_main utest_main.cpp )
TARGET_LINK_LIBRARIES(utest_main ${GTEST_LIBRARIES} Logging OTD )                   

ADD_EXECUTABLE(class_Tick_create_delete class_Tick_create_delete.cpp )
TARGET_LINK_LIBRARIES(class_Tick_create_delete ${GTEST_LIBRARIES} Logging OTD )

INSTALL ( TARGETS utest_main DESTINATION bin )
INSTALL ( TARGETS class_Tick_create_delete DESTINATION bin )


# ENABLE_TESTING()
# INCLUDE(CTest)
# ADD_TEST( UTest_Runs utest_main class_Tick_create_delete )
# set_tests_properties (UTest_Runs PROPERTIES PASS_REGULAR_EXPRESSION "Chen")
