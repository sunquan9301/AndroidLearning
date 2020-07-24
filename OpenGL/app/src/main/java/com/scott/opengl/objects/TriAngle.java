package com.scott.opengl.objects;

import com.scott.opengl.data.VertexArray;
import com.scott.opengl.programs.ColorShaderProgram;
import com.scott.opengl.util.Constants;

import static android.opengl.GLES20.GL_POINTS;
import static android.opengl.GLES20.GL_TRIANGLES;
import static android.opengl.GLES20.glDrawArrays;

public class TriAngle {
    private static final int POSITION_COMPONENT_COUNT = 2;
    private static final int COLOR_COMPONENT_COUNT = 3;
    private static final int STRIDE =
            (POSITION_COMPONENT_COUNT + COLOR_COMPONENT_COUNT)
                    * Constants.BYTES_PER_FLOAT;

    private static final float[] VERTEX_DATA = {
            // Order of coordinates: X, Y, R, G, B

            // Triangle Fan
            0f, 0.5f, 1f, 0f, 0f,
            -0.8f, -0.5f, 0f, 1f, 0f,
            0.8f, -0.5f, 0f, 0f, 1f
    };
    private final VertexArray vertexArray;

    public TriAngle() {
        this.vertexArray = new VertexArray(VERTEX_DATA);
    }

    public void bindData(ColorShaderProgram colorProgram) {
        vertexArray.setVertexAttribPointer(
                0,
                colorProgram.getPositionAttributeLocation(),
                POSITION_COMPONENT_COUNT,
                STRIDE);
//        vertexArray.setVertexAttribPointer(
//                POSITION_COMPONENT_COUNT,
//                colorProgram.getColorAttributeLocation(),
//                COLOR_COMPONENT_COUNT,
//                STRIDE);
    }
    public void draw() {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}
