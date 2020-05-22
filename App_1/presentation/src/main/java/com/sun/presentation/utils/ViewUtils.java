package com.sun.presentation.utils;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.graphics.Outline;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Build;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.KeyCharacterMap;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.ViewGroup;
import android.view.ViewOutlineProvider;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.FrameLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import androidx.core.app.NotificationManagerCompat;
import androidx.recyclerview.widget.RecyclerView;

import com.sun.presentation.components.PresentationApp;

import java.lang.reflect.Method;

import static android.content.Context.CLIPBOARD_SERVICE;

public class ViewUtils {
    private static Typeface typeFace;
    private static int deviceHeight = 0;
    private static int deviceWidth = 0;
    private static final String NAV_BAR_HEIGHT_RES_NAME = "navigation_bar_height";
    private static final String NAV_BAR_HEIGHT_LANDSCAPE_RES_NAME = "navigation_bar_height_landscape";

    public static int dp2px(float dp) {
        final float scale = PresentationApp.inst().getApp().getResources().getDisplayMetrics().density;
        return (int) (dp * scale + 0.5f);
    }

    public static int sp2px(float sp) {
        final float scale = PresentationApp.inst().getApp().getResources().getDisplayMetrics().scaledDensity;
        return (int) (sp * scale + 0.5f);
    }

    public static int px2dp(int px) {
        return (int) (px / getDensity() + 0.5);
    }

    public static float getDensity() {
        return PresentationApp.inst().getApp().getResources().getDisplayMetrics().density;
    }

    public static int getDeviceWidth() {
        if (deviceWidth == 0) {
            WindowManager wm = (WindowManager) PresentationApp.inst().getApp().getSystemService(Context.WINDOW_SERVICE);
            Display d = wm.getDefaultDisplay();
            DisplayMetrics realDisplayMetrics = new DisplayMetrics();
            d.getRealMetrics(realDisplayMetrics);
            deviceWidth = realDisplayMetrics.widthPixels;
        }
        return deviceWidth;
    }

    public static int getDeviceHeight() {
        if (deviceHeight == 0) {
            WindowManager wm = (WindowManager) PresentationApp.inst().getApp().getSystemService(Context.WINDOW_SERVICE);
            Display d = wm.getDefaultDisplay();
            DisplayMetrics realDisplayMetrics = new DisplayMetrics();
            d.getRealMetrics(realDisplayMetrics);
            deviceHeight = realDisplayMetrics.heightPixels;
        }
        return deviceHeight;
    }

    public static int getScreenWidth() {
        WindowManager wm = (WindowManager) PresentationApp.inst().getApp().getSystemService(Context.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        return DisplayCompat.getWidth(display);
    }

    public static int getScreenHeight() {
        WindowManager wm = (WindowManager) PresentationApp.inst().getApp().getSystemService(Context.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        return DisplayCompat.getHeight(display);
    }

    public static boolean isNotificationEnabled(Context context) {
        NotificationManagerCompat notificationManagerCompat = NotificationManagerCompat.from(context);
        boolean areNotificationsEnabled = notificationManagerCompat.areNotificationsEnabled();
        return areNotificationsEnabled;
    }

    //获取NavigationBar的高度
    @TargetApi(14)
    public static int getNavigationBarHeight(Activity context) {
        Resources res = context.getResources();
        int result = 0;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH) {
            String key;
            if (isInPortrait(context)) {
                key = NAV_BAR_HEIGHT_RES_NAME;
            } else {
                key = NAV_BAR_HEIGHT_LANDSCAPE_RES_NAME;
            }
            return getInternalDimensionSize(res, key);
        }
        return result;
    }

    //通过此方法获取资源对应的像素值
    private static int getInternalDimensionSize(Resources res, String key) {
        int result = 0;
        int resourceId = res.getIdentifier(key, "dimen", "android");
        if (resourceId > 0) {
            result = res.getDimensionPixelSize(resourceId);
        }
        return result;
    }

    public static boolean isInPortrait(Activity context) {
        Resources res = context.getResources();
        return (res.getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT);
    }

    /**
     * 判断是否有虚拟按键
     *
     * @param context
     * @return
     */
    public static boolean checkDeviceHasNavigationBar(Context context) {
        boolean hasNavigationBar = false;
        Resources rs = context.getResources();
        int id = rs.getIdentifier("config_showNavigationBar", "bool", "android");
        if (id > 0) {
            hasNavigationBar = rs.getBoolean(id);
        }
        try {
            Class systemPropertiesClass = Class.forName("android.os.SystemProperties");
            Method m = systemPropertiesClass.getMethod("get", String.class);
            String navBarOverride = (String) m.invoke(systemPropertiesClass, "qemu.hw.mainkeys");
            if ("1".equals(navBarOverride)) {
                hasNavigationBar = false;
            } else if ("0".equals(navBarOverride)) {
                hasNavigationBar = true;
            }
        } catch (Exception e) {
        }
        return hasNavigationBar;
    }

    public static boolean isNavigationBarShow(Activity context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            Display display = context.getWindowManager().getDefaultDisplay();
            Point size = new Point();
            Point realSize = new Point();
            display.getSize(size);
            display.getRealSize(realSize);
            return realSize.y != size.y;
        } else {
            boolean menu = ViewConfiguration.get(context).hasPermanentMenuKey();
            boolean back = KeyCharacterMap.deviceHasKey(KeyEvent.KEYCODE_BACK);
            return !menu && !back;
        }
    }

