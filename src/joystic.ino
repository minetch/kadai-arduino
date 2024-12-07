#define centerX 512
#define centerY 512

#define threshold 100

// ジョイスティックのピン定義
const int VRx = A1;  // X軸
const int VRy = A0;  // Y軸
const int SW = 7;    // ボタン

void setup() {
  pinMode(SW, INPUT_PULLUP); // ボタンをプルアップモードで設定
  Serial.begin(9600);        // シリアル通信を開始
}

void loop() {
  int xValue = analogRead(VRx); // X軸の値を取得
  int yValue = analogRead(VRy); // Y軸の値を取得
  int buttonState = digitalRead(SW); // ボタンの状態を取得（押下でLOW）

  if (abs(xValue - centerX) < threshold && abs(yValue - centerY) < threshold) {
    Serial.println("Center");
  }
  else {
    // X軸（左右）方向をチェック
    if (abs(xValue - centerX) > abs(yValue - centerY)) {  // X軸が強い場合
      if (xValue < centerX - threshold) {
        Serial.println("Right");  // 左に動くと "Right"（位置が逆転）
      } else if (xValue > centerX + threshold) {
        Serial.println("Left");   // 右に動くと "Left"
      }
    }
    // Y軸（上下）方向をチェック
    else {  // Y軸が強い場合
      if (yValue < centerY - threshold) {
        Serial.println("Down");  // 上に動くと "Down"（位置が逆転）
      } else if (yValue > centerY + threshold) {
        Serial.println("Up");    // 下に動くと "Up"
      }
    }
  }

  // シリアルモニタに出力
  /*
  Serial.print(xValue);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print("\t");
  */
  Serial.println(buttonState == LOW ? "Pressed" : "Released");

  delay(100); // 100ms待機
}