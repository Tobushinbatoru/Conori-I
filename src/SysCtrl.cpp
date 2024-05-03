/**
 * @file SysCtrl.cpp
 * @brief システムのメイン
 * @author Kenta Hiyoshi
 * @date 2023/12/14
 */

#include "SysCtrl.h"

IcsHardSerialClass krs;
/**
 * @brief Construct a new Sys Ctrl:: Sys Ctrl object
 * 
 */
SysCtrl::SysCtrl(void)
{   // コンストラクタ
    pinMode(PIN_1, INPUT_PULLUP);
    pinMode(PIN_2, INPUT_PULLUP);
}


void SysCtrl::initialize(void)
{
    /* krsモーターの初期設定 */
    krs.begin(&Serial1, EN_PIN, BAUDRATE, TIMEOUT);
    krs.setSpd(0, 10);
    krs.setStrc(0, 60);
}


/**
 * @brief SysCtrlの内容を実行する
 * 
 */
void SysCtrl::run(void)
{  
    int rotateState = 0;
    /* 状態の取得（ボタン、軸角度、速度、ストレッチ） */
   SystemStatus systemStatus = this->getSystemStatus();
    /* 指令値セット（目標角度、速度、ストレッチ）を生成 */
   ServoStatus cmdStatus = this->getCmdStatus(&systemStatus);     
      /* 指令セットの送信 */
   this->runServo(&cmdStatus);
}

/**
 * @brief 現在のシステム状態を取得
 * 
 * @return SystemStatus 
 */
SystemStatus SysCtrl::getSystemStatus()
{
    SystemStatus systemStatus;
    /* sw1がONの時 */
    if(!digitalRead(PIN_1)){systemStatus.isPushingBtn1 = true;}
    /* sw2がONの時 */
    if(!digitalRead(PIN_2)){systemStatus.isPushingBtn2 = true;}
    /* サーボ情報取得 */
    systemStatus.servoStatus.servoAngle = krs.getPos(0);
    systemStatus.servoStatus.servoSpd = krs.getSpd(0);
    systemStatus.servoStatus.servoStrc = krs.getStrc(0);
    return systemStatus;
}

/**
 * @brief 二つのボタン指示（IO指示）からモーターの駆動に必要なパラメータを決定する
 * 
 * @param systemStatus 
 * @return ServoStatus 
 */
