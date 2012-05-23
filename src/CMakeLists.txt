set(lpsmagic_SRCS  lpsmagic.cpp )
set(libmagic_SRCS renderutil.cpp renderermanager.cpp renderer.cpp renderedimage.cpp)

add_subdirectory(daemon)
add_subdirectory(renderers)

include_directories(${QMSYSTEM_INCLUDE_DIRS} ${GCONF_INCLUDE_DIRS} ${QT_INCLUDES} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/qxtcore)
QT4_ADD_DBUS_INTERFACE(lpsmagic_DBUS ${CMAKE_SOURCE_DIR}/data/lpsmagic.xml lpsdbusinterface)
qt4_automoc(${lpsmagic_SRCS} ${libmagic_SRCS})

add_library(lpsmagic SHARED ${libmagic_SRCS} ${lpsmagic_DBUS})
target_link_libraries(lpsmagic qxtcore ${GCONF_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

add_executable(lpsmagicdaemon main.cpp ${lpsmagic_SRCS})
target_link_libraries(lpsmagicdaemon lpsmagic lpsrenderers ${QMSYSTEM_LIBRARIES} ${GCONF_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
set_target_properties(lpsmagicdaemon PROPERTIES OUTPUT_NAME "lpsmagic")

install(TARGETS lpsmagicdaemon DESTINATION /usr/bin)
install(TARGETS lpsmagic DESTINATION /usr/lib)
