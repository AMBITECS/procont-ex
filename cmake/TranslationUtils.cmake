#=======================================================================
# Copyright © 2019-2022 Pedro López-Cabanillas <plcl@users.sf.net>
#=======================================================================

if (NOT TARGET Qt${QT_VERSION_MAJOR}::lconvert)
    message(FATAL_ERROR "The package \"Qt${QT_VERSION_MAJOR}LinguistTools\" is required.")
endif()

set(Qt_LCONVERT_EXECUTABLE Qt${QT_VERSION_MAJOR}::lconvert)

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

function(ADD_QT_TRANSLATIONS_RESOURCE res_file)
    set(_languages ${ARGN})
    set(_res_file ${CMAKE_CURRENT_BINARY_DIR}/qt_translations.qrc)
    set(_patterns qtbase qtmultimedia qtscript qtxmlpatterns)
    get_filename_component(_srcdir "${Qt${QT_VERSION_MAJOR}_DIR}/../../../translations" ABSOLUTE)
    set(_outfiles)
    foreach(_lang ${_languages})
        set(_infiles)
        set(_out qt_${_lang}.qm)
        foreach(_pat ${_patterns})
            set(_file "${_srcdir}/${_pat}_${_lang}.qm")
            if (EXISTS ${_file})
                list(APPEND _infiles ${_file})
            endif()
        endforeach()
        if(_infiles)
            add_custom_command(OUTPUT ${_out}
                    COMMAND ${Qt_LCONVERT_EXECUTABLE}
                    ARGS -i ${_infiles} -o ${_out}
                    COMMAND_EXPAND_LISTS VERBATIM)
            list(APPEND _outfiles ${_out})
        endif()
    endforeach()
    file(WRITE ${_res_file} "<!DOCTYPE RCC><RCC version=\"1.0\">\n <qresource prefix=\"/\">\n")
    foreach(_file ${_outfiles})
        get_filename_component(_filename ${_file} NAME)
        file(APPEND ${_res_file} "  <file>${_filename}</file>\n")
    endforeach()
    file(APPEND ${_res_file} " </qresource>\n</RCC>\n")
    set(${res_file} ${_res_file} PARENT_SCOPE)
endfunction()

#add_custom_target(lupdate
#        COMMAND ${Qt${QT_VERSION_MAJOR}_LUPDATE_EXECUTABLE} -recursive ${PROJECT_SOURCE_DIR} -ts *.ts
#        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#        COMMENT "Updating translations"
#)