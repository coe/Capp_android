package jp.coe.capp;

/**
 * Created by user on 2016/10/30.
 */

public interface MainActivityInterface {
    void showDiarog();
    void connect(MainActivityInterface connectCallback);
    void dismiss();
    void playSound();
    void connectCallback();
}
