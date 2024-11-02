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

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Widgets Xml LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Xml LinguistTools)

set(PROJECT_SOURCES
    main/MainApp.cpp
    main/MainWindow.cpp main/MainWindow.h

    model/DomModel.h model/DomModel.cpp
    model/ProxyModel.cpp model/ProxyModel.h

    item/DomItem.h item/DomItem.cpp
    item/ItemValue.cpp item/ItemValue.h
    item/ItemValueVariableTable.h item/ItemValueVariableTable.cpp

    widget/TabWidgetEditor.h widget/TabWidgetEditor.cpp
    widget/TabWidgetTree.h widget/TabWidgetTree.cpp
    widget/TabWidgetProtocol.cpp widget/TabWidgetProtocol.h
    widget/WidgetEditor.h widget/WidgetEditor.cpp

    log/Logger.h log/Logger.cpp log/Message.h log/Message.cpp

    view/TreeView.h view/TreeView.cpp
    view/ItemDelegate.h view/ItemDelegate.cpp
    view/SpinBoxMultiRange.h view/SpinBoxMultiRange.cpp
    view/TableView.h view/TableView.cpp

    editor/st/CodeEditor.cpp editor/st/CodeEditor.h
    editor/st/CodeEditorWidget.cpp editor/st/CodeEditorWidget.h
    editor/st/Highlighter.cpp editor/st/Highlighter.h
    editor/st/LineNumberArea.cpp editor/st/LineNumberArea.h
    editor/st/FilesManager.h editor/st/FilesManager.cpp
    editor/st/CommonStTypes.h
    editor/st/XmlParser.cpp editor/st/XmlParser.h
    editor/st/ArraySt.cpp editor/st/ArraySt.h
    editor/st/StructSt.cpp editor/st/StructSt.h
    editor/st/Variable.cpp editor/st/Variable.h
    editor/st/POU.cpp editor/st/POU.h
    editor/st/DataType.cpp editor/st/DataType.h
    editor/st/editor-st.qrc

    translator/SchemaViewer.cpp translator/SchemaViewer.h
    translator/GlobalType.h
    translator/XmlParser.cpp translator/XmlParser.h
    translator/TranslatorIec.h translator/TranslatorIec.cpp
    translator/TranslatorFbd.h translator/TranslatorFbd.cpp
    translator/TranslatorSfc.h translator/TranslatorSfc.cpp

    generate/Compiler.cpp generate/Compiler.h
    generate/Translator.cpp generate/Translator.h

    iec/StandardLibrary.cpp iec/StandardLibrary.h
    iec/Library.h iec/Library.cpp

    dialog/AddPOUDialog.h dialog/AddPOUDialog.cpp dialog/AddPOUDialog.ui
    dialog/AddTypeDialog.h dialog/AddTypeDialog.cpp dialog/AddTypeDialog.ui

    resource/procont-app-conf.qrc
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
        dialog/InputAssistantDialog.h dialog/InputAssistantDialog.cpp dialog/InputAssistantDialog.ui
        dialog/InputDialog.h dialog/InputDialog.cpp
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
