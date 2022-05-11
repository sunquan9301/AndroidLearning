/***
 * Excerpted from "OpenGL ES for Android",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/kbogla for more book information.
***/
package com.scott.opengl.util;

import android.content.Context;
import android.opengl.GLES30;
import android.util.Log;

import static android.opengl.GLES20.GL_COMPILE_STATUS;
import static android.opengl.GLES20.GL_FRAGMENT_SHADER;
import static android.opengl.GLES20.GL_LINK_STATUS;
import static android.opengl.GLES20.GL_VALIDATE_STATUS;
import static android.opengl.GLES20.GL_VERTEX_SHADER;
import static android.opengl.GLES20.glAttachShader;
import static android.opengl.GLES20.glCompileShader;
import static android.opengl.GLES20.glCreateProgram;
import static android.opengl.GLES20.glCreateShader;
import static android.opengl.GLES20.glDeleteProgram;
import static android.opengl.GLES20.glDeleteShader;
import static android.opengl.GLES20.glGetProgramInfoLog;
import static android.opengl.GLES20.glGetProgramiv;
import static android.opengl.GLES20.glGetShaderInfoLog;
import static android.opengl.GLES20.glGetShaderiv;
import static android.opengl.GLES20.glLinkProgram;
import static android.opengl.GLES20.glShaderSource;
import static android.opengl.GLES20.glValidateProgram;

import androidx.annotation.NonNull;
import androidx.annotation.RawRes;

import com.scott.opengl.R;
import com.scott.opengl.programs.IShaderProgram;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public class GLHelper {
    private static final String TAG = "ShaderHelper";

    public static class Vertex{
        public static FloatBuffer allocate(@NonNull float[] data){
            FloatBuffer vertexData = ByteBuffer
                    .allocateDirect(data.length * IShaderProgram.BYTES_PER_FLOAT)
                    .order(ByteOrder.nativeOrder())
                    .asFloatBuffer();

            vertexData.put(data);
            return vertexData;
        }
    }

    public static class Shader{
        public static int compileVertexShader(String shaderCode) {
            return compileShader(GL_VERTEX_SHADER, shaderCode);
        }

        public static int compileFragmentShader(String shaderCode) {
            return compileShader(GL_FRAGMENT_SHADER, shaderCode);
        }

        /**
         * Compiles a shader, returning the OpenGL object ID.
         */
        private static int compileShader(int type, String shaderCode) {
            // Create a new shader object.
            final int shaderObjectId = glCreateShader(type);

            if (shaderObjectId == 0) {
                if (LoggerConfig.ON) {
                    Log.w(TAG, "Could not create new shader.");
                }

                return 0;
            }

            // Pass in the shader source.
            glShaderSource(shaderObjectId, shaderCode);

            // Compile the shader.
            glCompileShader(shaderObjectId);

            // Get the compilation status.
            final int[] compileStatus = new int[1];
            glGetShaderiv(shaderObjectId, GL_COMPILE_STATUS,
                    compileStatus, 0);

            if (LoggerConfig.ON) {
                // Print the shader info log to the Android log output.
                Log.v(TAG, "Results of compiling source:" + "\n" + shaderCode
                        + "\n:" + glGetShaderInfoLog(shaderObjectId));
            }

            // Verify the compile status.
            if (compileStatus[0] == 0) {
                // If it failed, delete the shader object.
                glDeleteShader(shaderObjectId);

                if (LoggerConfig.ON) {
                    Log.w(TAG, "Compilation of shader failed.");
                }

                return 0;
            }

            // Return the shader object ID.
            return shaderObjectId;
        }
    }

    public static class Program{
        /**
         * Links a vertex shader and a fragment shader together into an OpenGL
         * program. Returns the OpenGL program object ID, or 0 if linking failed.
         */
        public static int linkProgram(int vertexShaderId, int fragmentShaderId) {

            // Create a new program object.
            final int programObjectId = GLES30.glCreateProgram();

            if (programObjectId == 0) {
                if (LoggerConfig.ON) {
                    Log.w(TAG, "Could not create new program");
                }

                return 0;
            }

            // Attach the vertex shader to the program.
            GLES30.glAttachShader(programObjectId, vertexShaderId);

            // Attach the fragment shader to the program.
            GLES30.glAttachShader(programObjectId, fragmentShaderId);

            // Link the two shaders together into a program.
            GLES30.glLinkProgram(programObjectId);

            // Get the link status.
            final int[] linkStatus = new int[1];
            GLES30.glGetProgramiv(programObjectId, GL_LINK_STATUS,
                    linkStatus, 0);

            if (LoggerConfig.ON) {
                // Print the program info log to the Android log output.
                Log.v(
                        TAG,
                        "Results of linking program:\n"
                                + glGetProgramInfoLog(programObjectId));
            }

            // Verify the link status.
            if (linkStatus[0] == 0) {
                // If it failed, delete the program object.
                GLES30.glDeleteProgram(programObjectId);

                if (LoggerConfig.ON) {
                    Log.w(TAG, "Linking of program failed.");
                }

                return 0;
            }

            // Return the program object ID.
            return programObjectId;
        }

        /**
         * Validates an OpenGL program. Should only be called when developing the
         * application.
         */
        public static boolean validateProgram(int programObjectId) {
            glValidateProgram(programObjectId);
            final int[] validateStatus = new int[1];
            glGetProgramiv(programObjectId, GL_VALIDATE_STATUS,
                    validateStatus, 0);
            Log.v(TAG, "Results of validating program: " + validateStatus[0]
                    + "\nLog:" + glGetProgramInfoLog(programObjectId));

            return validateStatus[0] != 0;
        }

        /**
         * Helper function that compiles the shaders, links and validates the
         * program, returning the program ID.
         */
        public static int buildProgram(String vertexShaderSource,
                                       String fragmentShaderSource) {
            int program;

            // Compile the shaders.
            int vertexShader = Shader.compileVertexShader(vertexShaderSource);
            int fragmentShader = Shader.compileFragmentShader(fragmentShaderSource);

            // Link them into a shader program.
            program = Program.linkProgram(vertexShader, fragmentShader);

            if (LoggerConfig.ON) {
                Program.validateProgram(program);
            }

            return program;
        }

        /**
         * Helper function that compiles the shaders, links and validates the
         * program, returning the program ID.
         */
        public static int buildProgram(Context context, @RawRes int vertexShaderResId,
                                       @RawRes int fragmentShaderResId) {
            String vertexShaderSource = TextResourceReader
                    .readTextFileFromResource(context, R.raw.triangle_vertex_shader);
            String fragmentShaderSource = TextResourceReader
                    .readTextFileFromResource(context, R.raw.triangle_fragment_shader);

            int program;

            // Compile the shaders.
            int vertexShader = Shader.compileVertexShader(vertexShaderSource);
            int fragmentShader = Shader.compileFragmentShader(fragmentShaderSource);

            // Link them into a shader program.
            program = Program.linkProgram(vertexShader, fragmentShader);

            if (LoggerConfig.ON) {
                Program.validateProgram(program);
            }

            return program;
        }
    }

}
