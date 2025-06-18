#include "MdMeasureDistance.h"
#include "DrUltraSonic.h"
#include "M5All-In-One-Gadget.h"
#include <M5Stack.h>

DrUltraSonic ultra(ECHO_PIN, TRIG_PIN);

double MdMeasureDistance::getDistance() {
    double t = ultra.measureReturnTime();  //往復時間（μs）
    double distance = (340.0 / 1000000) * t * 0.5 * 100;
    return distance;
}