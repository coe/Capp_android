//
// Created by COFFEE on 2016/10/30.
//

#ifndef CAPP_ANDROIDMAINNATIVE_H
#define CAPP_ANDROIDMAINNATIVE_H

#include "MainNative.hpp"
#include <jni.h>

class AndroidMainNative : public MainNative {
    JNIEnv *env_;
    jobject thiz_;
    std::function< void() > callback_;
public:
    AndroidMainNative();
    void showDiarog();
    void connect(std::function< void() > callback);
    void dismiss();
    void playSound();

    void setThiz(jobject thiz);
    void setEnv(JNIEnv *env);

    void connectCallback();
};


#endif //CAPP_ANDROIDMAINNATIVE_H
