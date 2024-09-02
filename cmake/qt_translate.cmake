
function(qt_translate)

    set(options ALL)

    set(one_value_args NAME TS_DIR OUT_FILE OUT_TARGET)
    set(multi_args SOURCES)
    cmake_parse_arguments(GENQMRC "${options}" "${one_value_args}" "${multi_args}" ${ARGV})

    if (NOT GENQMRC_NAME OR NOT GENQMRC_SOURCES OR NOT GENQMRC_TS_DIR OR NOT GENQMRC_OUT_FILE OR NOT GENQMRC_OUT_TARGET)
        message(FATAL_ERROR "Could not generate translate files and resources!")
    endif ()

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY CLEAN_NO_CUSTOM TRUE)

    FILE(GLOB TS_FILES "${GENQMRC_TS_DIR}/*.ts")
    find_package(Qt${QT_VERSION_MAJOR}LinguistTools)
    qt_create_translation(QM_FILES ${GENQMRC_SOURCES} ${TS_FILES})

    add_app_translations_resource(TRANSLATE_RES ${QM_FILES})

    add_custom_target(${GENQMRC_NAME}-TRANSLATE ALL DEPENDS ${QM_FILES})
    add_custom_target(${GENQMRC_NAME}-RESOURCE-LANG ALL DEPENDS ${TRANSLATE_RES})
    add_dependencies(${GENQMRC_NAME}-RESOURCE-LANG ${GENQMRC_NAME}-TRANSLATE)
    qt_add_resources(TR_RC ${TRANSLATE_RES})

    set(${GENQMRC_OUT_FILE} ${TR_RC} PARENT_SCOPE)
    set(${GENQMRC_OUT_TARGET} ${GENQMRC_NAME}-RESOURCE-LANG PARENT_SCOPE)

endfunction()

function(ADD_APP_TRANSLATIONS_RESOURCE res_file)
    set(_qm_files ${ARGN})
    set(_res_file ${CMAKE_CURRENT_BINARY_DIR}/app_translations.qrc)

    file(WRITE ${_res_file} "<!DOCTYPE RCC><RCC version=\"1.0\">\n <qresource prefix=\"/\">\n")
    foreach(_lang ${_qm_files})
        get_filename_component(_filename ${_lang} NAME)
        file(APPEND ${_res_file} "  <file>${_filename}</file>\n")
    endforeach()
    file(APPEND ${_res_file} " </qresource>\n</RCC>\n")

    set(${res_file} ${_res_file} PARENT_SCOPE)
endfunction()
