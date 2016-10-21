package com.jkwy.lib.bitmap;

import android.graphics.Bitmap;

/**
 * Created by tangzejin on 2016/9/30.
 * 功能说明：
 */

public class UtilBitmap {
    static {
        System.loadLibrary("jkwy-bitmap");
    }

    /**
     *
     */
    public static Bitmap angleBitmap(Bitmap bitmap){
        return angleBitmap(bitmap,Integer.MAX_VALUE);
    }

    public static Bitmap angleBitmap(Bitmap bitmap,int angle){
        bitmap.setHasAlpha(true);
        return cirBitmap(bitmap,angle);
    }

    private static native Bitmap cirBitmap(Bitmap bitmap,int angle);

}
