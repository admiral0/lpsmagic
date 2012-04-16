set(RENDERERS_SRCS batteryrenderer.cpp daterenderer.cpp iconrenderer.cpp dumbtext.cpp)

include_directories(${GCONF_INCLUDE_DIRS} ${QT_INCLUDES} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
qt4_automoc(${RENDERERS_SRCS})

add_library(lpsrenderers STATIC ${RENDERERS_SRCS})