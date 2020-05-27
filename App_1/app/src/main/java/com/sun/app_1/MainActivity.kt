package com.sun.app_1

import android.Manifest
import android.content.Intent
import android.os.Bundle
import android.os.PersistableBundle
import com.sun.app_1.feature.activity.IntentDemoActivity
import com.sun.presentation.BaseActivity
import com.sun.presentation.utils.NavUtil
import kotlinx.android.synthetic.main.activity_main.*

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
        initView()
        bindAction()
        checkoutPermission();
    }

    private fun checkoutPermission() {
        reqPermission(
            arrayOf(
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE
            )
        ) {
            if (it) {

            } else {
                App.exit()
            }
        }
    }

    private fun bindAction() {
        tv_intent.onClick {
            NavUtil.safeLunch(this, Intent(this@MainActivity, IntentDemoActivity::class.java))
        }
    }

    private fun initView() {

    }


}