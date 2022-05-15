cmake_minimum_required(VERSION 3.10.2)

set(PATH_TO_CODE_CORE ${CMAKE_SOURCE_DIR}/src/main/cpp)

file(GLOB FILES_JNI_LAYER "${PATH_TO_JNI_LAYER}/*.cpp")

include_directories(${PATH_TO_CODE_CORE}/include/)
include_directories(${PATH_TO_CODE_CORE}/common/)
include_directories(${PATH_TO_CODE_CORE}/jni/)
include_directories(${PATH_TO_CODE_CORE}/)

find_library(log-lib log)
find_library(android-lib android)
find_library(z-lib z)
find_library(EGL-lib EGL)
find_library(GLESv3-lib GLESv3)
find_library(OpenSLES-lib OpenSLES)

set(platform-libs
        ${log-lib}
        ${android-lib}
        ${EGL-lib}
        ${GLESv3-lib}
        ${OpenSLES-lib}
        ${z-lib}
        )

add_library(medianative SHARED
        ${FILES_JNI_LAYER}
        ${FILES_LIB_CORE_CODE}
        ${PATH_TO_CODE_CORE}/jni/NativeRenderJNI.cpp
        )


target_link_libraries(
        medianative
        ${platform-libs}
        )