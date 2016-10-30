//
//  MainNative.hpp
//  Capp
//
//  Created by COFFEE on 2016/10/29.
//  Copyright © 2016年 COFFEE. All rights reserved.
//

#ifndef MainNative_hpp
#define MainNative_hpp

#include <stdio.h>
#include <functional>

class MainNative {
    
public:
    virtual ~MainNative() {};
    void test();
    void onClick();
    virtual void showDiarog() = 0;
    virtual void connect(std::function< void() > callback) = 0;
    virtual void dismiss() = 0;
    virtual void playSound() = 0;
};

#endif /* MainNative_hpp */
