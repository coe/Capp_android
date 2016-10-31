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


//JNIEXPORT void JNICALL
//Java_jp_coe_capp_MainActivity_setObserver(JNIEnv *env, jobject instance, jobject javaobserver) {
//
//    //Retrieve the CPP version of MyLibrary. For me, I stored it inside the java
//    //object as a field, but you can implement it any way you want.
//    AndroidMainNative* cppMyLibrary = getInstance(env, instance);
//
//    if (cppMyLibrary == NULL) {
//        //Handle the problem
//        return;
//    }
//    jthrowable exc = NULL;
//
//    //Keep the jvm object around; the env is not available in another thread
//    //but can be obtained from the jvm.
//    JavaVM* jvm;
//    env->GetJavaVM(&jvm);
//
//    //The observer has to be made global; it's not available in another thread.
//    jobject observer = env->NewGlobalRef(observer);
//    //TODO: retrieve the previous observer and clean it up with DeleteGlobalRef()
//    //TODO: clean up this observer when destroying MyLibrary with DeleteGlobalRef()
//
//    try {
//        //At this point, both "jvm" and "observer" are accessible from the other thread.
//        cppMyLibrary->setLogFunction([jvm, observer] (std::string& p0, std::string& p1) {
//            JNIEnv* env;
//            jvm->AttachCurrentThread(&env, NULL); //Obtain the env
//            jclass clazz = env->GetObjectClass(observer);
//            jmethodID meth = env->GetMethodID(clazz, "log",
//                                              "(Ljava/lang/String;Ljava/lang/String;)V");
//            jstring s0 = env->NewStringUTF(p0.c_str());
//            jstring s1 = env->NewStringUTF(p1.c_str());
//            env->CallVoidMethod(observer, meth, s0, s1);
//
//            //TODO: make sure this is called even if there's an exception!
//            jvm->DetachCurrentThread();
//        });
//    } catch (...) {
//        exc = //handle your exceptions here
//    }
//
//    if (exc != NULL) {
//        env->Throw(exc);
//    }
//
//}


JNIEXPORT void JNICALL
Java_jp_coe_capp_MainActivity_init(JNIEnv *env, jobject instance, jobject observer) {

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
    setInstance(env, instance, na);

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

