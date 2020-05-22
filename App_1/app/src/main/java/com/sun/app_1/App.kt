package com.sun.app_1

import android.content.Context
import androidx.multidex.MultiDex
import androidx.multidex.MultiDexApplication
import com.sun.presentation.components.PresentationApp


/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2019/7/18
 **/
open class App : MultiDexApplication() {
    var appStartTime: Long = 0


    override fun onCreate() {
        super.onCreate()
        sApp = this
        PresentationApp.inst().init(this)
    }

    // 用于在调试的时候修改Component的
    open protected fun getComponentCallback(): Runnable? {
        return null
    }


//    fun <T : AbsComponent> getComponent(clazz: Class<T>): T {
//        return appRuntime.getComponent(clazz)
//    }

    override fun attachBaseContext(base: Context?) {
        super.attachBaseContext(base)
        MultiDex.install(this)
        appStartTime = System.currentTimeMillis()

    }

    companion object {
        const val MAIN_PROCESS_NAME = BuildConfig.APPLICATION_ID
        const val TAG = "App"

        var sApp: App = App()

        fun inst(): App {
            return sApp
        }

        fun exit() {
            System.exit(0)
        }
    }

}