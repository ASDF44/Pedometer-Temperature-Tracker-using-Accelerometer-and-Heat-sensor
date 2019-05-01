#include <PlotPlus.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
float celval;
int x;
int val;
const int xpin=0;
int ypin=1;
int zpin=2;
int steps,flag=0;
int kswitch = 0;
int tempPin = 3;
int powerpin=A0;
int gnd=A1;
float celx[3];
float threshhold
 }
 delay(100);
 xavg=sum/100.0;
 yavg=sum1/100.0;
 zavg=sum2/100.0;
 //Serial.println(xavg);Serial.println(" ");Serial.println(yavg);Serial.println(" ");Serial.println(zavg);
}
void setup() {
 lcd.init(); //initialize the lcd
 lcd.backlight(); //open the backlight
 lcd.setCursor(15,0);
 Serial.begin(9600);
 calibrate();
 calib();
//Serial.println("##########################################################################################"
);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Steps: ");
 lcd.print(0);
 k=-1;
 kswitch=1;
}
void loop() {
 float xv,yv,zv;
 xv=float(analogRead(xpin));
 yv=float(analogRead(ypin));
 zv=float(analogRead(zpin));
 val = analogRead(tempPin);
 float mv = ( val/1024.0)*5000;
 float cel = mv/10;
 float farh = (cel*9)/5 + 32;
 k++;
 if(k%1000==0){
 kswitch=(kswitch+1)%2;
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Steps: ");
 lcd.print(steps);
 lcd.print(" KCal:");
 int displaycal=0.35*steps;
 lcd.print(displaycal);
 celx[0] = celx[1];
 celx[1] = celx[2];
 celx[2] = cel;
 Serial.println(String(celx[0])+" "+String(celx[1])+" "+String(celx[2])+" ");
 celval = (celx[0]+celx[1]+celx[2]);
 if((celval>90)&&(celval<107)){
 lcd.setCursor(0,1);
 lcd.print("Temp:");
 int jx = (celval/3)*1.1;
 lcd.print(String(cel)+" *C");
 }
 }
 //Serial.println("X:"+String(xv-xavg)+" Y:"+String(yv-yavg)+" Z:"+String(zv-zavg));
 //if(k>100)
 //Serial.println(xv-xavg,yv-yavg);
 //Serial.print(k);
 if(((xv-xavg)>10)||(k%10==0)){
 x=xv-xavg;
 if(x>threshhold){
 //Serial.print("X: ");
 //Serial.println(x);
 //Serial.print(" ");
 if(count>8){
 steps+=1;
 //Serial.print("Count: ");
 //Serial.println(count);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Steps: ");
 lcd.print(steps);
 lcd.print(" KCal:");
 int displaycal=0.35*steps;
 lcd.print(displaycal);
 celx[0] = celx[1];
 celx[1] = celx[2];
 celx[2] = cel;
 Serial.println(String(celx[0])+" "+String(celx[1])+" "+String(celx[2])+" ");
 celval = (celx[0]+celx[1]+celx[2]);
 if((celval>90)&&(celval<107)){
 lcd.setCursor(0,1);
 lcd.print("Temp:");
 int jx = (celval/3)*1.1;
 lcd.print(String(cel)+" *C");
 }
 delay(500);
 }
 count=0;
 }
 }
 count++;
 //Serial.print("step: ");
 //Serial.print(steps);
 //if(((xv-xavg)>30)||(k%10==0))
 //Serial.print("Y: "); Serial.print(xv-xavg); Serial.print(" ");
 //Serial.print("Y: "); Serial.print(yv-yavg); Serial.print(" ");
 //Serial.print("Z: "); Serial.print(zv-zavg); Serial.print(" ");
 //Serial.println("uT");
}
void calib() {
 int i,j,per=0,lper=-1;
 float xv,aa;
 //Serial.println(" Calibrating");
 while(!(a[0]>25)){
 if(lper!=per){
 lcd.clear();
 lcd.setCursor(2,0);
 lcd.print("Calibrating");
 lcd.setCursor(2,1);
 aa=((float)per/15)*100;
 lcd.print(aa);
 lcd.print(" % done");
 lper=per;
 }
 xv=float(analogRead(xpin));
 x=xv-xavg;
 if(x>a[0] && x>25){
 a[0]=x;
 per++;
 sort();
/* Serial.println("x");
 Serial.println(x);
 Serial.println("a[0]");
 Serial.println(a[0]);
 Serial.println("a[1]");
 Serial.println(a[1]);
 Serial.println("a[2]");
 Serial.println(a[2]);
 Serial.println("a[3]");
 Serial.println(a[3]);
 Serial.println("a[4]");
 Serial.println(a[4]);
 Serial.println("a[5]");
 Serial.println(a[5]);
*/ delay(300);
 }
 }
 threshhold = (a[14]+a[9])/2;
 if(lper!=per){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Calibrating ...");
 lcd.setCursor(0,1);
 lcd.print(" Completed");
 lper=per;
 delay(2000);
 }
}
void sort(){
 int temp,i,j;
 for(i=0;i<14;i++){
 for(j=1;j<15-i;j++){
 if(a[j-1]>a[j]){
 temp=a[j-1];
 a[j-1]=a[j];
 a[j]=temp;
 }
 }
 }
}