void begined()
{
  pinMode(HX711_SCK, OUTPUT); 
  pinMode(HX711_DT, INPUT);
  Get_Maopi();
}
int reading(){
  Weight = Get_Weight();    //采样当前传感器重量，该重量已经自动去皮，去皮值根据初始化程序中采样的值计算
  return Weight;
}
int Pressed(int AlarmValue)
{
  if(Get_Weight() >= AlarmValue && CurrentAlarm == 0)
  {
    CurrentAlarm = 1;
    return 1;
  }
  else if(Get_Weight() < AlarmValue)
  {
    CurrentAlarm = 0;
    return 0;
  }
  return 0;
}

//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi()
{
  Weight_Maopi = HX711_Read();    
} 

//****************************************************
//称重
//****************************************************
long Get_Weight()
{
  HX711_Buffer = HX711_Read();

  Weight_Shiwu = HX711_Buffer;
  Weight_Shiwu = Weight_Shiwu - Weight_Maopi;       //获取实物的AD采样数值。
  
  Weight_Shiwu = (long)((float)Weight_Shiwu/ValueGap+0.05);   

  return Weight_Shiwu;
}

//****************************************************
//读取HX711
//****************************************************
unsigned long HX711_Read() //增益128
{
  unsigned long count; 
  unsigned char i;
  bool Flag = 0;

  digitalWrite(HX711_DT, HIGH);
  delayMicroseconds(1);

  digitalWrite(HX711_SCK, LOW);
  delayMicroseconds(1);

    count=0; 
    while(digitalRead(HX711_DT)); 
    for(i=0;i<24;i++)
  { 
      digitalWrite(HX711_SCK, HIGH); 
    delayMicroseconds(1);
      count=count<<1; 
    digitalWrite(HX711_SCK, LOW); 
    delayMicroseconds(1);
      if(digitalRead(HX711_DT))
      count++; 
  } 
  digitalWrite(HX711_SCK, HIGH); 
  delayMicroseconds(1);
  digitalWrite(HX711_SCK, LOW); 
  delayMicroseconds(1);
  count ^= 0x800000;
  return(count);
}
