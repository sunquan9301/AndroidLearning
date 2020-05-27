package com.sun.presentation.utils

import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.animation.AnimatorSet
import android.animation.ObjectAnimator
import android.app.Dialog
import android.view.View

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2019/7/28
 **/

interface KotlinExFunUtil {

    public fun View.onClick(action: (View) -> Unit) {
        // 启动一个 actor
        // 设置一个监听器来启用 actor
        setOnClickListener {
            Check.checkQuickClick(it, 300)
            action(it)
        }
    }

    public fun View.toGone() {
        visibility = View.GONE
    }

    public fun View.toVisible() {
        visibility = View.VISIBLE
    }

    public fun View.checkVisible(): Boolean {
        return visibility == View.VISIBLE
    }

    public fun View.checkGone(): Boolean {
        return visibility == View.GONE
    }

    fun View.fadeIn() {
        if (visibility == View.VISIBLE) return
        alpha = 1.0f
        visibility = View.VISIBLE
        val set = AnimatorSet()
        set.play(ObjectAnimator.ofFloat(this, "alpha", 0f, 1.0f))
        set.duration = AnimUtil.DEFAULT_TIME
        set.start()
    }

    public fun View.fadeOut() {
        if (visibility == View.GONE) return
        alpha = 1.0f
        val set = AnimatorSet()
        set.play(ObjectAnimator.ofFloat(this, "alpha", 1.0f, 0f))
        set.duration = AnimUtil.DEFAULT_TIME
        set.addListener(object : AnimatorListenerAdapter() {
            override fun onAnimationEnd(animation: Animator) {
                super.onAnimationEnd(animation)
                visibility = View.GONE
            }
        })
        set.start()
    }

    public fun View.fadeOut(action: () -> Unit) {
        if (visibility == View.GONE) return
        alpha = 1.0f
        val set = AnimatorSet()
        set.play(ObjectAnimator.ofFloat(this, "alpha", 1.0f, 0f))
        set.duration = AnimUtil.DEFAULT_TIME
        set.addListener(object : AnimatorListenerAdapter() {
            override fun onAnimationEnd(animation: Animator) {
                super.onAnimationEnd(animation)
                visibility = View.GONE
                action()
            }
        })
        set.start()
    }

    public fun Dialog.safeShow(): Dialog? {
        try {
            this.show()
            return this
        } catch (e: Throwable) {
            e.printStackTrace()
            return null
        }
    }
}