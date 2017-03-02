#define step1dir 7
#define step2dir 8
#define step1stp 9
#define step2stp 10
#define multi 10

#define max1 11000
#define min1 -11000
#define max2 6000
#define min2 -6000

#define in1 0
#define in2 1

int as1 = 0;
int as2 = 0;

boolean dir1 = false;
boolean dir2 = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(step1dir, OUTPUT);
  pinMode(step1stp, OUTPUT);
  pinMode(step2dir, OUTPUT);
  pinMode(step2stp, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {

  // put your main code here, to run repeatedly:
  int get1 = analogRead(in1) - 517;
  int get2 = analogRead(in2) - 502;
  
  if(get1 < 0){
    digitalWrite(step1dir, 1);
    get1 = get1 * -1;
    dir1 = true;
  }else{
    digitalWrite(step1dir, 0);
    dir1 = false;
  }

  if(get2 < 0){
    digitalWrite(step2dir, 1);
    get2 = get2 * -1;
    dir2 = true;
  }else{
    digitalWrite(step2dir, 0);
    dir2 = false;
  }

  get1 = map(get1, 0, 556, 254, 0);
  get2 = map(get2, 0, 556, 254, 0);

  if(get1 < 197)  doStep(0,get1);
  if(get2 < 197) doStep(1,get2);
  //delay(10);
  /*Serial.print(as1);
  Serial.print(" ^ ");
  Serial.println(as2);*/
  
}

void doStep(int steppr, int stpspeed){
  stpspeed = stpspeed * multi;

    switch (steppr) {
      case 0:
        if(!dir1 && as1+1 < max1){
          as1++;
          digitalWrite(step1stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step1stp, 0);
          delayMicroseconds(stpspeed);
        }
        if (dir1 && as1-1 > min1){
          as1--;
          digitalWrite(step1stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step1stp, 0);
          delayMicroseconds(stpspeed);
        }

        break;
      case 1:
        if(!dir2 && as2+1 < max2){
          as2++;
          digitalWrite(step2stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step2stp, 0);
          delayMicroseconds(stpspeed);
        }
        if (dir2 && as2-1 > min2){
          as2--;
          digitalWrite(step2stp, 1);
          delayMicroseconds(stpspeed);
          digitalWrite(step2stp, 0);
          delayMicroseconds(stpspeed);
        }
        break;
    }
}

