package com.scott.opengl.renders;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.util.Log;

import com.scott.opengl.R;
import com.scott.opengl.util.MatrixHelper;
import com.scott.basic.utils.GLHelper;
import com.scott.basic.utils.TextResourceReader;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;
import static android.opengl.GLES20.GL_FLOAT;
import static android.opengl.GLES20.GL_LINES;
import static android.opengl.GLES20.GL_POINTS;
import static android.opengl.GLES20.GL_TRIANGLE_FAN;
import static android.opengl.GLES20.glClear;
import static android.opengl.GLES20.glClearColor;
import static android.opengl.GLES20.glDrawArrays;
import static android.opengl.GLES20.glEnableVertexAttribArray;
import static android.opengl.GLES20.glGetAttribLocation;
import static android.opengl.GLES20.glGetUniformLocation;
import static android.opengl.GLES20.glUniformMatrix4fv;
import static android.opengl.GLES20.glUseProgram;
import static android.opengl.GLES20.glVertexAttribPointer;
import static android.opengl.GLES20.glViewport;

public class AirHockeyRenderer3D implements GLSurfaceView.Renderer {
    private static final String A_COLOR = "a_Color";
    private static final String A_POSITION = "a_Position";
    private static final String U_MATRIX = "u_Matrix";
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
    private int uMatrixLocation;

    private final float[] projectionMatrix = new float[16];
    private final float[] modelMatrix = new float[16];



    public AirHockeyRenderer3D(Context context) {
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
                0f,     0f,    1f,    1f,    1f,
                -0.5f, -0.8f, 0.7f, 0.7f, 0.7f,
                0.5f, -0.8f, 0.7f, 0.7f, 0.7f,
                0.5f,  0.8f, 0.7f, 0.7f, 0.7f,
                -0.5f,  0.8f, 0.7f, 0.7f, 0.7f,
                -0.5f, -0.8f, 0.7f, 0.7f, 0.7f,

                // Line 1
                -0.5f, 0f, 1f, 0f, 0f,
                0.5f, 0f, 1f, 0f, 0f,

                // Mallets
                0f, -0.4f, 0f, 0f, 1f,
                0f,  0.4f, 1f, 0f, 0f
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
        glClearColor(0f, 0f, 0.0f, 0.0f);
        String vertexShaderSource = TextResourceReader
                .readTextFileFromResource(context, R.raw.simple_vertex_shader_ortho);
        String fragmentShaderSource = TextResourceReader
                .readTextFileFromResource(context, R.raw.simple_fragment_shader_ortho);

        int vertexShader = GLHelper.Shader.compileVertexShader(vertexShaderSource);
        int fragmentShader = GLHelper.Shader.compileFragmentShader(fragmentShaderSource);

        program = GLHelper.Program.linkProgram(vertexShader, fragmentShader);

        GLHelper.Program.validateProgram(program);

        glUseProgram(program);

        aColorLocation = glGetAttribLocation(program, A_COLOR);

        aPositionLocation = glGetAttribLocation(program, A_POSITION);

        uMatrixLocation = glGetUniformLocation(program, U_MATRIX);

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

//        final float aspectRatio = width > height ?
//                (float) width / (float) height :
//                (float) height / (float) width;
//
//        if (width > height) {
//            // Landscape
//            Matrix.orthoM(projectionMatrix, 0, -aspectRatio, aspectRatio, -1f, 1f, -1f, 1f);
//        } else {
//            // Portrait or square
//            Matrix.orthoM(projectionMatrix, 0, -1f, 1f, -aspectRatio, aspectRatio, -1f, 1f);
//        }

        MatrixHelper.perspectiveM(projectionMatrix, 45, (float) width
                / (float) height, 1f, 10f);

        /*
        setIdentityM(modelMatrix, 0);
        translateM(modelMatrix, 0, 0f, 0f, -2f);
        */

        Matrix.setIdentityM(modelMatrix, 0);

        Matrix.translateM(modelMatrix, 0, 0f, 0f, -3f);
        Matrix.rotateM(modelMatrix, 0, -40f, 1f, 0f, 0f);

        final float[] temp = new float[16];
        Matrix.multiplyMM(temp, 0, projectionMatrix, 0, modelMatrix, 0);
        System.arraycopy(temp, 0, projectionMatrix, 0, temp.length);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        // Clear the rendering surface.
        glClear(GL_COLOR_BUFFER_BIT);

        glUniformMatrix4fv(uMatrixLocation, 1, false, projectionMatrix, 0);

        // Draw the table.
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

        // Draw the center dividing line.
        glDrawArrays(GL_LINES, 6, 2);

        // Draw the first mallet blue.
        glDrawArrays(GL_POINTS, 8, 1);

        // Draw the second mallet red.
        glDrawArrays(GL_POINTS, 9, 1);

    }
}
