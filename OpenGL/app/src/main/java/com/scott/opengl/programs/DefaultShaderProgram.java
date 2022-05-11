package com.scott.opengl.programs;

import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;
import static android.opengl.GLES20.GL_FLOAT;
import static android.opengl.GLES20.GL_TRIANGLES;
import static android.opengl.GLES20.glClear;
import static android.opengl.GLES20.glClearColor;
import static android.opengl.GLES20.glDrawArrays;
import static android.opengl.GLES20.glEnableVertexAttribArray;
import static android.opengl.GLES20.glGetAttribLocation;
import static android.opengl.GLES20.glUseProgram;
import static android.opengl.GLES20.glVertexAttribPointer;

import android.util.Log;

import com.scott.opengl.OpenGLApplication;
import com.scott.opengl.R;
import com.scott.opengl.util.GLHelper;

import java.nio.FloatBuffer;

public class DefaultShaderProgram implements IShaderProgram {
    private FloatBuffer vertexData;
    private int program;
    private int aPositionLocation;
    private int aColorLocation;

    @Override
    public void initAttributions() {
        float[] tableVerticesWithTriangles = {
                // Order of coordinates: X, Y, R, G, B

                // Triangle Fan
                0f, 0.5f, 1f, 0f, 0f,
                -0.8f, -0.5f, 0f, 1f, 0f,
                0.8f, -0.5f, 0f, 0f, 1f
        };
        vertexData = GLHelper.Vertex.allocate(tableVerticesWithTriangles);
    }

    @Override
    public void bindShaderSource() {
        Log.i("sun_opengl", "onSurfaceCreated");
        glClearColor(0.0f, 1.0f, 1.0f, 0.0f);

        program = GLHelper.Program.buildProgram(OpenGLApplication.appContext, R.raw.hello_triangle_vertex_shader,R.raw.triangle_fragment_shader);
        glUseProgram(program);

//        aColorLocation = glGetAttribLocation(program, A_COLOR);
//        aPositionLocation = glGetAttribLocation(program, A_POSITION);
        aColorLocation = 1;
        aPositionLocation = 0;
        // Bind our data, specified by the variable vertexData, to the vertex
        // attribute at location A_POSITION_LOCATION.
        vertexData.position(0);
        glVertexAttribPointer(aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT,
                false, STRIDE, vertexData);
        glEnableVertexAttribArray(aPositionLocation);

        vertexData.position(POSITION_COMPONENT_COUNT);
        glVertexAttribPointer(aColorLocation, COLOR_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, vertexData);
        glEnableVertexAttribArray(aColorLocation);
    }

    @Override
    public void onDraw() {
        // Clear the rendering surface.
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the table.
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
