cmake_minimum_required(VERSION 3.5)

set(NAME ${PNME}-conf-app)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/${PNME}/${NAME}/bin)
set(LIBRARY_OUTPUT_PATH     ${CMAKE_BINARY_DIR}/${PNME}/${NAME}/lib)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Xml LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Xml LinguistTools)

set(PROJECT_SOURCES
    main/MainApp.cpp
    model/DomModel.h model/DomModel.cpp
    item/DomItem.h item/DomItem.cpp
    model/ProxyModel.cpp model/ProxyModel.h
    view/TreeView.h view/TreeView.cpp
    widget/TabWidgetEditor.h widget/TabWidgetEditor.cpp
    widget/TabWidgetTree.h widget/TabWidgetTree.cpp
    main/MainWindow.cpp main/MainWindow.h
    widget/TabWidgetProtocol.cpp widget/TabWidgetProtocol.h
    log/Logger.h log/Logger.cpp log/Message.h log/Message.cpp
    view/ItemDelegate.h view/ItemDelegate.cpp
    view/SpinBoxMultiRange.h view/SpinBoxMultiRange.cpp
    item/ItemValue.cpp item/ItemValue.h
    item/ItemValueVariableTable.h item/ItemValueVariableTable.cpp
    view/TableView.h view/TableView.cpp
    editor-st/CodeEditor.cpp editor-st/CodeEditor.h editor-st/CodeEditorWidget.cpp
    editor-st/CodeEditorWidget.h editor-st/Highlighter.cpp editor-st/Highlighter.h
    editor-st/LineNumberArea.cpp editor-st/LineNumberArea.h
    editor-st/FilesManager.h editor-st/FilesManager.cpp
    widget/WidgetEditor.h widget/WidgetEditor.cpp
    editor-st/XmlParser.cpp editor-st/XmlParser.h
    resources/procont-app-conf.qrc
    editor-st/editor-st.qrc
    translator-fbd/SchemaViewer.cpp translator-fbd/SchemaViewer.h
    translator-fbd/GlobalType.h
    translator-fbd/XmlParser.cpp translator-fbd/XmlParser.h
)

qt_translate(
    NAME ${NAME}
    SOURCES ${PROJECT_SOURCES}
    TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tr"
    OUT_FILE TR_RC_FILE
    OUT_TARGET TR_RC_TARGET
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES} ${TR_RC_FILE}
    )
else()
    add_executable(${NAME} ${PROJECT_SOURCES} ${TR_RC_FILE})
endif()

add_dependencies(${NAME} ${TR_RC_TARGET})

set_target_properties(${NAME} PROPERTIES OUTPUT_NAME ${NAME})

target_link_libraries(${NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${NAME})
endif()