    public static void setMargins(View v, int l, int t, int r, int b) {
        if (v != null && v.getLayoutParams() instanceof ViewGroup.MarginLayoutParams) {
            ViewGroup.MarginLayoutParams p = (ViewGroup.MarginLayoutParams) v.getLayoutParams();
            p.setMargins(l, t, r, b);
            v.requestLayout();
        }
    }

    public static void fitScreen(View view, int videoWidth, int videoHeight) {
        FrameLayout.LayoutParams layoutParams = (FrameLayout.LayoutParams) view.getLayoutParams();
        int screenWidth = ViewUtils.getScreenWidth();
        int screenHeight = ViewUtils.getScreenHeight();
        float screenRatio = (float) screenWidth / screenHeight;
        float videoRatio = (float) videoWidth / videoHeight;
        if (videoRatio > screenRatio) {
            // 视频宽高比大于屏幕，需要设置控件高变低
            layoutParams.width = screenWidth;
            layoutParams.height = (int) (screenWidth / videoRatio);
            layoutParams.topMargin = (screenHeight - layoutParams.height) / 2;
            if (layoutParams.topMargin < 0) {
                layoutParams.topMargin = 0;
            }
        } else {
            layoutParams.height = screenHeight;
            layoutParams.width = (int) (screenHeight * videoRatio);
            layoutParams.leftMargin = (screenWidth - layoutParams.width) / 2;
            if (layoutParams.leftMargin < 0) {
                layoutParams.leftMargin = 0;
            }
        }
        view.setLayoutParams(layoutParams);
    }

    public static void toggleInput(View view, boolean show) {
        InputMethodManager imm = (InputMethodManager) view.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        if (show) {
            imm.showSoftInput(view, InputMethodManager.SHOW_IMPLICIT);
        } else {
            imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
        }
    }

    /**
     * 切换软键盘的状态
     * 如当前为收起变为弹出,若当前为弹出变为收起
     */
    public static void toggleInput(Context context) {
        InputMethodManager inputMethodManager =
                (InputMethodManager) context.getSystemService(Context.INPUT_METHOD_SERVICE);
        inputMethodManager.toggleSoftInput(0, InputMethodManager.HIDE_NOT_ALWAYS);
    }

    public static void setTextView(TextView textView, Object object) {
        if (textView != null) {
            textView.setText(object != null ? object.toString().trim() : "");
        }
    }

    //截取指定长度
    public static void setTextView(TextView textView, Object object, int endIndex, String endStr) {
        if (textView != null && object != null) {
            String text = object.toString().trim();
            int textLength = text.length();
            if (endIndex < textLength) {
                text = text.substring(0, endIndex) + endStr;
            }
            textView.setText(text);
        }
    }

    public static void setTvFonts(TextView textView) {
        if (typeFace == null) {
            typeFace = Typeface.createFromAsset(PresentationApp.inst().getApp().getResources().getAssets(), "fonts/AvenirNextLTPro-BoldCn.otf");
        }
        textView.setTypeface(typeFace);
    }

    public static void setBackground(Context context, View view, int id) {
        if (view != null) {
            view.setBackgroundColor(context.getResources().getColor(id));
        }
    }

    public static void setTextColor(Context context, TextView view, int id) {
        if (view != null) {
            view.setTextColor(context.getResources().getColor(id));
        }
    }

    /**
     * 设置 TextView 的中划线
     *
     * @param textView
     */
    public static void setTvCenterLine(TextView textView) {
        if (textView != null) {
            textView.setPaintFlags(Paint.ANTI_ALIAS_FLAG | Paint.ANTI_ALIAS_FLAG);
            textView.getPaint().setFlags(Paint.STRIKE_THRU_TEXT_FLAG); //中划线
            //一定要写在最后否则会出现锯齿
            textView.getPaint().setAntiAlias(true);//抗锯齿
        }
    }

    /**
     * 设置 TextView 的下划线
     *
     * @param textView
     */
    public static void setTvBottomLine(TextView textView) {
        if (textView != null) {
            textView.setPaintFlags(Paint.ANTI_ALIAS_FLAG | Paint.ANTI_ALIAS_FLAG);
            textView.getPaint().setFlags(Paint.UNDERLINE_TEXT_FLAG); //下划线
            //一定要写在最后否则会出现锯齿
            textView.getPaint().setAntiAlias(true);//抗锯齿
        }
    }

