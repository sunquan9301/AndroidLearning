package com.sun.app_1.feature.activity

import android.content.Intent
import com.sun.app_1.R
import com.sun.presentation.BaseActivity
import kotlinx.android.synthetic.main.activity_intent_demo.*


/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2020/5/23
 **/
class IntentDemoActivity : BaseActivity() {
    override fun getLayoutId(): Int {
        return R.layout.activity_intent_demo
    }

    override fun startInit() {
        //action_view 用于显示用户的数据，通过传递的data调用到相应的页面
        action_view.onClick {
            //            //打开浏览器
//            val uri: Uri = Uri.parse("http://www.baidu.com") //浏览器(网址必须带http)
//            startActivity(Intent(Intent.ACTION_VIEW, uri))
//


//            //播放视频
//            val intent = Intent(Intent.ACTION_VIEW)
//            val uri = Uri.parse("file:///sdcard/media.mp4")
//            intent.setDataAndType(uri, "video/*")
//            startActivity(intent)

            //发送短信
            val intent1 = Intent(Intent.ACTION_VIEW)
            intent1.putExtra("sms_body", "信息内容...")
            intent1.type = "vnd.android-dir/mms-sms"
            startActivity(intent1)
        }
    }
}