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

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets Xml LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets Xml LinguistTools)

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

    editor/fbd/fbd/graphics/CConnectorPin.cpp editor/fbd/fbd/graphics/CConnectorPin.h editor/fbd/fbd/graphics/CDiagramObject.cpp editor/fbd/fbd/graphics/CDiagramObject.h editor/fbd/fbd/graphics/cdiagramwidget.cpp editor/fbd/fbd/graphics/cdiagramwidget.h editor/fbd/fbd/graphics/cgraphicshelper.cpp editor/fbd/fbd/graphics/cgraphicshelper.h editor/fbd/fbd/graphics/CLadder.cpp editor/fbd/fbd/graphics/CLadder.h editor/fbd/fbd/graphics/CObjectsText.cpp editor/fbd/fbd/graphics/CObjectsText.h editor/fbd/fbd/graphics/COglStyle.cpp editor/fbd/fbd/graphics/COglStyle.h editor/fbd/fbd/graphics/coglwidget.cpp editor/fbd/fbd/graphics/coglwidget.h editor/fbd/fbd/graphics/COglWorld.cpp editor/fbd/fbd/graphics/COglWorld.h editor/fbd/fbd/graphics/diagramwgt.ui
    editor/fbd/fbd/palette/CFbdComponentsTree.cpp editor/fbd/fbd/palette/CFbdComponentsTree.h editor/fbd/fbd/palette/components_palette.inc editor/fbd/fbd/palette/palette.h
    editor/fbd/plc-xml/CAddData.cpp editor/fbd/plc-xml/CAddData.h editor/fbd/plc-xml/CAddDataInfo.cpp editor/fbd/plc-xml/CAddDataInfo.h editor/fbd/plc-xml/CConnection.cpp editor/fbd/plc-xml/CConnection.h editor/fbd/plc-xml/CConnectionPointIn.cpp editor/fbd/plc-xml/CConnectionPointIn.h editor/fbd/plc-xml/CConnectionPointOut.cpp editor/fbd/plc-xml/CConnectionPointOut.h editor/fbd/plc-xml/CConnector.cpp editor/fbd/plc-xml/CConnector.h editor/fbd/plc-xml/CData.cpp editor/fbd/plc-xml/CData.h editor/fbd/plc-xml/CDocumentation.cpp editor/fbd/plc-xml/CDocumentation.h editor/fbd/plc-xml/CExpression.cpp editor/fbd/plc-xml/CExpression.h editor/fbd/plc-xml/CInfo.cpp editor/fbd/plc-xml/CInfo.h editor/fbd/plc-xml/CInterface.cpp editor/fbd/plc-xml/CInterface.h editor/fbd/plc-xml/CPosition.cpp editor/fbd/plc-xml/CPosition.h editor/fbd/plc-xml/CRelPosition.cpp editor/fbd/plc-xml/CRelPosition.h editor/fbd/plc-xml/CTransitions.cpp editor/fbd/plc-xml/CTransitions.h editor/fbd/plc-xml/includes.h
    editor/fbd/plc-xml/common/CBody.cpp editor/fbd/plc-xml/common/CBody.h editor/fbd/plc-xml/common/CComment.cpp editor/fbd/plc-xml/common/CComment.h editor/fbd/plc-xml/common/CPou.cpp editor/fbd/plc-xml/common/CPou.h
    editor/fbd/plc-xml/fbd/CBlock.cpp editor/fbd/plc-xml/fbd/CBlock.h editor/fbd/plc-xml/fbd/CFbdContent.cpp editor/fbd/plc-xml/fbd/CFbdContent.h editor/fbd/plc-xml/fbd/CJump.cpp editor/fbd/plc-xml/fbd/CJump.h editor/fbd/plc-xml/fbd/CLabel.cpp editor/fbd/plc-xml/fbd/CLabel.h editor/fbd/plc-xml/fbd/CReturn.cpp editor/fbd/plc-xml/fbd/CReturn.h
    editor/fbd/plc-xml/objects/CMacroStep.cpp editor/fbd/plc-xml/objects/CMacroStep.h
    editor/fbd/plc-xml/sfc/CActionBlock.cpp editor/fbd/plc-xml/sfc/CActionBlock.h editor/fbd/plc-xml/sfc/CActions.cpp editor/fbd/plc-xml/sfc/CActions.h editor/fbd/plc-xml/sfc/CInline.cpp editor/fbd/plc-xml/sfc/CInline.h
    editor/fbd/plc-xml/variables/CBlockVar.cpp editor/fbd/plc-xml/variables/CBlockVar.h editor/fbd/plc-xml/variables/CIFaceVars.cpp editor/fbd/plc-xml/variables/CIfaceVars.h editor/fbd/plc-xml/variables/CInOutVariables.cpp editor/fbd/plc-xml/variables/CInOutVariables.h editor/fbd/plc-xml/variables/CInputVariables.cpp editor/fbd/plc-xml/variables/CInputVariables.h editor/fbd/plc-xml/variables/COutputVariables.cpp editor/fbd/plc-xml/variables/COutputVariables.h editor/fbd/plc-xml/variables/CVariable.cpp editor/fbd/plc-xml/variables/CVariable.h
    editor/fbd/general/QtDialogs.cpp editor/fbd/general/QtDialogs.h editor/fbd/general/types.h
    editor/fbd/resources/images16.qrc
    editor/fbd/general/ctreeobject.h editor/fbd/general/ctreeobject.cpp
    editor/fbd/general/OglWidget.h editor/fbd/general/OglWidget.cpp

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

    dialog/AddPOUDialog.h dialog/AddPOUDialog.cpp dialog/AddPOUDialog.ui
    dialog/AddTypeDialog.h dialog/AddTypeDialog.cpp dialog/AddTypeDialog.ui

    dialog/InputDialog.h dialog/InputDialog.cpp

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
