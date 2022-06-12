//
// Created by 孙全 on 2022/5/20.
//

#include "AssignFactory.h"
AssignFactory *AssignFactory::m_Instance = new AssignFactory();

AssignFactory *AssignFactory::getInstance() {
    return m_Instance;
}
void AssignFactory::createAssignDemo(int type) {
    if(type == ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE){
        this->p_AssignDemo = new RenderTriangle();
        return;
    }
    if(type == ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE_VBO){
        this->p_AssignDemo = new RenderTriangleVBO();
        return;
    }
    if(type == ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE_VAO){
        this->p_AssignDemo = new RenderTriangleVAO();
        return;
    }
    if(type == ASSIGN_LEARN_OPENGL_RECT){
        this->p_AssignDemo = new RenderRect();
        return;
    }
    if (type == ASSIGN_LEARN_OPENGL_RECT_TWO_FRAGMENT_SHADER) {
        this->p_AssignDemo = new RenderRectTwoFragmentShader();
        return;
    }
    if (type == ASSIGN_LEARN_OPENGL_RECT_EBO) {
        this->p_AssignDemo = new RenderRectEBO();
        return;
    }


    this->p_AssignDemo = new RenderTriangle();
}

void AssignFactory::createAssignDemoV2(JNIEnv *env, jobject asset_manager, int type) {
    if(type == ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE){
        this->p_AssignDemo = new RenderTriangle();
        this->p_AssignDemo->onInit(env,asset_manager,"hello_triangle_vertex_shader.glsl","hello_triangle_fragment_shader.glsl");
        return;
    }


    if (type == ASSIGN_LEARN_OPENGL_SHADER_SIMPLE_SHADER) {
        this->p_AssignDemo = new SimpleShader();
        this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_shaders_simpleshader_vertex_shader.glsl","learnopengl_shaders_simpleshader_fragment_shader.glsl");
        return;
    }
//    if (type == ASSIGN_LEARN_OPENGL_SHADER_UNIFORM_SHADER) {
//        this->p_AssignDemo = new UniformShader();
//        this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_shaders_uniform_vertex_shader.glsl","learnopengl_shaders_uniform_fragment_shader.glsl");
//        return;
//    }
    if (type == ASSIGN_LEARN_OPENGL_SHADER_UNIFORM_SHADER) {
        this->p_AssignDemo = new UniformShader();
        this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_shaders_uniform_vertex_shader1.glsl","learnopengl_shaders_uniform_fragment_shader1.glsl");
        return;
    }
    if (type == ASSIGN_LEARN_OPENGL_SHADER_STRIDE_SHADER) {
        this->p_AssignDemo = new StrideShader();
        this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_shaders_stride_vertex_shader.glsl","learnopengl_shaders_stride_fragment_shader.glsl");
        return;
    }
    if (type == ASSIGN_LEARN_OPENGL_TEXTURE_DEMO) {
        this->p_AssignDemo = new TextureDemo();
        this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_texture_vertex.glsl","learnopengl_texture_fragment.glsl");
        return;
    }
    if (type == ASSIGN_LEARN_OPENGL_TRANSFORM_DEMO) {
        this->p_AssignDemo = new TransformDemo();
        this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_transform_vertex_shader.glsl","learnopengl_transform_fragment_shader.glsl");
        return;
    }
    if (type == ASSIGN_LEARN_OPENGL_PERSPECTIVE_TRANSFORM_DEMO) {
        this->p_AssignDemo = new PerspactiveTransformDemo();
        this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_transform_perspactive_vertex_shader.glsl","learnopengl_transform_perspactive_fragment_shader.glsl");
        return;
    }
    this->p_AssignDemo = new SimpleShader();
    this->p_AssignDemo->onInit(env,asset_manager,"learnopengl_shaders_simpleshader_vertex_shader.glsl","learnopengl_shaders_simpleshader_fragment_shader.glsl");
}

void AssignFactory::onDestroyDemoResources() {
    if(AssignFactory::m_Instance){
        AssignFactory::m_Instance->onDestroy();
    }
}


