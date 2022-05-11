package com.scott.opengl.programs;

public interface IShaderProgram {
    String A_COLOR = "a_Color";
    String A_POSITION = "a_Position";
    int POSITION_COMPONENT_COUNT = 2;
    int COLOR_COMPONENT_COUNT = 3;
    int BYTES_PER_FLOAT = 4;
    int STRIDE = (POSITION_COMPONENT_COUNT + COLOR_COMPONENT_COUNT) * BYTES_PER_FLOAT;

    void initAttributions();

    void bindShaderSource();

    void onDraw();
}
