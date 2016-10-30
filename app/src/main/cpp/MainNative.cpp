//
//  MainNative.cpp
//  Capp
//
//  Created by COFFEE on 2016/10/29.
//  Copyright © 2016年 COFFEE. All rights reserved.
//

#include "MainNative.hpp"
#include <iostream>

void MainNative::test() {
}

void MainNative::onClick() {
    //ダイアログ出す
    showDiarog();

    //固定URLに対して非同期通信を行う
    //通信コールバックで震える
    std::function<void ()> callback = [this]{
        std::cout << "BLAH!" << std::endl;
        this->playSound();
        dismiss();
    };
    connect(callback);
    
    
    
}
