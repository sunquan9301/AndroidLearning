package com.sun.presentation.utils;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.provider.Settings;

import com.sun.presentation.BuildConfig;
import com.sun.presentation.R;

import java.lang.reflect.Field;
import java.util.Map;

/**
 * 跳转页面
 */
public class NavUtil {

    /**
     * 跳转到某个Activity
     */
    public static void gotoActivity(Context context, Class<?> toActivityClass) {
        Intent intent = new Intent(context, toActivityClass);
        safeLunchWithAnim(context, intent);
    }

    /**
     * 跳转到某个Activity
     */
    public static void gotoActivity(Context context, Class<?> toActivityClass, Bundle bundle) {
        Intent intent = new Intent(context, toActivityClass);
        if (bundle != null) {
            intent.putExtras(bundle);
        }
        safeLunchWithAnim(context, intent);
    }

    /**
     * 跳转到某个Activity
     */
    public static void gotoActivity(Context context, Class<?> toActivityClass, Bundle bundle, boolean isAnim) {
        Intent intent = new Intent(context, toActivityClass);
        if (bundle != null) {
            intent.putExtras(bundle);
        }
        if (isAnim) {
            safeLunchWithAnim(context, intent);
        } else {
            safeLunchNoAnim(context, intent);
        }
    }

    /**
     * 跳转到某个Activity
     */
    public static void gotoActivityAndFinishNoAnim(Activity mContext, Class<?> toActivityClass, Bundle bundle) {
        Intent intent = new Intent(mContext, toActivityClass);
        if (bundle != null) {
            intent.putExtras(bundle);
        }
        mContext.startActivity(intent);
        mContext.finish();
        mContext.overridePendingTransition(0, 0);
    }

    /**
     * 跳转到某个Activity
     */
    public static void gotoActivityAndFinish(Activity mContext, Class<?> toActivityClass, Bundle bundle) {
        Intent intent = new Intent(mContext, toActivityClass);
        if (bundle != null) {
            intent.putExtras(bundle);
        }
        mContext.startActivity(intent);
        mContext.finish();
        mContext.overridePendingTransition(R.anim.push_right_in, R.anim.not_exit_push_left_out);
    }

    /**
     * 跳转到某个Activity
     */
    public static void gotoActivityAndFinishNoAnim(Activity mContext, Intent i) {
        mContext.startActivity(i);
        mContext.finish();
        mContext.overridePendingTransition(0, 0);
    }

    /**
     * 跳转到某个Activity
     */
    public static void gotoActivityAndFinish(Activity mContext, Intent i) {
        mContext.startActivity(i);
        mContext.finish();
        mContext.overridePendingTransition(R.anim.push_right_in, R.anim.not_exit_push_left_out);
    }

    /**
     * 退出到某个Activity
     */
    public static void backActivity(Activity activity) {
        if (activity != null) {
            activity.finish();
            activity.overridePendingTransition(R.anim.not_exit_push_left_in, R.anim.push_right_out);
        }
    }

    public static Activity getCurrentTopActivity() {
        try {
            Class activityThreadClass = Class.forName("android.app.ActivityThread");
            Object activityThread = activityThreadClass.getMethod("currentActivityThread").invoke(null);
            Field activitiesField = activityThreadClass.getDeclaredField("mActivities");
            activitiesField.setAccessible(true);

            Map<Object, Object> activities = (Map<Object, Object>) activitiesField.get(activityThread);
            if (activities == null) {
                return null;
            }

            for (Object activityRecord : activities.values()) {
                Class activityRecordClass = activityRecord.getClass();
                Field pausedField = activityRecordClass.getDeclaredField("paused");
                pausedField.setAccessible(true);
                if (!pausedField.getBoolean(activityRecord)) {
                    Field activityField = activityRecordClass.getDeclaredField("activity");
                    activityField.setAccessible(true);
                    Activity activity = (Activity) activityField.get(activityRecord);
                    return activity;
                }
            }
        } catch (Exception ignored) {
            ignored.printStackTrace();
            return null;
        }
        return null;
    }

    public static void safeLunch(Context context, Intent intent) {
        if (!(context instanceof Activity)) {
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        }
        safeLunchWithAnim(context, intent);
    }

    public static void safeLunchWithAnim(Context context, Intent intent) {
        safeLunchWithAnim(context, intent, -1);
    }

    public static void safeLunchWithAnim(Activity context, Intent intent, int fromAnim, int endAnim) {
        context.startActivity(intent);
        ((Activity) context).overridePendingTransition(fromAnim, endAnim);
    }

    public static void safeLunchAndFinishWithAnim(Activity context, Intent intent, int fromAnim, int endAnim) {
        context.startActivity(intent);
        context.finish();
        ((Activity) context).overridePendingTransition(fromAnim, endAnim);
    }

    public static void safeLunchWithAnim(Context context, Intent intent, int requestCode) {
        if (context instanceof Activity) {
            if (requestCode <= 0) {
                context.startActivity(intent);
            } else {
                ((Activity) context).startActivityForResult(intent, requestCode);
            }
            ((Activity) context).overridePendingTransition(R.anim.push_right_in, R.anim.not_exit_push_left_out);
        } else {
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(intent);
        }
    }

    public static void safeLunchNoAnim(Context context, Intent intent) {
        if (context instanceof Activity) {
            context.startActivity(intent);
            ((Activity) context).overridePendingTransition(0, 0);
        } else {
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(intent);
        }
    }


    public static void gotoAppPermissionSetting(Context context) {
        try {
            Uri packageURI = Uri.parse("package:" + BuildConfig.APPLICATION_ID);
            Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS, packageURI);
            safeLunchNoAnim(context, intent);
        } catch (Throwable e) {
            context.startActivity(new Intent(Settings.ACTION_MANAGE_APPLICATIONS_SETTINGS));
        }
    }
}