ServoStatus SysCtrl::getCmdStatus(SystemStatus *systemStatus)
{
    static int preServoAng = systemStatus->servoStatus.servoAngle;
    static unsigned long millis_buf = 0;
    //unsigned long currentTime = millis();
    //unsigned long elapsedTime1 = currentTime - prevTime1;
    //unsigned long elapsedTime2 = currentTime - prevTime2;
    static long randomSeed = 0;
    //unsigned long time = 0;
    //Serial.print(time);
    //Serial.print("\t");
    //Serial.print(millis());
    //Serial.print(" ");
    Serial.print(preServoAng);
    Serial.print("\t");
    Serial.println(krs.posDeg(systemStatus->servoStatus.servoAngle));
    ServoStatus servoStatus;
    static int state = 0;
    static int l = 0;
    static int l2 = 0;
    static int l3 = 0;
    static int l4 = 0;
    static int l5 = 0;
    static int l6 = 0;
    
    static int k = 0;
    static int k2 = 0;
    static int k3 = 0;
    static int k4 = 0;
    static int k5 = 0;
    static int k6 = 0;
    
    static int count1 = 0;
    static float i = 0;
    static int angle = 0;
   
    if(systemStatus != nullptr)
    {
        //preServoAng = systemStatus->servoStatus.servoAngle;      
        if (Serial.available() > 0) {
        	char input = Serial.read();
		    if(input == '0') {
        		state = 0;
        	}
        	if(input == '1') {
        		millis_buf = millis();
        		i = 0;
        		state = 1;
        		l = 0;
        	}
        	if(input == '2') {
        		millis_buf = millis();
        		i = 0;
        		state = 2;
        		l = 0;
        	}
        	if(input == '3') {
        		millis_buf = millis();
        		i = 0;
        		l = 0;
        		state = 3;
        	}
        	if(input == '4') {
        		millis_buf = millis();
        		i = 0;
        		l = 0;
        		state = 4;
        	}
        	if(input == '5') {
        		millis_buf = millis();
        		i = 0;
        		l = 0;
        		state = 5;
        	}
        	if(input == '6') {
        		millis_buf = millis();
        		i = 0;
        		l = 0;
        		state = 6;
        	}
        	if(input == '7') {
        		state = 7;
        	}
        	if(input == '8') {
        		state = 8;
        	}
        	if(input == '9') {
        		state = 9;
        	}
        	if(input == 'a') {
        		state = 11;
        	}
        	if(input == 'b') {
        		state = 22;
        	}
        	if(input == 's') {
        		state = 999;
        		angle = systemStatus->servoStatus.servoAngle;
        	}
        }
        
        if(state == 0){
        	servoStatus.servoAngle = krs.degPos(0); 	
     		servoStatus.servoSpd = 30;
        	servoStatus.servoStrc = 120;
        	l = 0;
        	//Serial.println(krs.posDeg(systemStatus->servoStatus.servoAngle));
        }
        if(state == 1){
        	
            randomSeed = 1;
            // b
            if(l == 0){
            	delay(1000);
            	Serial.println(l);
            	l = 1;
            	
            }
            // c
            if(l == 1){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(i);
            	
            	if(i <= -25.0){
            		l = 2;
            	}
            }
            // d(random sleep 2.5s ~ 6s)
            if(l == 2){
            	int random1 = random(25,61)*100;
    	    	delay(random1);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random1);
            	
    	    	l = 3;
            }
            // d(random angle -20deg ~ -28deg)
            if(l == 3){
            	i += 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random2 = -1 * random(20,29);
        		
        		Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random2);
            	
            	if(i >= random2){
    	    		l = 4;
            	}
            }
            // d(random sleep 0.1s ~ 1s)
            if(l == 4){
            	int random3 = random(1,11)*100;
    	    	delay(random3);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random3);
            	
    	    	l = 5;
            }
            // d(random angle -30deg ~ -40geg)
            if(l == 5){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random4 = -1 * random(30,40);
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random4);
            	
            	if(i <= random4){
    	    		l = 2;
            	}
            }
            // there is interrpt when video finish(15s)
            ////////////////////////////////////////
            if((millis() - millis_buf) >= 17000){
            	//l = 6;
            	state = 10;
            	k = 0;
            }
            ////////////////////////////////////////
        }
        
       if(state == 2){
        	
            randomSeed = 2;
            // b
            if(l == 0){
            	delay(1000);
            	Serial.println(l);
            	l = 1;
            	
            }
            // c
            if(l == 1){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(i);
            	
            	if(i <= -25.0){
            		l = 2;
            	}
            }
            // d(random sleep 2.5s ~ 6s)
            if(l == 2){
            	int random1 = random(25,61)*100;
    	    	delay(random1);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random1);
            	
    	    	l = 3;
            }
            // d(random angle -20deg ~ -28deg)
            if(l == 3){
            	i += 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random2 = -1 * random(20,29);
        		
        		Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random2);
            	
            	if(i >= random2){
    	    		l = 4;
            	}
            }
            // d(random sleep 0.1s ~ 1s)
            if(l == 4){
            	int random3 = random(1,11)*100;
    	    	delay(random3);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random3);
            	
    	    	l = 5;
            }
            // d(random angle -30deg ~ -40geg)
            if(l == 5){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random4 = -1 * random(30,40);
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random4);
            	
            	if(i <= random4){
    	    		l = 2;
            	}
            }
            // there is interrpt when video finish(15s)
            ////////////////////////////////////////
            if((millis() - millis_buf) >= 10000){
            	//l = 6;
            	state = 10;
            	k = 0;
            }
            ////////////////////////////////////////
        }
        if(state == 3){
        	
            randomSeed = 1;
            // b
            if(l == 0){
            	delay(1000);
            	Serial.println(l);
            	l = 1;
            	
            }
            // c
            if(l == 1){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(i);
            	
            	if(i <= -25.0){
            		l = 2;
            	}
            }
            // d(random sleep 2.5s ~ 6s)
            if(l == 2){
            	int random1 = random(25,61)*100;
    	    	delay(random1);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random1);
            	
    	    	l = 3;
            }
            // d(random angle -20deg ~ -28deg)
            if(l == 3){
            	i += 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random2 = -1 * random(20,29);
        		
        		Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random2);
            	
            	if(i >= random2){
    	    		l = 4;
            	}
            }
            // d(random sleep 0.1s ~ 1s)
            if(l == 4){
            	int random3 = random(1,11)*100;
    	    	delay(random3);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random3);
            	
    	    	l = 5;
            }
            // d(random angle -30deg ~ -40geg)
            if(l == 5){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random4 = -1 * random(30,40);
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random4);
            	
            	if(i <= random4){
    	    		l = 2;
            	}
            }
            // there is interrpt when video finish(15s)
            ////////////////////////////////////////
            if((millis() - millis_buf) >= 14000){
            	//l = 6;
            	state = 10;
            	k = 0;
            }
            ////////////////////////////////////////
        }
        if(state == 4){
        	
            randomSeed = 1;
            // b
            if(l == 0){
            	delay(1000);
            	Serial.println(l);
            	l = 1;
            	
            }
            // c
            if(l == 1){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(i);
            	
            	if(i <= -25.0){
            		l = 2;
            	}
            }
            // d(random sleep 2.5s ~ 6s)
            if(l == 2){
            	int random1 = random(25,61)*100;
    	    	delay(random1);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random1);
            	
    	    	l = 3;
            }
            // d(random angle -20deg ~ -28deg)
            if(l == 3){
            	i += 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random2 = -1 * random(20,29);
        		
        		Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random2);
            	
            	if(i >= random2){
    	    		l = 4;
            	}
            }
            // d(random sleep 0.1s ~ 1s)
            if(l == 4){
            	int random3 = random(1,11)*100;
    	    	delay(random3);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random3);
            	
    	    	l = 5;
            }
            // d(random angle -30deg ~ -40geg)
            if(l == 5){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random4 = -1 * random(30,40);
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random4);
            	
            	if(i <= random4){
    	    		l = 2;
            	}
            }
            // there is interrpt when video finish(15s)
            ////////////////////////////////////////
            if((millis() - millis_buf) >= 4000){
            	//l = 6;
            	state = 10;
            	k = 0;
            }
            ////////////////////////////////////////
        }
        if(state == 5){
        	
            randomSeed = 1;
            // b
            if(l == 0){
            	delay(1000);
            	Serial.println(l);
            	l = 1;
            	
            }
            // c
            if(l == 1){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(i);
            	
            	if(i <= -25.0){
            		l = 2;
            	}
            }
            // d(random sleep 2.5s ~ 6s)
            if(l == 2){
            	int random1 = random(25,61)*100;
    	    	delay(random1);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random1);
            	
    	    	l = 3;
            }
            // d(random angle -20deg ~ -28deg)
            if(l == 3){
            	i += 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random2 = -1 * random(20,29);
        		
        		Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random2);
            	
            	if(i >= random2){
    	    		l = 4;
            	}
            }
            // d(random sleep 0.1s ~ 1s)
            if(l == 4){
            	int random3 = random(1,11)*100;
    	    	delay(random3);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random3);
            	
    	    	l = 5;
            }
            // d(random angle -30deg ~ -40geg)
            if(l == 5){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random4 = -1 * random(30,40);
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random4);
            	
            	if(i <= random4){
    	    		l = 2;
            	}
            }
            // there is interrpt when video finish(15s)
            ////////////////////////////////////////
            if((millis() - millis_buf) >= 13000){
            	//l = 6;
            	state = 10;
            	k = 0;
            }
            ////////////////////////////////////////
        }
        if(state == 6){
        	
            randomSeed = 1;
            // b
            if(l == 0){
            	delay(1000);
            	Serial.println(l);
            	l = 1;
            	
            }
            // c
            if(l == 1){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(i);
            	
            	if(i <= -25.0){
            		l = 2;
            	}
            }
            // d(random sleep 2.5s ~ 6s)
            if(l == 2){
            	int random1 = random(25,61)*100;
    	    	delay(random1);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random1);
            	
    	    	l = 3;
            }
            // d(random angle -20deg ~ -28deg)
            if(l == 3){
            	i += 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random2 = -1 * random(20,29);
        		
        		Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random2);
            	
            	if(i >= random2){
    	    		l = 4;
            	}
            }
            // d(random sleep 0.1s ~ 1s)
            if(l == 4){
            	int random3 = random(1,11)*100;
    	    	delay(random3);
    	    	
    	    	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random3);
            	
    	    	l = 5;
            }
            // d(random angle -30deg ~ -40geg)
            if(l == 5){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random4 = -1 * random(30,40);
            	
            	Serial.print(l);
            	Serial.print(" ");
            	Serial.println(random4);
            	
            	if(i <= random4){
    	    		l = 2;
            	}
            }
            // there is interrpt when video finish(15s)
            ////////////////////////////////////////
            if((millis() - millis_buf) >= 15000){
            	//l = 6;
            	state = 10;
            	k = 0;
            }
            ////////////////////////////////////////
        }
        if(state == 10){
        	//Serial.print("state is 10");
        	//Serial.print("\t");
        	//Serial.print(k);
        	/////////////////////////////////////////////////////////////////////////////////////
            // e(turn to -20deg)
            if(k == 0){
            	i -= 0.1;
            	// slove
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 120;
        			
        		Serial.print(k);
            	Serial.print("\t\t\t");
            	Serial.println(i);
            	
            	if(i <= -20){
    	    		k = 1;
            	}
            }
            // f(sleep 3s ~ 4s)
            if(k == 1){
            	int random5 = random(30,41)*100;
    	    	delay(random5);
            	Serial.print(k);
            	Serial.print(" ");
            	Serial.println(random5);
            	
            	k = 2;            
            }
            // g(turn to -35deg)
          	if(k == 2){
          		i -= 1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        			
        		Serial.print(k);
            	Serial.print(" ");
            	Serial.println(i);
        			
        		if(i <= -35){
    	    		k = 3;
            	}
          	}
          	// h(random sleep 2s ~ 5s)
            if(k == 3){
            	int random6 = random(20,51)*100;
    	    	delay(random6);
    	    	
    	    	Serial.print(k);
            	Serial.print(" ");
            	Serial.println(random6);
            	
    	    	k = 4;
            }
            // h(random angle -20deg ~ -28deg)
            if(k == 4){
            	i += 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random7 = -1 * random(20,29);
        		
        		Serial.print(k);
            	Serial.print(" ");
            	Serial.println(random7);
            	
            	if(i >= random7){
    	    		k = 5;
            	}
            }
            // h(random sleep 0.1s ~ 1s)
            if(k == 5){
            	int random8 = random(1,11)*100;
    	    	delay(random8);

    	    	Serial.print(k);
            	Serial.print(" ");
            	Serial.println(random8);
            	
    	    	k = 6;
            }
            // h(random angle -35deg ~ -45geg)
            if(k == 6){
            	i -= 0.1;
            	
            	servoStatus.servoAngle = krs.degPos(i); 	
     			servoStatus.servoSpd = 30;
        		servoStatus.servoStrc = 60;
        		
        		int random9 = -1 * random(35,46);
            	
            	Serial.print(k);
            	Serial.print(" ");
            	Serial.println(random9);
            	
            	if(i <= random9){
    	    		k = 3;
            	}
            }
        }
        
        if(state == 999) {
        	
        	servoStatus.servoAngle = angle; 	
     		servoStatus.servoSpd = 30;
       		servoStatus.servoStrc = 60;
       		
       		angle += 5;
       		
       		Serial.print(state);
       		Serial.print("\t");
       		Serial.println(angle);
       		
       		if(angle >= krs.degPos(20)){
       			angle = krs.degPos(20);
       		}
        }
    }
    // その他の処理
    return servoStatus;
}

/**
 * @brief krsモーターを駆動させる
 * 
 * @param cmdStatus 
 */
void SysCtrl::runServo(ServoStatus *cmdStatus)
{
    if(cmdStatus != nullptr)
    {
        krs.setPos(0, cmdStatus->servoAngle);
        krs.setSpd(0, cmdStatus->servoSpd);
        krs.setStrc(0, cmdStatus->servoStrc);
    }
}
   
        /*
int IcsBaseClass::degPos(float deg)
{
  if (deg > MAX_DEG) {
    return -1;
  }
  if (deg < MIN_DEG) {
    return -1;
  }
  int pos = deg * 29.633;
  pos = pos + 7500;
  return pos;
}               
        */
