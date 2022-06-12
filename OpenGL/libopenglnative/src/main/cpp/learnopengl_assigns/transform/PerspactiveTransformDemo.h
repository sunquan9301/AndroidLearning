//
// Created by 孙全 on 2022/6/12.
//

#ifndef OPENGL_PERSPACTIVETRANSFORMDEMO_H
#define OPENGL_PERSPACTIVETRANSFORMDEMO_H

#include "learnopengl_assigns/GLAbsRender.h"

class PerspactiveTransformDemo : public GLAbsRender {
public:
    virtual void onDraw();
    static void perspactive(float eye_fov, float aspect_ratio,
                            float zNear, float zFar);

    virtual void onSurfaceCreated();
    GLuint VBO,EBO;
    glm::mat4 model,view,projection;

    PerspactiveTransformDemo(){
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
    }
};


#endif //OPENGL_PERSPACTIVETRANSFORMDEMO_H
