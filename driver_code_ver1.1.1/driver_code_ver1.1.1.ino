#define MotorX1 11//극성 주의
#define MotorX2 10
#define MotorY1 9//극성 주의 
#define MotorY2 8
#define MotorEnable 12
#define MotorSpeed 100 //1~255
#define reversTork 25 //ms 역토크 
#define inputX1 30//sensor input
#define inputX2 31
#define inputY1 32
#define inputY2 33
#define muxA 2//y축 센서 mux입력
#define muxB 3
#define muxC 4
#define muxA2 5//x축 센서 mux입력 
#define muxB2 6
#define muxC2 7
#define solenoid1 40
#define solenoid2 41
#define ySwitch 44//y axis switch
#define ySwitch2 45
#define xSwitch 46
#define xSwitch2 47
#define sol_power 180//solenoid power

//스위치 풀다운 저항 필요가능성 있음

void setup() {
  pinMode(MotorX1, OUTPUT);  
  pinMode(MotorX2, OUTPUT);  
  pinMode(MotorY1, OUTPUT);  
  pinMode(MotorY2, OUTPUT);  
  pinMode(MotorEnable, OUTPUT);  
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(inputX1, INPUT);
  pinMode(inputX2, INPUT);
  pinMode(inputY1, INPUT);
  pinMode(inputY2, INPUT);
  pinMode(muxA, OUTPUT);  
  pinMode(muxB, OUTPUT);  
  pinMode(muxC, OUTPUT);
  pinMode(muxA2, OUTPUT);  
  pinMode(muxB2, OUTPUT);  
  pinMode(muxC2, OUTPUT);  
  pinMode(solenoid1, OUTPUT);
  pinMode(solenoid2, OUTPUT);
  pinMode(ySwitch2, OUTPUT);
  digitalWrite(ySwitch, HIGH);
  pinMode(ySwitch, INPUT);
  pinMode(xSwitch2, OUTPUT);
  digitalWrite(xSwitch, HIGH);
  pinMode(xSwitch, INPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

}
void loop(){
  int i=0;
  int j=0;
  char coor[5]={0,0,0,0,0};
      int incomingByte = 0;
      /*
      int board[8][8]={{1,2,1,1,1,1,2,1},//[x][y]
                       {1,1,1,1,1,1,1,1},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {1,1,1,1,1,1,1,1},
                       {1,2,1,1,1,1,2,1 }};//2 for night//can be disable
      */
      char Xf,Xl,Yf,Yl;
// for test. put only 1x and 1y.
//Solenoid_io(1);
      for(i=0;i<5;)
      {
        if (Serial2.available() > 0) {
            incomingByte = Serial2.read();
            coor[i]=incomingByte;
            i++;//if not work, change to while
            if(coor[0]!='S')
            i=0;
        }
       /* if(i=4)
        {
            if(coor[1]<'a' || coor[1]>'h')
            i=0;
            if(coor[2]<'1' || coor[2]>'8')
            i=0;
            if(coor[3]<'a' || coor[3]>'h')
            i=0;
            if(coor[4]<'1' || coor[4]>'8')
            i=0;
            Serial.write(coor[1]);
    Serial.write(coor[2]);
    Serial.write(coor[3]);
    Serial.write(coor[4]);
    Serial.print('\n');
    Serial.print("-------");
        }*/
      }

    Xf = (coor[1]-'a'+1)*2;//2,4,6,8,10,12,14,16
    Yf = (coor[2]-'1'+1)*2;
    Xl = (coor[3]-'a'+1)*2;
    Yl = (coor[4]-'1'+1)*2;
    Serial.write(coor[1]);
    Serial.write(coor[2]);
    Serial.write(coor[3]);
    Serial.write(coor[4]);
    Serial.print('\n');
    Serial.print("-------");

  Solenoid_io(0);//turn off
  /***************************************/
//배열 내용 이동시키는 것. 
/*
int temp;
temp=board[Xf][Yf];
board[Xf][Yf]=0;
board[Xl][Yl]=temp;
*/

//배열 출력. 
/*
int a,b;
for(a=0;a<8;a++){
  for(b=0;b<8;b++)
  {
  Serial.print(board[a][b]);
  }
  Serial.print('\n');
}
Serial.print("--------");
Serial.print('\n');
*/
//while(1);
/****************************************/
/*
  if(board[(Yl/2-1)][(Xl/2-1)]!=0)//말이 잡히는 경우 //말 버리는 작업만 
  {
    int i=0;
    Solenoid_io(0);//just for sure. can be disable
    motorMoveX(Xl);
    motorMoveY(Yl);//버리는 말 위치로 이동
    Solenoid_io(1);//grab
    i=inputFromY();//y위치 파악 후 반칸 이동 
    if(i=1)
      motorMoveY(2);
    else
      motorMoveY(i-1);//y축 반칸 이동 완료
    motorMoveX(1);//말을 x축 가장 왼쪽으로 보낸다
   // motorMoveY(9);//왼쪽 중간을 버리는 공간으로 하는 경우 사용 
    Solenoid_io(0);//release
  }
  int temp;
temp=board[Yf][Xf];
board[Yf][Xf]=0;
board[Yl][Xl]=temp;
*/
//int a,b;
/*
for(a=0;a<8;a++){
  for(b=0;b<8;b++)
  {
  Serial.print(board[a][b]);
  }
  Serial.print('\n');
}
Serial.print("--------");
Serial.print('\n');
*/
  //////////////////////
  if(Yf==Yl && !(Xf==Xl))//x축만 이동 
  {
    Solenoid_io(0);//just for sure. can be disable
    motorMoveX(Xf);
    motorMoveY(Yf);//초기 위치로 이동 
    Solenoid_io(1);//grab
    motorMoveX(Xl);
    Solenoid_io(0);//release
  }
  else if(Xf==Xl && !(Yf==Yl))//y축만 이동 
  {
    Solenoid_io(0);//just for sure. can be disable
    motorMoveX(Xf);
    motorMoveY(Yf);
    Solenoid_io(1);//grab
    motorMoveY(Yl);
    Solenoid_io(0);release
  }    
  else if(abs(Xl-Xf)==abs(Yl-Yf))//대각선 이동.(abs(Xl-Xf)==abs(Yl-Yf) && Xl!=Xf && Yl!=Yf)
  {
      if((Xl-Xf)>0 && (Yl-Yf)>0)//1st case
      {
        Solenoid_io(0);//just for sure. can be disable
        motorMoveX(Xf);
        motorMoveY(Yf);
        Solenoid_io(1);

        int j=0,k=0;
        int inputX,inputY;
        k=(Xl-Xf);
        digitalWrite(MotorEnable,HIGH);//방향 맞는지 확인 
        analogWrite(MotorX2, MotorSpeed);
        digitalWrite(MotorX1, LOW);
        analogWrite(MotorY2, MotorSpeed);
        digitalWrite(MotorY1, LOW);
        for(j=1;j<=k;)//needs test 
        {
          inputX=inputFromX();
          inputY=inputFromY();
          if(inputX-Xf==j){
            digitalWrite(MotorX2, LOW);
          }
          if(inputY-Yf==j){
            digitalWrite(MotorY2, LOW);
          }
          if((inputX-Xf==j)&&(inputY-Yf==j)){
            analogWrite(MotorX2, MotorSpeed);
            digitalWrite(MotorX1, LOW);
            analogWrite(MotorY2, MotorSpeed);
            digitalWrite(MotorY1, LOW);
            j++;
          }
        }
        digitalWrite(MotorEnable, LOW);
        Solenoid_io(0);//release
      }//1st case end
      else if((Xl-Xf)<0 && (Yl-Yf)>0)//2nd case
      {
        Solenoid_io(0);//just for sure. can be disable
        motorMoveX(Xf);
        motorMoveY(Yf);
        Solenoid_io(1);

        int j=0,k=0;
        int inputX,inputY;
        k=abs(Xl-Xf);
        digitalWrite(MotorEnable,HIGH);//방향 맞는지 확인 
        analogWrite(MotorX1, MotorSpeed);
        digitalWrite(MotorX2, LOW);
        analogWrite(MotorY2, MotorSpeed);
        digitalWrite(MotorY1, LOW);
        for(j=1;j<=k;)//needs test 
        {
          inputX=inputFromX();
          inputY=inputFromY();
          if(Xf-inputX==j){//abs로 처리하였지만 오류의 경우 Xf-inputX
            digitalWrite(MotorX1, LOW);
          }
          if(inputY-Yf==j){
            digitalWrite(MotorY2, LOW);
          }
          if((Xf-inputX==j)&&(inputY-Yf==j)){
            analogWrite(MotorX1, MotorSpeed);
            digitalWrite(MotorX2, LOW);
            analogWrite(MotorY2, MotorSpeed);
            digitalWrite(MotorY1, LOW);
            j++;
          }
        }
        digitalWrite(MotorEnable, LOW);
        Solenoid_io(0);
      }//2nd case end
      else if((Xl-Xf)<0 && (Yl-Yf)<0)//3rd case
      {
        Solenoid_io(0);//just for sure. can be disable
        motorMoveX(Xf);
        motorMoveY(Yf);
        Solenoid_io(1);

        int j=0,k=0;
        int inputX,inputY;
        k=abs(Xl-Xf);
        digitalWrite(MotorEnable,HIGH);//방향 맞는지 확인 
        analogWrite(MotorX1, MotorSpeed);
        digitalWrite(MotorX2, LOW);
        analogWrite(MotorY1, MotorSpeed);
        digitalWrite(MotorY2, LOW);
        for(j=1;j<=k;)//needs test 
        {
          inputX=inputFromX();
          inputY=inputFromY();
          if(Xf-inputX==j){//abs로 처리하였지만 오류의 경우 Xf-inputX
            digitalWrite(MotorX1, LOW);
          }
          if(Yf-inputY==j){
            digitalWrite(MotorY1, LOW);
          }
          if((Xf-inputX==j)&&(Yf-inputY==j)){
            analogWrite(MotorX1, MotorSpeed);
            digitalWrite(MotorX2, LOW);
            analogWrite(MotorY1, MotorSpeed);
            digitalWrite(MotorY2, LOW);
            j++;
          }
        }
        digitalWrite(MotorEnable, LOW);
        Solenoid_io(0);
      }//3rd case end
      else if((Xl-Xf)>0 && (Yl-Yf)<0)//4th case
      {
        Solenoid_io(0);//just for sure. can be disable
        motorMoveX(Xf);
        motorMoveY(Yf);
        Solenoid_io(1);

        int j=0,k=0;
        int inputX,inputY;
        k=abs(Xl-Xf);
        digitalWrite(MotorEnable,HIGH);//방향 맞는지 확인 
        analogWrite(MotorX2, MotorSpeed);
        digitalWrite(MotorX1, LOW);
        analogWrite(MotorY1, MotorSpeed);
        digitalWrite(MotorY2, LOW);
        for(j=1;j<=k;)//needs test 
        {
          inputX=inputFromX();
          inputY=inputFromY();
          if(inputX-Xf==j){
            digitalWrite(MotorX2, LOW);
          }
          if(Yf-inputY==j){
            digitalWrite(MotorY1, LOW);
          }
          if((inputX-Xf==j)&&(Yf-inputY==j)){
            analogWrite(MotorX2, MotorSpeed);
            digitalWrite(MotorX1, LOW);
            analogWrite(MotorY1, MotorSpeed);
            digitalWrite(MotorY2, LOW);
            j++;
          }
        }
        digitalWrite(MotorEnable, LOW);
        Solenoid_io(0);
      }//4th case end//대각선 이동 end
  }
  else if(1)//Night move.. //if(board[Xf][Yf]==2)
  {
    Solenoid_io(0);
    int a,b;
    a=abs(Xl-Xf);
    b=abs(Yl-Yf);
    motorMoveX(Xf);
    motorMoveY(Yf);

    if(a==2 && b==4)//세로방향 이동 
    {
      if(Xl-Xf>0)//오른쪽 이동 
      {
        Solenoid_io(1);
        motorMoveX(Xf+1);
        motorMoveY(Yl);
        motorMoveX(Xl);
        Solenoid_io(0);
      }
      else//왼쪽 이동 
      {
        Solenoid_io(1);
        motorMoveX(Xf-1);
        motorMoveY(Yl);
        motorMoveX(Xl);
        Solenoid_io(0);
      }
    }
    if(a==4 && b==2)//가로방향 이동 
    {
      if(Yl-Yf>0)
      {
        Solenoid_io(1);
        motorMoveY(Yf+1);
        motorMoveX(Xl);
        motorMoveY(Yl);
        Solenoid_io(0);
      }
      else
      {
        Solenoid_io(1);
        motorMoveY(Yf-1);
        motorMoveX(Xl);
        motorMoveY(Yl);
        Solenoid_io(0);
      }
    }
  }//Night move end
  Serial2.print('E');
 /* for(a=0;a<8;a++){
  for(b=0;b<8;b++)
  {
  Serial.print(board[a][b]);
  }
  Serial.print('\n');
}
Serial.print("--------");
Serial.print('\n');*/

}//loop end
   
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/*
solenoid is connected to driver board.
put PWM signal to solenoid1
solenoid2 for enable driver board 
pin 26 for solenoid GND, pin 27 for solenoid power 
*/
void Solenoid_io(int solenoid){
  if(solenoid==0)//turn off the solenoid
  {
    analogWrite(solenoid1, 0);
    digitalWrite(solenoid2, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
  }
  if(solenoid==1)//turn on the solenoid
  {
    analogWrite(solenoid1, sol_power);
    digitalWrite(solenoid2, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(26, HIGH);
   }
   return;
}

int inputFromY(){
  int in_X1 = 0;
  int in_X2 = 0;
  int buf_X1 = 0;//save buffer for input
  int buf_X2 = 0;
  
  //1st state
  digitalWrite(muxA2, HIGH);
  digitalWrite(muxB2, HIGH); 
  digitalWrite(muxC2, HIGH);
  buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
   if(buf_X1==HIGH)
   in_X1 =1;
   if(buf_X2==HIGH)
      in_X2 =9;
         
 //2nd state
  digitalWrite(muxA2, HIGH);
  digitalWrite(muxB2, HIGH); 
  digitalWrite(muxC2, LOW);
  buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
   if(buf_X1==HIGH)
   in_X1 =2;
   if(buf_X2==HIGH)
   in_X2 =10;
  
  //3rd state
  digitalWrite(muxA2, HIGH);
  digitalWrite(muxB2, LOW); 
  digitalWrite(muxC2, HIGH);
  buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
   if(buf_X1==HIGH)
   in_X1 =3;
   if(buf_X2==HIGH)
   in_X2 =11;
  
 //4th state
  digitalWrite(muxA2, HIGH);
  digitalWrite(muxB2, LOW); 
  digitalWrite(muxC2, LOW);
 buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
   if(buf_X1==HIGH)
   in_X1 =4;
   if(buf_X2==HIGH)
   in_X2 =12;
  
  //5th state
  digitalWrite(muxA2, LOW);
  digitalWrite(muxB2, HIGH); 
  digitalWrite(muxC2, HIGH);
  buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
  if(buf_X1==HIGH)
   in_X1 =5;
   if(buf_X2==HIGH)
   in_X2 =13;

  //6th state
  digitalWrite(muxA2, LOW);
  digitalWrite(muxB2, HIGH); 
  digitalWrite(muxC2, LOW);
  buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
   if(buf_X1==HIGH)
     in_X1 =6;
   if(buf_X2==HIGH)
      in_X2 =14;
        
  //7th state
  digitalWrite(muxA2, LOW);
  digitalWrite(muxB2, LOW); 
  digitalWrite(muxC2, HIGH);
  buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
   if(buf_X1==HIGH)
   in_X1 =7;
   if(buf_X2==HIGH)
   in_X2 =15;
  
  //8th state
  digitalWrite(muxA2, LOW);
  digitalWrite(muxB2, LOW); 
  digitalWrite(muxC2, LOW);
  buf_X1=!digitalRead(inputX1);
  buf_X2=!digitalRead(inputX2);
   if(buf_X1==HIGH)
   in_X1 =8;
   if(buf_X2==HIGH)
   in_X2 =16;
  
 int result=0;
  if(in_X2>0)
    result=in_X2;
  else
    result=in_X1;

  //Serial.print('\n');
  //Serial.print("reading x=");
  //Serial.print(result);
  //Serial.print('\n');
  //delay(200);
  return result;
}
int inputFromX(void){
  int in_y1 = 0;
  int in_y2 = 0;
  int buf_y1 = 0;//save buffer for input
  int buf_y2 = 0;

  //1st state
  digitalWrite(muxA, LOW);
  digitalWrite(muxB, LOW); 
  digitalWrite(muxC, LOW);
  buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
   if(buf_y1==HIGH)
   in_y1 =1;
   if(buf_y2==HIGH)
      in_y2 =9;
 
 //2nd state
  digitalWrite(muxA, HIGH);
  digitalWrite(muxB, LOW); 
  digitalWrite(muxC, LOW);
  buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
   if(buf_y1==HIGH)
   in_y1 =2;
   if(buf_y2==HIGH)
   in_y2 =10;
  
  //3rd state
  digitalWrite(muxA, LOW);
  digitalWrite(muxB, HIGH); 
  digitalWrite(muxC, LOW);
  buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
   if(buf_y1==HIGH)
   in_y1 =3;
   if(buf_y2==HIGH)
   in_y2 =11;
  
 //4th state
  digitalWrite(muxA, HIGH);
  digitalWrite(muxB, HIGH); 
  digitalWrite(muxC, LOW);
 buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
   if(buf_y1==HIGH)
   in_y1 =4;
   if(buf_y2==HIGH)
   in_y2 =12;
  
  //5th state
  digitalWrite(muxA, LOW);
  digitalWrite(muxB, LOW); 
  digitalWrite(muxC, HIGH);
  buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
  if(buf_y1==HIGH)
   in_y1 =5;
   if(buf_y2==HIGH)
   in_y2 =13;

  //6th state
  digitalWrite(muxA, HIGH);
  digitalWrite(muxB, LOW); 
  digitalWrite(muxC, HIGH);
  buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
   if(buf_y1==HIGH)
     in_y1 =6;
   if(buf_y2==HIGH)
      in_y2 =14;
        
  //7th state
  digitalWrite(muxA, LOW);
  digitalWrite(muxB, HIGH); 
  digitalWrite(muxC, HIGH);
  buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
   if(buf_y1==HIGH)
   in_y1 =7;
   if(buf_y2==HIGH)
   in_y2 =15;
  
  //8th state
  digitalWrite(muxA, HIGH);
  digitalWrite(muxB, HIGH); 
  digitalWrite(muxC, HIGH);
  buf_y1=!digitalRead(inputY1);
  buf_y2=!digitalRead(inputY2);
   if(buf_y1==HIGH)
   in_y1 =8;
   if(buf_y2==HIGH)
   in_y2 =16;
  
 int result=0;
  if(in_y2>0)
    result=in_y2;
  else
    result=in_y1;

  //Serial.print('\n');
  //Serial.print("reading y=");
  //Serial.print(result);
  //Serial.print('\n');
  //delay(200);
  return result;
}

int motorMoveX(int wantMoveX)//원하는 x좌표 입력
{
  digitalWrite(MotorY1, LOW);
  digitalWrite(MotorY2, LOW);//반대 축 모터가 움직이지 않도록. 

int wise = 0;
int input = 0;
int i;
input=inputFromX();
//
if(input==0)
{
  digitalWrite(MotorEnable,HIGH);//방향 맞는지 확인 
  analogWrite(MotorX1, MotorSpeed);
  digitalWrite(MotorX2, LOW);
  while(input==0)
  {
    input=inputFromX();
    i=digitalRead(xSwitch);
    if(i==HIGH)//
    {
      analogWrite(MotorX2, MotorSpeed);
      digitalWrite(MotorX1, LOW);
      while(input==0)
      {
        input=inputFromX();
      }
      digitalWrite(MotorX2, LOW);
      break;
    }
    

  }
}

if(input>wantMoveX)//ccw//ccw & cw can be reversed
  wise = -1;
else if(input<wantMoveX)//cw
  wise = 1;
else//input==wantMoveX
  return 0;

if(wise==-1){//ccw
  digitalWrite(MotorEnable,HIGH);
  analogWrite(MotorX1, MotorSpeed);
  digitalWrite(MotorX2, LOW);
  while(1)
  {
    input=inputFromX();
    if(input==wantMoveX)
      break;
  }
  analogWrite(MotorX2, MotorSpeed);//역토크 can be disable
  digitalWrite(MotorX1, LOW);//역토크 can be disable
  delay(reversTork);
  digitalWrite(MotorEnable,LOW);
}//if.ccw end
else if(wise==1){//cw
  digitalWrite(MotorEnable,HIGH);
  analogWrite(MotorX2, MotorSpeed);
  digitalWrite(MotorX1, LOW);
  while(1)
  {
    input=inputFromX();
    if(input==wantMoveX)
      break;
  }
  analogWrite(MotorX1, MotorSpeed);//역토크 can be disable
  digitalWrite(MotorX2, LOW);//역토크 can be disable
  delay(reversTork);
  digitalWrite(MotorEnable,LOW);
}
else
  return 0;
}//end of funtion

int motorMoveY(int wantMoveY)//원하는 x좌표 입력
{
  digitalWrite(MotorX1, LOW);
  digitalWrite(MotorX2, LOW);//반대 축 모터가 움직이지 않도록. 

int wise = 0;
int input =0;
int i;
input=inputFromY();
if(input==0)
{
  digitalWrite(MotorEnable,HIGH);//방향 맞는지 확인 
  analogWrite(MotorY1, MotorSpeed);
  digitalWrite(MotorY2, LOW);
  while(input==0)
  {
    input=inputFromY();
    i=digitalRead(ySwitch);
    if(i==HIGH)//
    {
      analogWrite(MotorY2, MotorSpeed);
      digitalWrite(MotorY1, LOW);
      while(input==0)
      {
        input=inputFromY();
      }
      digitalWrite(MotorY2, LOW);
      break;
    }
    

  }
}
if(input>wantMoveY)//ccw//ccw & cw can be reversed
  wise = -1;
else if(input<wantMoveY)//cw
  wise = 1;
else
  return 0;

if(wise==-1){//ccw
  digitalWrite(MotorEnable,HIGH);
  analogWrite(MotorY1, MotorSpeed);
  digitalWrite(MotorY2, LOW);
  while(1)
  {
    input=inputFromY();
    if(input==wantMoveY)
      break;
  }
  analogWrite(MotorY2, MotorSpeed);//역토크 can be disable
  digitalWrite(MotorY1, LOW);//역토크 can be disable
  delay(reversTork);
  digitalWrite(MotorEnable,LOW);
}//if.ccw end
else if(wise==1){//cw
  digitalWrite(MotorEnable,HIGH);
  analogWrite(MotorY2, MotorSpeed);
  digitalWrite(MotorY1, LOW);
  while(1)
  {
    input=inputFromY();
    if(input==wantMoveY)
      break;
  }
  analogWrite(MotorY1, MotorSpeed);//역토크 can be disable
  digitalWrite(MotorY2, LOW);//역토크 can be disable
  delay(reversTork);
  digitalWrite(MotorEnable,LOW);
}
else
  return 0;
}//end of funtion
