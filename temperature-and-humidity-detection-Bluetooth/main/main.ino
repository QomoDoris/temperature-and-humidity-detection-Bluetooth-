#######Hello, welcome to Qomo indoor temperature and humidity control detection project####
#####which is based on Anduino single chip microcomputer.####
####The data communication mode is bluetooth hc-05####
####and the mobile terminal is AndroidAPP####
####The author is Qomo####
####It was written on March 11, 2019####
#
#
#include <DHT.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,9);//自定义Rx :8   Tx:9

#define CONTRAIL 300//延时
#define DHTPIN 4 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int HX711_SCK = 2;
int HX711_DT = 3;  
int atomizeVcc = 5;
int atomizeGnd = 6;
int LED = 13;

volatile int temp,hum,humnew=0;  //温度测量值
volatile int weights;  
long Get_Weight();
void begined();
int Pressed(int AlarmValue);

float ValueGap=750;
long HX711_Buffer;
long Weight_Maopi;
long Weight_Shiwu;
int CurrentAlarm;

void Get_Maopi();
unsigned long HX711_Read();
long Weight = 0;    //定义一个变量用于存放承重的重量，单位为g

volatile int read_data,data='1',flagWeight,flagOperation;
int readnumber=0;
String strs ;
void setup() {
// pin that will blink to your heartbeat!
  Serial.begin(9600);   
  mySerial.begin(9600); 
  // we agree to talk fast!
  while (!Serial||!mySerial) {
    ; //等待串口连接。只需要本地USB端口
  }
  //////////////////////////////
  dht.begin(); //DHT开始工作
    // put your setup code here, to run once:  
  Serial.println("Welcome to use!\n");
  mySerial.println("my name is Qomo");
  pinMode(HX711_SCK, OUTPUT);  
  pinMode(HX711_DT, INPUT);
  pinMode(atomizeVcc, OUTPUT);
  pinMode(LED, OUTPUT);        //设定LED是输出引脚
  digitalWrite(LED, LOW);     //LED熄灭
//  Get_Maopi();
//  begined();          //读取传感器支架毛重
  delay(500);                //延时3s用于传感器稳定
//  begined();          //重新读取传感器支架毛重用于后续计算
  digitalWrite(LED, HIGH);    //板载LED点亮，说明可以承重
}

void loop() {
  HumidityandTemperature();
  weights = reading()-11143;   
    if(weights>CONTRAIL)flagWeight ='0';
    else {
      flagWeight = '1';
      read_data = flagWeight;
    } 
  
  while(mySerial.available()){
      read_data = mySerial.read();
      readnumber++;   
  }  
  if(readnumber==1)data=read_data;
  stopAndoperation(data);
  String myS0("#");
  String myS1(hum);
  String myS2("#");//温度
  String myS3(temp);
  String myS4("#");
  String myS5(weights);
  String myS6("#");
  char myS7(data);
  String myS8('#') ;
  mySerial.println(myS0+myS1+myS2+myS3+myS4+myS5+myS6+myS7+myS8);;
}



