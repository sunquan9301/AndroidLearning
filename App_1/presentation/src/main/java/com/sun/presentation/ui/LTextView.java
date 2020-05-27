package com.sun.presentation.ui;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Typeface;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.GradientDrawable;
import android.util.AttributeSet;

import androidx.annotation.ColorInt;
import androidx.annotation.Nullable;
import androidx.appcompat.widget.AppCompatTextView;

import com.sun.presentation.R;
import com.sun.presentation.utils.ViewUtils;

import static android.graphics.drawable.GradientDrawable.RADIAL_GRADIENT;

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2018/9/27
 **/
public class LTextView extends AppCompatTextView {
    private int stroke;
    private @ColorInt int strokeColor;
    private int solidColor;
    private int shape;
    private float radius;
    private boolean isBold;
    private boolean isUseFont;
    private Context context;

    public LTextView(Context context) {
        this(context, null);
    }

    public LTextView(Context context, @Nullable AttributeSet attrs) {
        this(context, attrs, -1);
    }

    public LTextView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        this.context = context;
        if (attrs != null) {
            getAttrs(context, attrs);
        }
    }

    private void getAttrs(Context context, AttributeSet attrs) {
        TypedArray ta = context.obtainStyledAttributes(attrs, R.styleable.LTextView);
        stroke = ta.getDimensionPixelOffset(R.styleable.LTextView_tv_stroke, 0);
        strokeColor = ta.getColor(R.styleable.LTextView_tv_stroke_color, getResources().getColor(R.color.transparent));
        solidColor = ta.getColor(R.styleable.LTextView_tv_solid_color, getResources().getColor(R.color.transparent));
        shape = ta.getInt(R.styleable.LTextView_tv_shape, 0);
        radius = ta.getDimension(R.styleable.LTextView_tv_radius, 0);
        isBold = ta.getBoolean(R.styleable.LTextView_tv_bold, false);
        isUseFont = ta.getBoolean(R.styleable.LTextView_tv_font, false);
        ta.recycle();
        setBackground(getThemeBackground());
        if (isBold) {
            getPaint().setFakeBoldText(true);
        }
        if (isUseFont) {
            ViewUtils.setTvFonts(this);
        }
        setIncludeFontPadding(false);
    }

    public void setFont(boolean isUseFont) {
        if (isUseFont) {
            ViewUtils.setTvFonts(this);
            return;
        }
        setTypeface(Typeface.DEFAULT);
    }

    public void setShape(int shape) {
        this.shape = shape;
    }

    public void setStroke(int stroke) {
        this.stroke = stroke;
    }

    public void setRadius(int radius) {
        this.radius = radius;
    }
    public void setBold(boolean isBold) {
        getPaint().setFakeBoldText(isBold);
    }

    public void setSolidAndStrokeColor(int solidColor, int storkeColor) {
        this.solidColor = solidColor;
        this.strokeColor = storkeColor;
        setBackground(null);
        setBackground(getThemeBackground());
    }


    private Drawable getThemeBackground() {
        GradientDrawable gd = new GradientDrawable();
        gd.setShape(shape);
        gd.setStroke(stroke, strokeColor);
        gd.setGradientType(RADIAL_GRADIENT);
        gd.setColor(solidColor);
        gd.setCornerRadius(radius);
        if (stroke < 8) {
            return gd;
        } else {
            return new BgTextDrawable(shape, stroke, strokeColor, solidColor, radius);
        }
    }
}
