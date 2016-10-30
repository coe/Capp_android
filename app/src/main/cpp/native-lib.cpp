#include <jni.h>
#include <string>
#include "AndroidMainNative.h"
#define SAFE_DELETE(p) { if (p){ delete p; } p = NULL; }

extern "C" {
// フィールド情報
struct fields_t {
    jfieldID    context;
};
static fields_t fields;

/**
 * インスタンス取得
 */
static AndroidMainNative* getInstance(JNIEnv* env, jobject thiz)
{
    if (fields.context == NULL) {
        return NULL;
    }
    AndroidMainNative* const ptr = (AndroidMainNative*)env->GetLongField(thiz, fields.context);
    ptr->setEnv(env);
    ptr->setThiz(thiz);
    return ptr;
}

/**
 * インスタンス保存
 */
static void setInstance(JNIEnv* env, jobject thiz, AndroidMainNative* na)
{
    env->SetLongField(thiz, fields.context, (jlong)na);
}

/**
 * 初期化
 */
void JNICALL Java_jp_coe_capp_MainActivity_init(JNIEnv *env, jobject thiz)
{
    jclass clazz;

    // クラス検索
    clazz = env->FindClass("jp/coe/capp/MainActivity"); // クラス名
    if (clazz == NULL) {
        return;
    }
    fields.context = env->GetFieldID(clazz, "mNativeContext", "J"); // "J"は long型
    if (fields.context == NULL) {
        return;
    }

    // クラス生成
    AndroidMainNative *na = new AndroidMainNative();
    setInstance(env, thiz, na);
}

/**
 * 破棄
 */
void JNICALL Java_jp_co_test_ndk_NativeAccess_native_1destroy(JNIEnv *env, jobject thiz)
{
    AndroidMainNative* ptr = getInstance(env, thiz);
    if (ptr == NULL) {
        return;
    }
    SAFE_DELETE(ptr);
    fields.context = NULL;
}


void
Java_jp_coe_capp_MainActivity_onClickFromJNI(
        JNIEnv *env,
        jobject  thiz) {
    AndroidMainNative* ptr = getInstance(env, thiz);
    ptr->onClick();
}

jstring
Java_jp_coe_capp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


}

