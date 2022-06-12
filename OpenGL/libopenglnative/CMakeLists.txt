cmake_minimum_required(VERSION 3.10.2)

set(PATH_TO_CODE_CORE ${CMAKE_SOURCE_DIR}/src/main/cpp)

file(GLOB FILES_JNI_LAYER "${PATH_TO_JNI_LAYER}/*.cpp")

include_directories(${PATH_TO_CODE_CORE}/include/libimage)
include_directories(${PATH_TO_CODE_CORE}/include/glm)
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

add_library(openglnative SHARED
        ${FILES_JNI_LAYER}
        ${FILES_LIB_CORE_CODE}
        ${PATH_TO_CODE_CORE}/EGLRender.cpp


        ${PATH_TO_CODE_CORE}/jni/NativeRenderJNI.cpp


        ${PATH_TO_CODE_CORE}/learnopengl_assigns/GLAbsRender.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/AssignFactory.cpp

        # learnopengl triangle demo
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/triangle/RenderTriangle.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/triangle/RenderTriangleVBO.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/triangle/RenderTriangleVAO.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/triangle/RenderRect.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/triangle/RenderRectTwoFragmentShader.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/triangle/RenderRectEBO.cpp

        # shaders demo
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/shaders/SimpleShader.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/shaders/UniformShader.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/shaders/StrideShader.cpp

        # textures
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/textures/TextureDemo.cpp

        # transform
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/transform/TransformDemo.cpp
        ${PATH_TO_CODE_CORE}/learnopengl_assigns/transform/PerspactiveTransformDemo.cpp

        ${PATH_TO_CODE_CORE}/common/TypeUtil.cpp
        ${PATH_TO_CODE_CORE}/common/AssetFun.cpp
        ${PATH_TO_CODE_CORE}/common/GLUtils.cpp
        ${PATH_TO_CODE_CORE}/common/TimeUtil.cpp
        )


target_link_libraries(
        openglnative
        ${platform-libs}
        )