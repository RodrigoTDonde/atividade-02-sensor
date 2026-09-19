cmake_minimum_required(VERSION 3.16)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
if(DEFINED CMAKE_PROJECT_INCLUDE_BEFORE)
    # O bootloader e um subprojeto e precisa da mesma selecao de compilador.
    idf_build_set_property(EXTRA_CMAKE_ARGS
        "-DCMAKE_PROJECT_INCLUDE_BEFORE=${CMAKE_PROJECT_INCLUDE_BEFORE}" APPEND)
endif()
project(atividade_02_sensor)
