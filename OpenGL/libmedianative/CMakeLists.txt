cmake_minimum_required(VERSION 3.10.2)

set(PATH_TO_CODE_CORE ${CMAKE_SOURCE_DIR}/src/main/cpp)
set(PATH_TO_JNI_LAYER ${CMAKE_SOURCE_DIR}/src/main/cpp/jni)

file(GLOB FILES_JNI_LAYER "${PATH_TO_JNI_LAYER}/*.cpp")
file(GLOB FILES_LIB_CORE_CODE "${PATH_TO_CODE_CORE}/*.cpp")

include_directories(BEFORE ${PATH_TO_CODE_CORE}/include/)
include_directories(${PATH_TO_CODE_CORE}/)

##add_library(libmedianative SHARED
##        ${FILES_JNI_LAYER}
##        ${FILES_LIB_CORE_CODE}
##        )
#
#
#target_link_libraries(
#        GLESv3
#        dl
#        z
#        m
#        )