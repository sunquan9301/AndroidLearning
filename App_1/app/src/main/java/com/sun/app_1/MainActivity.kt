package com.sun.app_1

import android.os.Bundle
import android.os.PersistableBundle
import com.sun.presentation.BaseActivity

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2020/5/22
 **/
class MainActivity : BaseActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }
    override fun getLayoutId(): Int {
        return R.layout.activity_main
    }

    override fun startInit() {
    }
}