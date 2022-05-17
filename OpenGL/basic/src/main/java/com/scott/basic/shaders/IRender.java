package com.scott.basic.shaders;

public interface IRender {
    String A_COLOR = "a_Color";
    String A_POSITION = "a_Position";
    int POSITION_COMPONENT_COUNT = 2;
    int COLOR_COMPONENT_COUNT = 3;
    int BYTES_PER_FLOAT = 4;
    int STRIDE = (POSITION_COMPONENT_COUNT + COLOR_COMPONENT_COUNT) * BYTES_PER_FLOAT;

    void init();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);

    void onDrawFrame();

    void onSurfaceDestroyed();
}
