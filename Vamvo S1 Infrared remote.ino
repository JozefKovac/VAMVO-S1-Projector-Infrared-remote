#include <IRremote.h>
IRsend irsend;

/******************************** VAMVO S1 projector IR remote ******************************
 used standard arduino nano
 
 pin 3 - Infra Red pin
 pin 4 - Flashlight LED (optional)
 
 4x4 buttons matrix pins
 
        5 6 7 8
        | | | |
   9 -- x x x x 
  10 -- x x x x
  11 -- x x x x 
  12 -- x x x x 

 Button layout:
  
     1 0 L S
     0 o 0 +
     e 0 m -
     < p > M
 
S - select input
0 - arrow
+ - volume
o - ENTER
e - esc
m - menu
M - mute
< - back
P - play/pause
> - forward
1 - standby / ON
L - flashlight Led

 *********************************************************************************************/
//simplified raw codes:

// enter
byte raw0[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0};
//1 on/off
byte raw1[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0};
// mute
byte raw2[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0};
// <<
byte raw3[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0};
// play/pause
byte raw4[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0};
// >>
byte raw5[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0};
//top
byte raw6[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0};
//left
byte raw7[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0};
//right
byte raw8[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0};
//bottom,
byte raw9[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
//esc
byte raw10[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0};
//menu
byte raw11[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0};
//select input
byte raw12[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0};
//volume -
byte raw13[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0};
// volume +
byte raw14[68]= {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0};


unsigned int rawTemp[68];

void setup()
{
  Serial.begin(9600);

    pinMode( 5,  OUTPUT); //column 1
    pinMode( 6,  OUTPUT); //column 2
    pinMode( 7,  OUTPUT); //column 3
    pinMode( 8,  OUTPUT); //column 4
    
    pinMode( 9,  INPUT_PULLUP); //row 1
    pinMode( 10, INPUT_PULLUP); //row 2
    pinMode( 11, INPUT_PULLUP); //row 3
    pinMode( 12, INPUT_PULLUP); //row 4

    pinMode ( 4, OUTPUT); // LED max 40mA

}

void loop()
{
//column 1
digitalWrite(5, LOW);
digitalWrite(6, HIGH);
digitalWrite(7, HIGH);
digitalWrite(8, HIGH);

if(!digitalRead(9 )){
  createRaw(raw1);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(10 )){
  createRaw(raw7);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(11 )){
  createRaw(raw10);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(12 )){
  createRaw(raw3);
  irsend.sendRaw(rawTemp,68,38);
}



//column 2
digitalWrite(5, HIGH);
digitalWrite(6, LOW);
digitalWrite(7, HIGH);
digitalWrite(8, HIGH);

if(!digitalRead(9 )){
  createRaw(raw6);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(10 )){
  createRaw(raw0);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(11 )){
  createRaw(raw9);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(12 )){
  createRaw(raw4);
  irsend.sendRaw(rawTemp,68,38);
}

//column 3
digitalWrite(5, HIGH);
digitalWrite(6, HIGH);
digitalWrite(7, LOW);
digitalWrite(8, HIGH);

if(!digitalRead(9 )){
  digitalWrite(4, HIGH);
  //createRaw(raw13);
  //irsend.sendRaw(rawTemp,68,38);
}else{digitalWrite(4, LOW);}

if(!digitalRead(10 )){
  createRaw(raw8);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(11 )){
  createRaw(raw11);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(12 )){
  createRaw(raw5);
  irsend.sendRaw(rawTemp,68,38);
}

//column 4
digitalWrite(5, HIGH);
digitalWrite(6, HIGH);
digitalWrite(7, HIGH);
digitalWrite(8, LOW);


if(!digitalRead(9 )){
  createRaw(raw12);
  irsend.sendRaw(rawTemp,68,38);
}

if(!digitalRead(10 )){
  createRaw(raw14);
  irsend.sendRaw(rawTemp,68,38);

}

if(!digitalRead(11 )){
//irsend.sendNEC(0x1807FA02F,38);
  createRaw(raw13);
  irsend.sendRaw(rawTemp,68,38);

}

if(!digitalRead(12 )){
  createRaw(raw2);
  irsend.sendRaw(rawTemp,68,38);
}

//recreating correct raw timing
void createRaw(uint8_t rawInput[68]){
 
for (int i = 0; i < 68; i++) {
  if(rawInput[i])rawTemp[i]=1650; else rawTemp[i]=605; 
  if(i==0) rawTemp[i]=8950; //begining sequecnce
  if(i==1) rawTemp[i]=4400;

  }

     return  rawTemp[68];
  }

