package com.sun.presentation

import android.os.Bundle
import android.view.WindowManager
import androidx.appcompat.app.AppCompatActivity
import com.sun.presentation.utils.StatusBarUtils

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2020/5/22
 **/
abstract class BaseActivity : AppCompatActivity() {
    protected var statusBarHeight = 0
    protected var TAG = ""
    private val isTranslucent = true


    override fun onCreate(savedInstanceState: Bundle?) {
        window.addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS)
        statusBarHeight = StatusBarUtils.getStatusBarHeight(this)
        super.onCreate(savedInstanceState)
        setContentView(getLayoutId())

        try {
            TAG = javaClass.simpleName
        } catch (e: Exception) {
            e.printStackTrace()
        }
        if (isTranslucent) {
            StatusBarUtils.translucent(this, resources.getColor(R.color.transparent)) // 沉浸式状态栏
        }
        StatusBarUtils.setStatusTextBlack(this)
        startInit()
    }

    abstract fun getLayoutId(): Int

    /**
     * 参数设置
     */
    abstract fun startInit()

    override fun finish() {
        super.finish()
        overridePendingTransition(R.anim.not_exit_push_left_in, R.anim.push_right_out)
    }

    open fun finishWithNoAnim() {
        super.finish()
        overridePendingTransition(0, 0)
    }

}