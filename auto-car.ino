#include<Servo.h>
#define safedis 25
Servo s;
int k,
int trig = 13,echo = 12,in1 = 3,in2 = 5,in3 = 6,in4 = 11,leftspeed = 230,rightspeed = 220;
float cm,dis[5];
void setup() {
    s.attach(10);            // initialize servo
    s.write(90);
    pinMode(trig,OUTPUT);    // initialize ultrasonic
    pinMode(echo,INPUT);
    allstop();               // initialize motor
    caldis();                // scan 5 directions
    turn(getmax());          // turn to the farest direction
}

void loop() {
    k = getdis();
    while(k >= safedis){     // go straight if enough space
        gostraight();        
        k = getdis();
    }
    allstop();               // stop and scan 5 directions
    caldis();
    turn(getmax());
}
int getmax(){                // get the farest direction
    int m = 0;
    for(int i = 0;i <= 4;i++){
        if(dis[i] == 0)      // over 1 meter
            return i;
        if(dis[i] > dis[m])
        m = i;
    }
    return m;
}
void turn(int x){           // turn to x direction
    int y = x*45-90;
    if(y < 0)
    {        
        analogWrite(in1,0);
        analogWrite(in2,rightspeed-50);
        analogWrite(in3,leftspeed-50);
        analogWrite(in4,0);
        delay(abs(y/90*1000));
    }
    else if(y > 0)
    {
        analogWrite(in1,rightspeed-50);
        analogWrite(in2,0);
        analogWrite(in3,0);
        analogWrite(in4,leftspeed-50);
        delay(abs(y/90*1000));
    }
    allstop();  
}
void gostraight(){             // go straight
    analogWrite(in1,0);
    analogWrite(in2,rightspeed);
    analogWrite(in3,0);
    analogWrite(in4,leftspeed);
    delay(100);
}
float getdis(){               // get distance
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    long etime = pulseIn(echo,HIGH);
    cm = etime/29/2;
    return cm;}


void caldis(){              // scan 5 directions
    for(int i = 0;i <= 4;i++){
        s.write(i*45); 
        delay(500);
        dis[i] = getdis();
    }
    s.write(90);
}
void allstop()              // stop all motors
{
    analogWrite(in1,0);              
    analogWrite(in2,0);
    analogWrite(in3,0);              
    analogWrite(in4,0);
    delay(500);
    return;
}
