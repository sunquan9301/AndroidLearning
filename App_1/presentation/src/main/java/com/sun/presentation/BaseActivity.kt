package com.sun.presentation

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.view.WindowManager
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.sun.presentation.components.PresentationApp
import com.sun.presentation.utils.Check
import com.sun.presentation.utils.Constants
import com.sun.presentation.utils.KotlinExFunUtil
import com.sun.presentation.utils.StatusBarUtils

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2020/5/22
 **/
abstract class BaseActivity : AppCompatActivity(), KotlinExFunUtil {
    private val PERMISSION_REQUEST_CODE = 1

    protected var statusBarHeight = 0
    protected var TAG = ""
    private val isTranslucent = true
    var permissionCallBack: (Boolean) -> Unit = {}


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
        Log.i(Constants.TAG.TAG_ACTIVITY, "${TAG}, onCreate")
    }

    override fun onResume() {
        super.onResume()
        Log.i(Constants.TAG.TAG_ACTIVITY, "${TAG}, onResume")
    }

    override fun onRestart() {
        super.onRestart()
        Log.i(Constants.TAG.TAG_ACTIVITY, "${TAG}, onRestrat")
    }

    override fun onPause() {
        super.onPause()
        Log.i(Constants.TAG.TAG_ACTIVITY, "${TAG}, onPause")
    }

    override fun onStop() {
        super.onStop()
        Log.i(Constants.TAG.TAG_ACTIVITY, "${TAG}, onStop")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.i(Constants.TAG.TAG_ACTIVITY, "${TAG}, onDestroy")
    }

    abstract fun getLayoutId(): Int

    fun reqPermission(
        permissions: Array<String>,
        callBack: (Boolean) -> Unit
    ) {
        if (Check.isEmpty(permissions)) {
            callBack(true)
        }
        var needPermission = false
        for (permission in permissions) {
            if (ActivityCompat.checkSelfPermission(
                    PresentationApp.inst().getApp(),
                    permission
                ) != PackageManager.PERMISSION_GRANTED
            ) {
                needPermission = true
                break
            }
        }
        permissionCallBack = callBack
        if (needPermission) {
            ActivityCompat.requestPermissions(
                this,
                permissions,
                PERMISSION_REQUEST_CODE
            )
        } else if (callBack != null) {
            callBack(true)
        }
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String>,
        grantResults: IntArray
    ) {
        if (grantResults == null) {
            permissionCallBack(false)
            return
        }
        if (requestCode != PERMISSION_REQUEST_CODE || grantResults.size == 0) {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults)
            permissionCallBack(false)
            return
        }
        for (result in grantResults) {
            if (result == PackageManager.PERMISSION_DENIED) {
                super.onRequestPermissionsResult(requestCode, permissions, grantResults)
                permissionCallBack(false)
                return
            }
        }
        if (permissionCallBack != null) {
            permissionCallBack(true)
        }
    }

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