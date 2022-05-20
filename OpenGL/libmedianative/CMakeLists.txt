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

set(platform-libs
        ${log-lib}
        ${android-lib}
        ${EGL-lib}
        ${GLESv3-lib}
        ${z-lib}
        )

add_library(medianative SHARED
        ${FILES_JNI_LAYER}
        ${FILES_LIB_CORE_CODE}
        ${PATH_TO_CODE_CORE}/EGLRender.cpp


        ${PATH_TO_CODE_CORE}/jni/NativeRenderJNI.cpp

        ${PATH_TO_CODE_CORE}/assigns/GLAbsRender.cpp
        ${PATH_TO_CODE_CORE}/assigns/AssignFactory.cpp
        ${PATH_TO_CODE_CORE}/assigns/triangle/RenderTriangle.cpp
        ${PATH_TO_CODE_CORE}/assigns/triangle/RenderTriangleVBO.cpp



        ${PATH_TO_CODE_CORE}/common/TypeUtil.cpp
        ${PATH_TO_CODE_CORE}/common/AssetFun.cpp
        ${PATH_TO_CODE_CORE}/common/GLUtils.cpp




        )


target_link_libraries(
        medianative
        ${platform-libs}
        )