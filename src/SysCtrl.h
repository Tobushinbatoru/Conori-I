/**
 * @file SysCtrl.h
 * @brief システムのメイン
 * @author Kenta Hiyoshi
 * @date 2023/12/14
 */

#ifndef SysCtrl_h
#define SysCtrl_h

// #include "lib/IcsHardSerialClass.h"
#include <Arduino.h>
#include <IcsHardSerialClass.h>

#define EN_PIN 2
#define BAUDRATE 115200
#define TIMEOUT 1000		/* [ms] 通信できてないか確認用にわざと遅めに設定 */
#define LOOP_TIME 10    /* [ms] */
#define PIN_1 11
#define PIN_2 7

#define SERVO_ANGLE_MAX 20    /* [deg] ※モーター取り付け位置につき反転しているので注意*/  /*20*/
#define SERVO_ANGLE_MIN -60   /* [deg] ※モーター取り付け位置につき反転しているので注意*/  /*-60*/
#define SERVO_ANGLE_ZERO 0

/*
  サーボ情報
*/
typedef struct
{
    int servoAngle = 0;
    int servoSpd = 0;
    int servoStrc = 0;
}ServoStatus;


/*
  システム全体の状態
*/
typedef struct
{
    bool isPushingBtn1 = false;
    bool isPushingBtn2 = false;
    bool situation_1 = false;
    bool situation_2 = false;
    bool situation_3 = false;
    bool situation_4 = false;
    bool situation_5 = false;
    bool situation_6 = false;
    bool situation_7 = false;
    bool situation_8 = false;
    bool situation_9 = false;
    bool situation_0 = false;
    ServoStatus servoStatus;
}SystemStatus; 


class SysCtrl
{
public:
    SysCtrl(void);
    void run(void);
    void initialize(void);

private:
    SystemStatus getSystemStatus();
    ServoStatus getCmdStatus(SystemStatus *systemStatus);
    void runServo(ServoStatus *cmdStatus);
    //void demand(int angle, int speed, int strc);
    
};


#endif
