#define step1dir 6
#define step2dir 8
#define step1stp 7
#define step2stp 9

#define in1 0
#define in2 1

void setup() {
  // put your setup code here, to run once:
  pinMode(step1dir, OUTPUT);
  pinMode(step1stp, OUTPUT);
  pinMode(step2dir, OUTPUT);
  pinMode(step2stp, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  /*digitalWrite(step1stp, 1);
  delay(1);
  digitalWrite(step1stp, 0);
  delay(1);*/
  // put your main code here, to run repeatedly:
  int get1 = analogRead(in1) - 517;
  int get2 = analogRead(in2) - 502;
  Serial.print(get1);
  Serial.print("      ");
  Serial.println(get2);
  //if(get1 < 0) get1 = get1 * -1;
  //if(get2 < 0) get2 = get2 * -1;

  if(get1 !=0)  doStep(0,1,get1);
  if(get2 !=0) doStep(1,1,get2);
  delay(10);
  
}

void doStep(int steppr, int steps, int stpspeed){
  if(steps < 0){
    steps = steps * -1;
    switch (steppr) {
      case 0:
        digitalWrite(step1dir, 1);
        for (int i = 0; i < steps; i++){
          digitalWrite(step1stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step1stp, 0);
          delayMicroseconds(stpspeed);
        }
        digitalWrite(step1dir, 0);
        break;
      case 1:
        digitalWrite(step2dir, 1);
        for (int i = 0; i < steps; i++){
          digitalWrite(step2stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step2stp, 0);
          delayMicroseconds(stpspeed);
        }
        digitalWrite(step2dir, 0);
        break;
    }
  }else{
    switch (steppr) {
      case 0:
        digitalWrite(step1dir, 1);
        for (int i = 0; i < steps; i++){
          digitalWrite(step1stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step1stp, 0);
          delayMicroseconds(stpspeed);
        }
        digitalWrite(step1dir, 0);
        break;
      case 1:
        digitalWrite(step2dir, 1);
        for (int i = 0; i < steps; i++){
          digitalWrite(step2stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step2stp, 0);
          delayMicroseconds(stpspeed);
        }
        digitalWrite(step2dir, 0);
        break;
    }
  }
}

