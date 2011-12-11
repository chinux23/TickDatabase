PROJECT(Logging)

set( ${PROJECT_NAME}_headers QsDebugOutput.h QsLog.h QsLogDest.h )
set( ${PROJECT_NAME}_sources QsDebugOutput.cpp QsLog.cpp QsLogDest.cpp )
# QT4_WRAP_CPP(${PROJECT_NAME}_QT_MOC_CPP ${${PROJECT_NAME}_headers} )

add_library ( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources} )
install ( TARGETS ${PROJECT_NAME} 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
