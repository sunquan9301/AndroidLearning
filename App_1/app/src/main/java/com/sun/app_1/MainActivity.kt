package com.sun.app_1

import android.Manifest
import android.content.Intent
import android.os.Bundle
import android.util.Log
import com.sun.app_1.feature.activity.IntentDemoActivity
import com.sun.app_1.feature.activity.LifeCycleDemoActivity
import com.sun.app_1.feature.activity.StartForResultDemoActivity
import com.sun.app_1.feature.activity.TransprantDemoActivity
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
        tv_lifecycle.onClick {
            NavUtil.safeLunch(this, Intent(this@MainActivity, LifeCycleDemoActivity::class.java))
        }
        tv_transprant.onClick {
            NavUtil.safeLunch(this, Intent(this@MainActivity, TransprantDemoActivity::class.java))
        }
        tv_start_for_result.onClick {
            NavUtil.safeLunchWithAnim(
                this,
                Intent(this@MainActivity, StartForResultDemoActivity::class.java), 5
            )
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        Log.i("startForResult", "requestCode = ${requestCode}; resultCode = ${resultCode}")
    }

    private fun initView() {

    }


}