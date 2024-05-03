/**
   @file DriveServo.ino
   @brief Arduinoの周期設定等
   @author Kenta Hiyoshi
   @date 2023/12/14
*/

#include "SysCtrl.h"

SysCtrl sysCtrl;

void setup() 
{   // put your setup code here, to run once:
    Serial.begin(BAUDRATE);
    sysCtrl = SysCtrl();
    delay(1000);
    //Serial.begin(9600);
}


void loop()
{
    // 初期化処理
    static bool isInitialized = false;
    if (!isInitialized)
    {
        sysCtrl.initialize();
        delay(50);
        isInitialized = true;
    }
    
    if (timeCnt(LOOP_TIME))
    {
        loopMain();
        //Serial.println("hello, paulina, I'm conori I, nice to meet you!");
    }
}


/*
  指定した時間が経過したら1を返す(単位はms)
**/
unsigned int timeCnt(unsigned int cntTime)
{
    static unsigned long preTime = millis();
    unsigned int ret = 0;
    unsigned long currentTime = millis();
    unsigned long delta = currentTime - preTime;
    if (delta >= cntTime)
    {
        ret = 1;
        preTime = currentTime;
    }
    return ret;
}


/*
  メインループ
**/
void loopMain()
{
    sysCtrl.run();
}