    public static void setRvItemHeight(RecyclerView.ViewHolder itemViewHolder, int mItemHeight) {
        ViewGroup.LayoutParams layoutParams = itemViewHolder.itemView.getLayoutParams();
        layoutParams.height = mItemHeight;
        itemViewHolder.itemView.setLayoutParams(layoutParams);
    }

    public static void setRvItemWH(RecyclerView.ViewHolder itemViewHolder, int itemWidth, int itemHeight) {
        if (itemWidth == 0 || itemHeight == 0) {
            return;
        }

        ViewGroup.LayoutParams layoutParams = itemViewHolder.itemView.getLayoutParams();
        layoutParams.width = itemWidth;
        layoutParams.height = itemHeight;
        itemViewHolder.itemView.setLayoutParams(layoutParams);
    }

    // 两次点击按钮之间的点击间隔不能少于1000毫秒
    private static final int MIN_CLICK_DELAY_TIME = 200;
    private static long lastClickTime;

    public static boolean isNotFastClick() {
        boolean flag = false;
        long curClickTime = System.currentTimeMillis();
        if ((curClickTime - lastClickTime) >= MIN_CLICK_DELAY_TIME) {
            flag = true;
        }
        lastClickTime = curClickTime;
        return flag;
    }

    public static void setScrollViewShadow(ScrollView scrollView, View vShadow) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            scrollView.setOnScrollChangeListener(new View.OnScrollChangeListener() {
                @Override
                public void onScrollChange(View v, int scrollX, int scrollY, int oldScrollX, int oldScrollY) {
                    int verticalOffset = scrollView.getScrollY();
                    if (verticalOffset > 20) {
                        vShadow.setVisibility(View.VISIBLE);
                    } else if (verticalOffset == 0) {
                        vShadow.setVisibility(View.GONE);
                    }
                }
            });
        }
    }

    /**
     * 打开设置通知页面
     *
     * @param activity
     */
    public static void openSysAppPushPage(Activity activity) {
        if (!activity.isFinishing()) {
            Intent localIntent = new Intent();
            localIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            if (Build.VERSION.SDK_INT >= 9) {
                localIntent.setAction("android.settings.APPLICATION_DETAILS_SETTINGS");
                localIntent.setData(Uri.fromParts("package", PresentationApp.inst().getApp().getPackageName(), null));
            } else if (Build.VERSION.SDK_INT <= 8) {
                localIntent.setAction(Intent.ACTION_VIEW);

                localIntent.setClassName("com.android.settings",
                        "com.android.settings.InstalledAppDetails");

                localIntent.putExtra("com.android.settings.ApplicationPkgName",
                        PresentationApp.inst().getApp().getPackageName());
            }
            activity.startActivity(localIntent);
        }
    }

    public static void configViewOutlineProvider(View view, float radius) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            view.setOutlineProvider(new ViewOutlineProvider() {
                @Override
                public void getOutline(View view, Outline outline) {
                    outline.setRoundRect(0, 0, view.getWidth(),
                            view.getHeight(),
                            ViewUtils.dp2px(radius));
                }
            });
            view.setClipToOutline(true);
        }
    }

    public static void configViewOutlineProvider(View view) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            view.setOutlineProvider(ViewOutlineProvider.PADDED_BOUNDS);
            view.setClipToOutline(true);
        }
    }


    public static boolean isDevice9X18() {
        return (double) ViewUtils.getScreenWidth() / ViewUtils.getScreenHeight() <= (double) 9 / 18;
    }

    public static boolean isDevice95X18() {
        return (double) ViewUtils.getScreenWidth() / ViewUtils.getScreenHeight() <= (double) 9.5 / 18;
    }

    public static void copyToClipboard(String text) {
        ClipboardManager clipboardManager = (ClipboardManager) PresentationApp.inst().getApp().getSystemService(Context.CLIPBOARD_SERVICE);
        if (clipboardManager == null) {
            return;
        }

        final ClipData text1 = ClipData.newPlainText("text", text);
        clipboardManager.setPrimaryClip(text1);
    }

    /**
     * 获取剪切板中的文字
     *
     * @return
     */
    public static String getClipContent() {
        String content = "";
        try {
            ClipboardManager cm = (ClipboardManager) PresentationApp.inst().getApp().getSystemService(CLIPBOARD_SERVICE);
            ClipData data = cm.getPrimaryClip();
            ClipData.Item item = data.getItemAt(0);
            content = item.getText().toString();
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        return content;
    }

    public static String getClipContentWithRemove() {
        String content = getClipContent();
        copyToClipboard("");
        return content;
    }

}
