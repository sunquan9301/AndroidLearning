package com.scott.opengl.programs;

//import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;
//import static android.opengl.GLES20.GL_FLOAT;
//import static android.opengl.GLES20.GL_TRIANGLES;
//import static android.opengl.GLES20.glClear;
//import static android.opengl.GLES20.glClearColor;
//import static android.opengl.GLES20.glDrawArrays;
//import static android.opengl.GLES20.glEnableVertexAttribArray;
//import static android.opengl.GLES20.glUseProgram;
//import static android.opengl.GLES20.glVertexAttribPointer;

import static android.opengl.GLES30.GL_COLOR_BUFFER_BIT;
import static android.opengl.GLES30.GL_FLOAT;
import static android.opengl.GLES30.GL_TRIANGLES;

import android.opengl.GLES30;
import android.util.Log;

import com.scott.basic.shaders.IRender;
import com.scott.opengl.OpenGLApplication;
import com.scott.opengl.R;
import com.scott.basic.utils.GLHelper;

import java.nio.FloatBuffer;

public class DefaultRenderES3_0 implements IRender {
    private FloatBuffer vertexData;
    private int program;
    private int aPositionLocation;
    private int aColorLocation;

    @Override
    public void init() {
        float[] tableVerticesWithTriangles = {
                // Order of coordinates: X, Y, R, G, B

                0.0f,  0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
        };
        vertexData = GLHelper.Vertex.allocate(tableVerticesWithTriangles);
    }

    @Override
    public void onSurfaceCreated() {
        Log.i("sun_opengl", "onSurfaceCreated");
        GLES30.glClearColor(0.5f, 0.0f, 1.0f, 0.0f);

        program = GLHelper.Program.buildProgram(OpenGLApplication.appContext, R.raw.hello_triangle_vertex_shader,R.raw.hello_triangle_fragment_shader);
        GLES30.glUseProgram(program);

//        aColorLocation = glGetAttribLocation(program, A_COLOR);
//        aPositionLocation = glGetAttribLocation(program, A_POSITION);
//        aColorLocation = 1;
//        aPositionLocation = 0;
        // Bind our data, specified by the variable vertexData, to the vertex
        // attribute at location A_POSITION_LOCATION.
        vertexData.position(0);
        GLES30.glVertexAttribPointer(1,3,GL_FLOAT,false,12,vertexData);
//        GLES30.glVertexAttribPointer(aPositionLocation, 3, GL_FLOAT,
//                false, 12, vertexData);
        GLES30.glEnableVertexAttribArray(1);

//        vertexData.position(POSITION_COMPONENT_COUNT);
//        GLES30.glVertexAttribPointer(aColorLocation, COLOR_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, vertexData);
//        GLES30.glEnableVertexAttribArray(aColorLocation);
    }

    @Override
    public void onSurfaceChanged(int width, int height) {
        GLES30.glViewport(0,0,width,height);
    }

    @Override
    public void onDrawFrame() {
        // Clear the rendering surface.
        GLES30.glClear(GL_COLOR_BUFFER_BIT);

        // Draw the table.
        GLES30.glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    @Override
    public void onSurfaceDestroyed() {

    }
}
