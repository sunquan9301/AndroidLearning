package com.scott.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;

import com.scott.opengl.util.LoggerConfig;
import com.scott.opengl.util.ShaderHelper;
import com.scott.opengl.util.TextResourceReader;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

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
import static android.opengl.GLES20.glViewport;

public class TriAngleRenderer implements GLSurfaceView.Renderer {
    private static final String A_COLOR = "a_Color";
    private static final String A_POSITION = "a_Position";
    private static final int POSITION_COMPONENT_COUNT = 2;
    private static final int COLOR_COMPONENT_COUNT = 3;
    private static final int BYTES_PER_FLOAT = 4;
    private static final int STRIDE =
            (POSITION_COMPONENT_COUNT + COLOR_COMPONENT_COUNT) * BYTES_PER_FLOAT;
    private final FloatBuffer vertexData;
    private final Context context;
    private int program;
    private int aPositionLocation;
    private int aColorLocation;


    public TriAngleRenderer(Context context) {
        this.context = context;
        /*
		float[] tableVertices = {
			0f,  0f,
			0f, 14f,
			9f, 14f,
			9f,  0f
		};
         */
//        float[] tableVerticesWithTriangles = {
//                // Triangle 1
//                0f, 0f,
//                9f, 14f,
//                0f, 14f,
//
//                // Triangle 2
//                0f, 0f,
//                9f, 0f,
//                9f, 14f,
//                // Comma here for formatting purposes
//
//                // Line 1
//                0f, 7f,
//                9f, 7f,
//
//                // Mallets
//                4.5f, 2f,
//                4.5f, 12f
//        };
//        float[] tableVerticesWithTriangles = {
//                // Order of coordinates: X, Y, R, G, B
//
//                // Triangle Fan
//                0f,    0f,   1f,   1f,   1f,
//                -0.5f, -0.5f, 0.7f, 0.7f, 0.7f,
//                0.5f, -0.5f, 0.7f, 0.7f, 0.7f,
//                0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
//                -0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
//                -0.5f, -0.5f, 0.7f, 0.7f, 0.7f,
//
//                // Line 1
//                -0.5f, 0f, 1f, 0f, 0f,
//                0.5f, 0f, 1f, 0f, 0f,
//
//                // Mallets
//                0f, -0.25f, 0f, 0f, 1f,
//                0f,  0.25f, 1f, 0f, 0f
//        };

        float[] tableVerticesWithTriangles = {
                // Order of coordinates: X, Y, R, G, B

                // Triangle Fan
                0f, 0.5f, 1f, 0f, 0f,
                -1f, -0.5f, 0f, 1f, 0f,
                1f, -0.5f, 0f, 0f, 1f
        };
        vertexData = ByteBuffer
                .allocateDirect(tableVerticesWithTriangles.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer();

        vertexData.put(tableVerticesWithTriangles);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.i("sun_opengl", "onSurfaceCreated");
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        String vertexShaderSource = TextResourceReader
                .readTextFileFromResource(context, R.raw.simple_vertex_shader);
        String fragmentShaderSource = TextResourceReader
                .readTextFileFromResource(context, R.raw.simple_fragment_shader);

        int vertexShader = ShaderHelper.compileVertexShader(vertexShaderSource);
        int fragmentShader = ShaderHelper.compileFragmentShader(fragmentShaderSource);

        program = ShaderHelper.linkProgram(vertexShader, fragmentShader);

        if (LoggerConfig.ON) {
            ShaderHelper.validateProgram(program);
        }

        glUseProgram(program);

        aColorLocation = glGetAttribLocation(program, A_COLOR);

        aPositionLocation = glGetAttribLocation(program, A_POSITION);

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
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.i("sun_opengl", "onSurfaceChanged,w = " + width + ",height = " + height);
        glViewport(0, 0, width, height);

    }

    @Override
    public void onDrawFrame(GL10 gl) {
        // Clear the rendering surface.
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the table.
        glDrawArrays(GL_TRIANGLES, 0, 3);

//        // Draw the center dividing line.
//        glDrawArrays(GL_LINES, 6, 2);
//
//        // Draw the first mallet blue.
//        glDrawArrays(GL_POINTS, 8, 1);
//
//        // Draw the second mallet red.
//        glDrawArrays(GL_POINTS, 9, 1);

    }
}
