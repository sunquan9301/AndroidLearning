package com.sun.app_1.feature.activity

import android.content.res.Configuration
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AlertDialog
import androidx.core.view.doOnPreDraw
import com.sun.app_1.R
import com.sun.presentation.BaseActivity
import com.sun.presentation.utils.Constants
import kotlinx.android.synthetic.main.activity_life_cycle.*


/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2020/5/23
 **/
class LifeCycleDemoActivity : BaseActivity() {
    override fun getLayoutId(): Int {
        return R.layout.activity_life_cycle
    }

    override fun startInit() {
    }

    override fun onResume() {
        super.onResume()
        Log.i(
            Constants.TAG.TAG_LIFECYCLE,
            "onResume tv_lifecycle measureW = ${tv_lifecycle.measuredWidth};width = ${tv_lifecycle.width}"
        )

        window.decorView.doOnPreDraw {
            Log.i(
                Constants.TAG.TAG_LIFECYCLE,
                "onResume tv_lifecycle measureW = ${tv_lifecycle.measuredWidth};width = ${tv_lifecycle.width}"
            )
        }
    }

    override fun onPause() {
        super.onPause()
        Log.i(
            Constants.TAG.TAG_LIFECYCLE,
            "onPause tv_lifecycle measureW = ${tv_lifecycle.measuredWidth};width = ${tv_lifecycle.width}"
        )
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle?) {
        super.onRestoreInstanceState(savedInstanceState)
        Log.i(
            Constants.TAG.TAG_LIFECYCLE,
            "onRestoreInstanceState: " + savedInstanceState?.getString("lifeCycle", "")
        )
    }

    override fun onConfigurationChanged(newConfig: Configuration?) {
        super.onConfigurationChanged(newConfig)
        Log.i(
            Constants.TAG.TAG_LIFECYCLE,
            "onConfigurationChanged"
        )
    }

    override fun isFinishing(): Boolean {
        return super.isFinishing()
        Log.i(
            Constants.TAG.TAG_LIFECYCLE,
            "isFinishing"
        )
    }

    override fun onBackPressed() {
        Log.i(
            Constants.TAG.TAG_LIFECYCLE,
            "onBackPressed"
        )
        AlertDialog.Builder(this).setMessage("确定要退出该页面吗？")
            .setPositiveButton(
                android.R.string.yes
            ) { dialog, which -> finish() }.setNegativeButton(
                android.R.string.no
            ) { dialog, which -> dialog.dismiss() }.create().show()
    }

    override fun onSaveInstanceState(outState: Bundle?) {
        super.onSaveInstanceState(outState)
        Log.i(
            Constants.TAG.TAG_LIFECYCLE,
            "onSaveInstanceState: "
        )
        outState?.putString("lifeCycle", "rotate")
    }

}