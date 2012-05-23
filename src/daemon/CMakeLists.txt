set(lpsdaemon_SRCS main.cpp lpsdbus.cpp)

include_directories(${QT_QTDBUS_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/src/daemon ${PCRE_INCLUDE_DIRS})

QT4_ADD_DBUS_ADAPTOR(lpsdaemon_DBUS ${CMAKE_SOURCE_DIR}/data/lpsmagic.xml lpsdbus.h LpsDbus)
qt4_automoc(${lpsdaemon_SRCS})

add_executable(lpsdaemon ${lpsdaemon_SRCS} ${lpsdaemon_DBUS})
target_link_libraries(lpsdaemon ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY} ${PCRE_LIBRARIES})

install(TARGETS lpsdaemon DESTINATION /usr/bin)