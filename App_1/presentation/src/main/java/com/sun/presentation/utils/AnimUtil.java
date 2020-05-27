package com.sun.presentation.utils;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.animation.AnimatorSet;
import android.animation.ObjectAnimator;
import android.animation.ValueAnimator;
import android.view.View;
import android.view.animation.LinearInterpolator;
import android.widget.TextView;

import static android.animation.ValueAnimator.INFINITE;

/**
 * @author sunquan
 * sunquan@bitstarlight.com
 * @date 2018/8/22
 **/
public class AnimUtil {
    public static final long DEFAULT_TIME = 300;


    public static void fadeIn(View view) {
        fadeIn(view, DEFAULT_TIME);
    }

    public static void fadeIn(View view, long time) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 0f, 1.0f));
        set.setDuration(time);
        set.start();
    }

    public static void fadeIn(View view, long time, AnimEndListener listener) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 0f, 1.0f));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }


    public static void fadeIn(View view, AnimEndListener listener) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 0f, 1.0f));
        set.setDuration(DEFAULT_TIME);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }

    public static void gameAnimIn(View view, AnimEndListener listener) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 0f, 1.0f));
        set.play(ObjectAnimator.ofFloat(view, "scaleX", 0f, 1.3f, 1.2f));
        set.play(ObjectAnimator.ofFloat(view, "scaleY", 0f, 1.3f, 1.2f));
        set.setDuration(DEFAULT_TIME);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }

    public static void gameAnimOut(View view, AnimEndListener listener) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 1.0f, 0f));
        set.play(ObjectAnimator.ofFloat(view, "scaleX", 1.0f, 0f));
        set.play(ObjectAnimator.ofFloat(view, "scaleY", 1.0f, 0f));
        set.setDuration(DEFAULT_TIME);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }


    public static void gameAnimOut(View view, Long time, AnimEndListener listener) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 1.0f, 0f));
        set.play(ObjectAnimator.ofFloat(view, "scaleX", 1.0f, 0f));
        set.play(ObjectAnimator.ofFloat(view, "scaleY", 1.0f, 0f));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }

    public static void fadeOut(View view, AnimEndListener listener) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 1.0f, 0f));
        set.setDuration(DEFAULT_TIME);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }

    public static void fadeOut(View view, long time, AnimEndListener listener) {
        if (view == null) {
            return;
        }
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "alpha", 1.0f, 0f));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }

    public static AnimatorSet translationY(View view, float from, float to, AnimEndListener listener) {
        return translationY(view, from, to, DEFAULT_TIME, listener);
    }

    public static AnimatorSet scale(View view, float from, float to, long animDuration, AnimEndListener listener) {
        AnimatorSet set = genScale(view, from, to, animDuration, listener);
        set.start();
        return set;
    }

    public static AnimatorSet genScale(View view, float from, float to, long animDuration, AnimEndListener listener) {
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "scaleX", from, to));
        set.play(ObjectAnimator.ofFloat(view, "scaleY", from, to));
        set.setDuration(animDuration);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        return set;
    }

    public static ObjectAnimator rotateView(View view,int duration) {
        /*view.setPivotX(view.getMeasuredHeight() / 2);
        view.setPivotY(view.getMeasuredWidth() / 2);*/
        ObjectAnimator anim = ObjectAnimator.ofFloat(view, "rotation", 0, 360);
        anim.setRepeatCount(INFINITE);
        anim.setDuration(duration);
        anim.setInterpolator(new LinearInterpolator());
        anim.start();
        return anim;
    }

    public static AnimatorSet rotate(View view, float fromDegree, float toDegree, AnimEndListener listener) {
        AnimatorSet set = new AnimatorSet();
        view.setPivotX(view.getMeasuredHeight() / 2);
        view.setPivotY(view.getMeasuredWidth() / 2);
        set.play(ObjectAnimator.ofFloat(view, "rotation", fromDegree, toDegree));
        set.setDuration(DEFAULT_TIME);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
        return set;
    }


    public static AnimatorSet scale(View view, float from, float to, AnimEndListener listener) {
        return scale(view, from, to, DEFAULT_TIME, listener);
    }


    public static AnimatorSet translationY(View view, float from, float to, long time, AnimEndListener listener) {
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "translationY", from, to));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
        return set;
    }

    public static AnimatorSet translationYWithAlpha(View view, float from, float to, boolean isShow, long time, AnimEndListener listener) {
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "translationY", from, to))
                .with(ObjectAnimator.ofFloat(view, "alpha", isShow ? 0f : 1f, isShow ? 1f : 0f));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
        return set;
    }


    public static AnimatorSet translationX(View view, float from, float to, long time, AnimEndListener listener) {
        if (view == null) return null;
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "translationX", from, to));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
        return set;
    }

    public static AnimatorSet translationXWithAlpha(View view, float from, float to, boolean isShow, Long time, AnimEndListener listener) {
        if (view == null) return null;
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "translationX", from, to))
                .with(ObjectAnimator.ofFloat(view, "alpha", isShow ? 0f : 1f, isShow ? 1f : 0f));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
        return set;
    }

    public static AnimatorSet translationXWithAlpha(View view, float from, float to, float fromAlpha, float toAlpha, Long time, AnimEndListener listener) {
        if (view == null) return null;
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view, "translationX", from, to))
                .with(ObjectAnimator.ofFloat(view, "alpha", fromAlpha, toAlpha));
        set.setDuration(time);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
        return set;
    }

    public static void fadeSwitch(View view1, View view2, AnimEndListener listener) {
        view1.setAlpha(1.0f);
        view2.setAlpha(1.0f);
        view1.setVisibility(View.GONE);
        view2.setVisibility(View.VISIBLE);
        AnimatorSet set = new AnimatorSet();
        set.play(ObjectAnimator.ofFloat(view2, "alpha", 0f, 1.0f));
        set.setDuration(DEFAULT_TIME);
        set.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                if (listener != null) {
                    listener.animEnd();
                }
            }
        });
        set.start();
    }

    public static ObjectAnimator fadeInOf(View anchor, int duration) {
        return fadeInOf(anchor, duration, 1);
    }

    public static ObjectAnimator fadeInOf(View anchor, int duration, float targetValue) {
        ObjectAnimator objectAnimator = ObjectAnimator.ofFloat(anchor, "alpha", 0, targetValue);
        objectAnimator.setDuration(duration);
        objectAnimator.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationStart(Animator animation) {
                anchor.setVisibility(View.VISIBLE);
            }
        });
        return objectAnimator;
    }

    public static ObjectAnimator fadeOutOf(View anchor, int duration) {
        return fadeOutOf(anchor, duration, 1);
    }

    public static ObjectAnimator fadeOutOf(View anchor, int duration, float initialValue) {
        anchor.setVisibility(View.VISIBLE);
        ObjectAnimator objectAnimator = ObjectAnimator.ofFloat(anchor, "alpha", initialValue, 0);
        objectAnimator.setDuration(duration);
        objectAnimator.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                anchor.setAlpha(1.0f);
                anchor.setVisibility(View.GONE);
            }
        });
        return objectAnimator;
    }

    public static void numberTimer(TextView view, int start, int end) {
        ValueAnimator valueAnimator = ValueAnimator.ofInt(start, end);
        valueAnimator.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
            @Override
            public void onAnimationUpdate(ValueAnimator valueAnimator) {
                view.setText(valueAnimator.getAnimatedValue() + "");
            }
        });
        valueAnimator.setDuration(DEFAULT_TIME);
        valueAnimator.start();
    }

    public interface AnimEndListener {
        void animEnd();
    }
}
