/* インクルードガード */
#pragma once

#include "M5All-In-One-Gadget.h"
#include "DrUltraSonic.h"
#include <M5Stack.h>

class MdMeasureDistance // classの定義
{
private: // privateはクラス内からしかアクセスできない

public: // publicはどこからでもアクセス可能
    double getDistance();//関数定義
};