#include <jni.h>
#include <android/bitmap.h>
#include <math.h>


#ifndef eprintf
#define eprintf(...) __android_log_print(ANDROID_LOG_ERROR,"@",__VA_ARGS__)
#endif

/**
 * 计算两点间距离的平方
 */
float getDistance(float x0,float y0,float x1,float y1){
    return fabsf(x0-x1)*fabsf(x0-x1)+fabs(y0-y1)*fabs(y0-y1);
}



void argb_8888(JNIEnv* env,AndroidBitmapInfo & info,jobject jbitmap,int angle){
    float  min = fminf(info.width,info.height);//宽高的最小值
    float r = angle>min/2?min/2:angle;//得到半径
    float rr = r*r;//半径平方

    uint32_t * data32 = NULL;
    AndroidBitmap_lockPixels(env,jbitmap,(void**)&data32);
    if(data32!=NULL) {
        uint32_t rx = info.width / 2;
        uint32_t ry = info.height / 2;
        if (r == angle) {//是导角
            int tempy = r;
            for (int y = 0; y < info.height; ++y) {
                if (y < ry && y > tempy) {
                    y = info.height - r;
                    tempy = y;
                } else {
                    for (int x = 0; x < info.width; ++x) {
                        if (x > rx || getDistance(r, tempy, x, y) > rr) {//在圆外
                            uint32_t argb = data32[y * info.width + x];
                            data32[y * info.width + x] = argb & 0x0;
                        } else {//在圆内
                            if (x < rx) {
                                x = rx * 2 - x;
                            }
                        }
                    }
                }
            }
        } else {//一整个圆
            for (int y = 0; y < info.height; ++y) {
                for (int x = 0; x < info.width; ++x) {
                    if (x > rx || getDistance(rx, ry, x, y) > rr) {//在圆外
                        uint32_t argb = data32[y * info.width + x];
                        data32[y * info.width + x] = argb & 0x0;
                    } else {//在圆内
                        if (x < rx) {
                            x = rx * 2 - x;
                        }
                    }
                }
            }
        }
        AndroidBitmap_unlockPixels(env, jbitmap);
    }
}

void argb_4444(JNIEnv* env,AndroidBitmapInfo & info,jobject jbitmap,int angle){
    float  min = fminf(info.width,info.height);//宽高的最小值
    float r = angle>min/2?min/2:angle;//得到半径
    float rr = r*r;//半径平方

    uint16_t * data16 = NULL;
    AndroidBitmap_lockPixels(env,jbitmap,(void**)&data16);
    if(data16!=NULL) {
        uint16_t rx = info.width / 2;
        uint16_t ry = info.height / 2;
        if (r == angle) {//是导角
            int tempy = r;
            for (int y = 0; y < info.height; ++y) {
                if (y < ry && y > tempy) {
                    y = info.height - r;
                    tempy = y;
                } else {
                    for (int x = 0; x < info.width; ++x) {
                        if (x > rx || getDistance(r, tempy, x, y) > rr) {//在圆外
                            uint16_t argb = data16[y * info.width + x];
                            data16[y * info.width + x] = argb & 0x0;
                        } else {//在圆内
                            if (x < rx) {
                                x = rx * 2 - x;
                            }
                        }
                    }
                }
            }
        } else {//一整个圆
            for (int y = 0; y < info.height; ++y) {
                for (int x = 0; x < info.width; ++x) {
                    if (x > rx || getDistance(rx, ry, x, y) > rr) {//在圆外
                        uint16_t argb = data16[y * info.width + x];
                        data16[y * info.width + x] = argb & 0x0;
                    } else {//在圆内
                        if (x < rx) {
                            x = rx * 2 - x;
                        }
                    }
                }
            }
        }
        AndroidBitmap_unlockPixels(env, jbitmap);
    }
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_jkwy_lib_bitmap_UtilBitmap_cirBitmap(JNIEnv* env,jclass type, jobject jbitmap,jint angle) {
    AndroidBitmapInfo info={0,0,0,0,0};
    if(AndroidBitmap_getInfo(env,jbitmap,&info)<-1){
        return jbitmap;
    }
    AndroidBitmapInfo & bitmapInfo = info;
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888){
        argb_8888(env,bitmapInfo,jbitmap,angle);
    }else if(info.format == ANDROID_BITMAP_FORMAT_RGBA_4444){
        argb_4444(env,bitmapInfo,jbitmap,angle);
    }
    return jbitmap;
}




