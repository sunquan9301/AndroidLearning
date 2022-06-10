package com.scott.opengl;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.LinearLayoutCompat;

import com.scott.nativecode.IType;

public class MainActivity extends AppCompatActivity {

    private int[] demos = new int[]{
            IType.AssignType.ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE
    };
    private String[] btnTitles = new String[]{
            "绘制一个三角形"
    };
    private LinearLayoutCompat llContainer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        setContentView(R.layout.activity_main);
        llContainer = findViewById(R.id.ll_container);
    }


    @Override
    protected void onPostCreate(@Nullable Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        for (int i=0;i<demos.length;i++){
            llContainer.addView(createDemoBtn(i));
        }
    }

    private TextView createDemoBtn(final int index) {
        TextView textView = new TextView(this);
        textView.setGravity(Gravity.CENTER);
        textView.setId(demos[index]);
        LinearLayoutCompat.LayoutParams ll = new LinearLayoutCompat.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,100);
        ll.bottomMargin = 30;
        ll.gravity = Gravity.CENTER;
        textView.setLayoutParams(ll);
        textView.setTextSize(14);
        textView.setTextColor(Color.BLACK);
        textView.setBackgroundColor(Color.LTGRAY);
        textView.setText(btnTitles[index]);
        textView.setPadding(36,0,36,0);
        textView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this,OpenGLActivity.class);
                i.putExtra("demoType",demos[index]);
                startActivity(i);
            }
        });
        return textView;
    }
}
