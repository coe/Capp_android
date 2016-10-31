#include <jni.h>
#include <string>
#include "AndroidMainNative.h"
#define SAFE_DELETE(p) { if (p){ delete p; } p = NULL; }

JavaVM * savedVM = NULL;
jobject saved_listener_instance;

JNIEXPORT void JNICALL
Java_jp_coe_capp_MainActivity_addListener(JNIEnv *env, jobject instance, jobject listener) {

    env->GetJavaVM( &savedVM );
    //save listener_instance for use later
    saved_listener_instance = listener;


}

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

void doSomething()
{
    //Get current thread JNIEnv
    JNIEnv * ENV;
    int stat = savedVM->GetEnv((void **)&ENV, JNI_VERSION_1_6);
    if (stat == JNI_EDETACHED)  //We are on a different thread, attach
        savedVM->AttachCurrentThread((JNIEnv **) &ENV, NULL);
    if( ENV == NULL )
        return;  //Cant attach to java, bail

    //Get the Listener class reference
    jclass listenerClassRef = ENV->GetObjectClass( saved_listener_instance );

    //Use Listener class reference to load the eventOccurred method
    jmethodID listenerEventOccured = ENV->GetMethodID( listenerClassRef, "eventOccurred", "()V" );

    //Get Info class reference
    jclass infoClsRef = ENV->FindClass( "Info" );

//    //Create Info class
//    jobject info_instance = ENV->NewObject( infoClsRef, ..... );//For you to fill in with your arguments

    //invoke listener eventOccurred
    ENV->CallVoidMethod( saved_listener_instance, listenerEventOccured );

//    //Cleanup
//    ENV->DeleteLocalRef( info_instance );
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

