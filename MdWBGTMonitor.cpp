#include "MdWBGTMonitor.h"
#include "DrTHSensor.h"
#include "M5All-In-One-Gadget.h"
#include <M5Stack.h>

DrTHSensor dthsen;//DrTHSensorクラスのインスタンス

void MdWBGTMonitor::init() {
    dthsen.init();//温度センサーの初期化
}

//計算結果によってアラートの分類を分ける
void MdWBGTMonitor::getWBGT(double* temperature, double* humidity, WbgtIndex* index) {
    double temperature = 0;
    double humidity = 0;
    WbgtIndex index;
    int calc_index; 

    dthsen.getTempHumi(temperature, humidity);
    calc_index = 0.68 * (*temperature) + 0.12 * (*humidity);//calc_indexにWBGTの計算結果を格納
    //int calc_index //WBGTの計算結果を格納する
    //WbgtIndex *	index	アラートを代入する変数のアドレス

    if (calc_index <= 15) {
        *index = SAFE;
    } else if (calc_index <= 24) {
        *index = ATTENTION;
    } else if (calc_index <= 27) {
        *index = ALERT;
    } else if (calc_index <= 30) {
        *index = HIGH_ALERT;
    } else if (calc_index >= 31){
        *index = DANGER;
    }
}