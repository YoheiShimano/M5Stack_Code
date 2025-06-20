/* インクルードガード */
#pragma once
#include "DrTHSensor.h"
#include "M5All-In-One-Gadget.h"
#include <M5Stack.h>

class MdWBGTMonitor // classの定義
{
private: // privateはクラス内からしかアクセスできない
    DrTHSensor dthsen; //温湿度センサーの初期化

public: // publicはどこからでもアクセス可能
    //MdWBGTMonitor(); //コンストラクタ
    void init();
    void getWBGT(double* temperature, double* humidity, WbgtIndex* index);
};