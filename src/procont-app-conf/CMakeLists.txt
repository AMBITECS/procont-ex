cmake_minimum_required(VERSION 3.5)

set(NAME ${PNME}-conf-app)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/${PNME}/${NAME}/bin)
set(LIBRARY_OUTPUT_PATH     ${CMAKE_BINARY_DIR}/${PNME}/${NAME}/lib)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets Xml LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets Xml LinguistTools)

file(GLOB_RECURSE fbd-editor
        editor/fbd/*.cpp
        editor/fbd/*.h
        editor/fbd/*.ui
        editor/fbd/*.qrc
        )

file(GLOB_RECURSE st-editor
        editor/st/*.cpp
        editor/st/*.h
        editor/st/*.ui
        editor/st/*.qrc
    )

set(PROJECT_SOURCES
    main/MainApp.cpp
    main/MainWindow.cpp main/MainWindow.h
    main/Settings.h

    model/DomModel.h model/DomModel.cpp
    model/ProxyModel.cpp model/ProxyModel.h

    item/DomItem.h item/DomItem.cpp
    item/ItemValue.cpp item/ItemValue.h
    item/ItemValueVariableTable.h item/ItemValueVariableTable.cpp

    widget/TabWidgetEditor.h widget/TabWidgetEditor.cpp
    widget/TabWidgetTree.h widget/TabWidgetTree.cpp
    widget/TabWidgetProtocol.cpp widget/TabWidgetProtocol.h
    widget/WidgetEditor.h widget/WidgetEditor.cpp
    widget/WidgetEditor_fbd.cpp widget/WidgetEditor_fbd.h
    widget/WidgetEditor_inherit.cpp widget/WidgetEditor_inherit.h

    log/Logger.h log/Logger.cpp log/Message.h log/Message.cpp

    view/TreeView.h view/TreeView.cpp
    view/ItemDelegate.h view/ItemDelegate.cpp
    view/SpinBoxMultiRange.h view/SpinBoxMultiRange.cpp
    view/TableView.h view/TableView.cpp

    translator/SchemaViewer.cpp translator/SchemaViewer.h
    translator/GlobalType.h
    translator/XmlParser.cpp translator/XmlParser.h
    translator/TranslatorIec.h translator/TranslatorIec.cpp
    translator/TranslatorFbd.h translator/TranslatorFbd.cpp
    translator/TranslatorSfc.h translator/TranslatorSfc.cpp
    translator/TranslatorIL.cpp translator/TranslatorIL.h
    translator/TranslatorLD.cpp translator/TranslatorLD.h
    translator/TranslatorST.cpp translator/TranslatorST.h

    generate/Compiler.cpp generate/Compiler.h
    generate/Translator.cpp generate/Translator.h

    iec/StandardLibrary.cpp iec/StandardLibrary.h
    iec/Library.h iec/Library.cpp

    dialog/InputDialog.h dialog/InputDialog.cpp
    dialog/AddPOUDialog.h dialog/AddPOUDialog.cpp
    dialog/AddDUTDialog.h dialog/AddDUTDialog.cpp
    dialog/RenameDialog.h dialog/RenameDialog.cpp

    resource/procont-app-conf.qrc

    tr/translation.h tr/translation.cpp

    xml/PLCopenXML.cpp xml/PLCopenXML.h

    undo/iundocommand.cpp undo/iundocommand.h
    undo/cundocommand_edit.cpp undo/cundocommand_edit.h
    undo/cundocommand_remove.h undo/cundocommand_remove.cpp
    undo/cundocommand_insert.h undo/cundocommand_insert.cpp

    ${st-editor}

    ${fbd-editor}
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

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(glut_lib
            C:/msys64/mingw64/lib/libglu32.a
            C:/msys64/mingw64/lib/libopengl32.a
    )
endif ()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(glut_lib /usr/lib/x86_64-linux-gnu/libGLU.so)
endif ()

if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    set(glut_lib /usr/local/lib/libGLU.so)
endif ()

target_link_libraries(${NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    Qt${QT_VERSION_MAJOR}::Xml)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${NAME})
endif()
