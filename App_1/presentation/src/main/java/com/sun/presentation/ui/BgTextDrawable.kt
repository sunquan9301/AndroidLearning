package com.sun.presentation.ui

import android.graphics.Canvas
import android.graphics.Paint
import android.graphics.RectF
import androidx.annotation.ColorInt

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2019/8/5
 **/
class BgTextDrawable(
    var shape: Int,
    var stroke: Int, @ColorInt var strokeColor: Int,
    var solidColor: Int,
    var radius: Float
) : PaintDrawable() {

    override fun draw(canvas: Canvas) {
        val height = bounds.height()
        val width = bounds.width()

        if (shape == 1 && width == height) {
            //circle
            mPaint.color = solidColor
            mPaint.style = Paint.Style.FILL
            canvas.drawCircle(width / 2.0f, height / 2.0f, width / 2.0f, mPaint)


            mPaint.color = strokeColor
            mPaint.strokeWidth = stroke.toFloat()
            mPaint.style = Paint.Style.STROKE
            canvas.drawCircle(width / 2.0f, height / 2.0f, (width - stroke) / 2.0f, mPaint)

        } else {
            //rect
            mPaint.color = solidColor
            mPaint.style = Paint.Style.FILL
            var rect: RectF = RectF(0f, 0f, width.toFloat(), height.toFloat())
            canvas.drawRoundRect(rect, radius, radius, mPaint)
            mPaint.color = strokeColor
            mPaint.strokeWidth = stroke.toFloat()
            mPaint.style = Paint.Style.STROKE
            // - 3是因为内边框和外边框弯曲不一样
            var rect1: RectF = RectF(
                stroke.toFloat() / 2f - 3,
                stroke.toFloat() / 2f - 3f,
                width.toFloat() - stroke / 2f + 3f,
                height.toFloat() - stroke / 2f + 3f
            )
            canvas.drawRoundRect(rect1, radius, radius, mPaint)
        }
    }
}