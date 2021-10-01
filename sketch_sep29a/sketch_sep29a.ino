#include <MsTimer2.h>
#include <Wire.h>

// 変数の設定
int adt7410I2CAddress = 0x48;     //温度センサのアドレス
int SensorOutPin = 0; // パルスセンサー出力をアナログピンの0番指定
int LED = 13;         // Lチカ用のデジタルピンを13番指定
int Signal;           // analogReadで読み取る値の格納変数
int Threshold = 550;  // 心拍のスレッショルド指定（LED点灯判定用）
int timercnt;         // タイマーの判定用変数
int i=0;
float buf;

void timerHandler() {
  //タイマ満了時呼び出される
  timercnt++;
}

void setup() {
  pinMode(LED,OUTPUT); // 13番ピンを出力指定
  Serial.begin(9600);  // シリアルポートを9600bpsで指定
  Wire.begin();                  //I2C通信開始
}

void loop() {
  // ローカル変数設定
  int cnt = 0;
  int state = 0;

  MsTimer2::set(10000, timerHandler);
  timercnt = 0;
  MsTimer2::start();
  
  while(timercnt == 0){ 
    Signal = analogRead(SensorOutPin); // パルスセンサの値を読み込み
    //Serial.println(Signal);          // AD変換した値を表示
    i++;
    if(i==1000){
      uint16_t uiVal; //2バイト(16ビット)の領域
      float fVal;
      int iVal;
 
      Wire.requestFrom(adt7410I2CAddress, 2);   //2バイト要求
 
      uiVal = (uint8_t)Wire.read() << 8;   // 1バイト読み出しで上位にシフト
      uiVal |= Wire.read();                 // 1バイト読み出して下位にセット
 
      uiVal >>= 3;                          // シフトで13bit化
 
      if (uiVal & 0x1000) {                // 13ビットで符号判定
        iVal = uiVal - 0x2000;             // マイナスの時 (10進数で8192)
      }
      else {
        iVal = uiVal;                      //プラスの時
      }
      fVal = (double)iVal / 16.0;           // 温度換算(摂氏)
      Serial.print(fVal);
      Serial.print(",");
      Serial.print(buf);
      Serial.println(",");
      i=0;    
    }
    //LEDのON,OFF及び脈拍・心拍のカウント
    if(Signal > Threshold){
      if(state == 0){
        cnt++;                 //閾値を超えて状態0ならカウントアップ
        //Serial.println(cnt);   //20秒間のカウント値を表示
      }
        state = 1;             //状態を1にする
      } else {
        state = 0;             // 状態を0にする
      }
    delay(1);              // 10ms遅延設定
  }


   buf = float(cnt)/10*60; // 20秒のカウント値を60秒換算
}
