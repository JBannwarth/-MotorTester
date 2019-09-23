// Written: 2019/09/24, Bannwarth, J.X.J.
#include <Servo.h>

#define N_SERVO 8

Servo ESCs[N_SERVO];
int curPwm = 1000;

void SendPWM( int pwm ){
  int pwmRemapped = map( constrain(pwm, 1000, 2000), 1000, 2000, 0, 180);
  for (int i = 0; i < N_SERVO; ++i){
    ESCs[i].write( pwmRemapped );
  }
}

void setup() {
  delay(5000);
  // Map pins 2 to 9 to ESCs
  for (int i = 0; i < N_SERVO; ++i){
    ESCs[i].attach(i+2,1000,2000);
  }

  Serial.begin(9600);
  Serial.println("Started");
}

void loop() {
  SendPWM( curPwm );
  Serial.print( "PWM: " ); Serial.println( curPwm );
  
  while (Serial.available() > 0) {
   char received = Serial.read();
   switch ( received ){
    case '1': curPwm = 1250; break;
    case '2': curPwm = 1500; break;
    case '3': curPwm = 1750; break;
    case '4': curPwm = 2000; break;
    case '0': curPwm = 1000; break;
    default: break;
   }
  }
  delay( 200 );
}
