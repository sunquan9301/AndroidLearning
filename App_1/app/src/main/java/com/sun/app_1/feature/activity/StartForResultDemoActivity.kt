package com.sun.app_1.feature.activity

import android.app.Activity
import android.content.Intent
import com.sun.app_1.R
import com.sun.presentation.BaseActivity
import kotlinx.android.synthetic.main.activity_intent_demo.*
import kotlinx.android.synthetic.main.activity_start_for_result_demo.*


/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2020/5/23
 **/
class StartForResultDemoActivity : BaseActivity() {
    override fun getLayoutId(): Int {
        return R.layout.activity_start_for_result_demo
    }

    override fun startInit() {
        //action_view 用于显示用户的数据，通过传递的data调用到相应的页面
        tv_finish.onClick {
            val i: Intent = Intent()
            i.putExtra("result", "ok")
            setResult(Activity.RESULT_OK, i)
            finish()
        }
    }

    override fun onBackPressed() {
        super.onBackPressed()
    }
}