#include "MdWBGTMonitor.h"

DrTHSensor dthsen;
void init();//温度センサーの初期化


void getWBGT(double* temperature, double* humidity, WbgtIndex* index);//取得した温湿度を基に、アラートの分類分けを行う
    int temperature = mwbgt.getTemperature(); //温度の取得
    int humidity = mwbgt.getHumidity();  //湿度の取得
    int index = mwbgt.getWBGTIndex();  //WBGT指数の取得
int calc_index;
