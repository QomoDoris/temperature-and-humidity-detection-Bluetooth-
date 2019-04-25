
void stopAndoperation(volatile int flag){
    if(flag=='0'&&flagWeight=='0'){
      detal(true);
      readnumber=0;
    }
    else if((flag=='1'&&flagWeight=='0')||flagWeight=='1'){
      detal(false);
      data='1';//加水后不运行
      readnumber=0;//可连续接收数据
    }
}

boolean detal(boolean weights)
{
  if(weights)
  {
    digitalWrite(atomizeVcc, HIGH);    
  }else{
    digitalWrite(atomizeVcc,LOW );   
  }  
  return 0;
}
