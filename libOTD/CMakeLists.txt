project( OTD )

set ( ${PROJECT_NAME}_headers libOTD.h )
set ( ${PROJECT_NAME}_sources libOTD.cpp )    

add_library ( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers} )
target_link_libraries ( ${PROJECT_NAME} Logging ${Boost_LIBRARIES} ${QT_LIBRARIES} )

INSTALL ( TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib/static
        ) 
