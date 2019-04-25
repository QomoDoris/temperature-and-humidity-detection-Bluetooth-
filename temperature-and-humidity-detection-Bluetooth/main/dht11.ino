
int HumidityandTemperature(){
    // 两次检测之间，要等几秒钟，这个传感器有点慢。
  delay(2000);
  // 读温度或湿度要用250毫秒
  float h = dht.readHumidity();//读湿度
  float t = dht.readTemperature();//读温度，默认为摄氏度
//  Serial.print("Humidity: ");//湿度
//  Serial.println(h);
//  Serial.print("Temperature: ");//温度
//  Serial.print(t);
//  Serial.println(" ℃ ");
  hum = h;
  temp = t;
}
