//
// Created by COFFEE on 2016/10/30.
//

#include "AndroidMainNative.h"
#include <iostream>


AndroidMainNative::AndroidMainNative() {

}

void AndroidMainNative::showDiarog(){
    jclass clazz = env_->FindClass("jp/coe/capp/MainActivity");
    jmethodID messageMe = env_->GetMethodID(clazz, "showDiarog","()V");

    env_->CallVoidMethod(thiz_,messageMe);
}

void AndroidMainNative::connect(std::function<void()> callback) {
    callback_ = callback;
    //TODO:コールバックどうする
    jclass clazz = env_->FindClass("jp/coe/capp/MainActivity");
    jmethodID messageMe = env_->GetMethodID(clazz, "connect","()V");

    env_->CallVoidMethod(thiz_,messageMe);

}

void AndroidMainNative::dismiss() {
    std::cout << "dismiss" << std::endl;
    jclass clazz = env_->FindClass("jp/coe/capp/MainActivity");
    jmethodID messageMe = env_->GetMethodID(clazz, "dismiss","()V");

    env_->CallVoidMethod(thiz_,messageMe);
}

void AndroidMainNative::playSound() {
    std::cout << "playSound" << std::endl;
    jclass clazz = env_->FindClass("jp/coe/capp/MainActivity");
    jmethodID messageMe = env_->GetMethodID(clazz, "playSound","()V");

    env_->CallVoidMethod(thiz_,messageMe);
}


void AndroidMainNative::connectCallback() {
    callback_();
}

void AndroidMainNative::setThiz(jobject thiz) {
    thiz_ = thiz;
}

void AndroidMainNative::setEnv(JNIEnv *env) {
    env_ = env;
}
















