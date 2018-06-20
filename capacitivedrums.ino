#include <CapacitiveSensor.h>

#define NOTE_C4 0x3C
#define NOTE_CS4 0x3D 
#define NOTE_D4 0x3E
#define NOTE_DS4 0x3F
#define NOTE_E4 0x40

#define MIDI_CHANNEL 3

CapacitiveSensor sensorA = CapacitiveSensor(7, 2);
CapacitiveSensor sensorB = CapacitiveSensor(8, 3);
CapacitiveSensor sensorC = CapacitiveSensor(9, 4);
CapacitiveSensor sensorD = CapacitiveSensor(10, 5);
//CapacitiveSensor sensorE = CapacitiveSensor(8, 3);

int thresholdA = 40;
/*int thresholdB = 5000;
int thresholdC = 5000;
int thresholdD = 5000;
int thresholdE = 5000;*/
int thresholdB = 1000;
int thresholdC = 1000;
int thresholdD = 1000;
int thresholdE = 1000;

bool turnedOnA = false;
bool activatedA = false;

bool turnedOnB = false;
bool activatedB = false;

bool turnedOnC = false;
bool activatedC = false;

bool turnedOnD = false;
bool activatedD = false;

bool turnedOnE = false;
bool activatedE = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  long sensorValueA = sensorA.capacitiveSensor(30);
  long sensorValueB = sensorB.capacitiveSensor(30);
  long sensorValueC = sensorC.capacitiveSensor(30);
  long sensorValueD = sensorD.capacitiveSensor(30);
  //long sensorValueE = sensorE.capacitiveSensor(30);

//Serial.println(sensorValueA);
//Serial.println(sensorValueB);
//Serial.println(sensorValueC);
//Serial.println(sensorValueD);

  if(sensorValueA > thresholdA && !turnedOnA)
  {
    if(activatedA == false)
    {
    
      turnedOnA = true;
      Serial.println("a");
      noteOn(MIDI_CHANNEL, NOTE_C4, 0x7F);
    }
    activatedA = true;
  }
  else if(sensorValueA < thresholdA)
  {
    noteOff(MIDI_CHANNEL, NOTE_C4);   
    activatedA = false;
    turnedOnA = false;
  }
  //Serial.println(sensorValueB);
  if(sensorValueB > thresholdB && !turnedOnB)
  {
    if(activatedB == false)
    {
      turnedOnB = true;
      //Serial.println("b");
      noteOn(1, NOTE_CS4, 0x7F);
    }
    activatedB = true;
  }
  else if(sensorValueB < thresholdB)
  {
    noteOff(1, NOTE_CS4);
    activatedB = false;
    turnedOnB = false;
  }

  if(sensorValueC > thresholdC && !turnedOnC)
  {
    if(activatedC == false)
    {
      turnedOnC = true;
      //Serial.println("c");
      noteOn(1, NOTE_D4, 0x7F);
    }
    activatedC = true;
  }
  else if(sensorValueC < thresholdC)
  {
    noteOff(1, NOTE_D4);
    activatedC = false;
    turnedOnC = false;
  }

  if(sensorValueD > thresholdD && !turnedOnD)
  {
    if(activatedD == false)
    {
      turnedOnD = true;
      //Serial.println("d");
      noteOn(1, NOTE_DS4, 0x7F);
    }
    activatedD = true;
  }
  else if(sensorValueD < thresholdD)
  {
    noteOff(1, NOTE_DS4);
    activatedD = false;
    turnedOnD = false;
  }
  /*
  if(sensorValueE > thresholdE && !turnedOnE)
  {
    if(activatedE == false)
    {
      turnedOnE = true;
      //Serial.println("e");
      noteOn(1, NOTE_E4, 0x7F);
    }
    activatedE = true;
  }
  else if(sensorValueE < thresholdE)
  {
    noteOff(1, NOTE_E4);
    activatedE = false;
    turnedOnE = false;
  }
  */
  
  delay(10);
}

// Send a MIDI note on message
void noteOn(byte channel, byte pitch, byte velocity)
{
  // 0x90 is the first of 16 note on channels. Subtract one to go from MIDI's 1-16 channels to 0-15
  channel += 0x90 - 1;
  
  // Ensure we're between channels 1 and 16 for a note on message
  if (channel >= 0x90 && channel <= 0x9F)
  {
    Serial.write(channel);
    Serial.write(pitch);
    Serial.write(velocity);
  }
}

// Send a MIDI note off message
void noteOff(byte channel, byte pitch)
{
  // 0x80 is the first of 16 note off channels. Subtract one to go from MIDI's 1-16 channels to 0-15
  channel += 0x80 - 1;
  
  // Ensure we're between channels 1 and 16 for a note off message
  if (channel >= 0x80 && channel <= 0x8F)
  {
    Serial.write(channel);
    Serial.write(pitch);
    Serial.write((byte)0x00);
  }
}

// Send a MIDI control change message
void controlChange(byte channel, byte control, byte value)
{
  // 0xB0 is the first of 16 control change channels. Subtract one to go from MIDI's 1-16 channels to 0-15
  channel += 0xB0 - 1;
  
  // Ensure we're between channels 1 and 16 for a CC message
  if (channel >= 0xB0 && channel <= 0xBF)
  {
    Serial.write(channel);
    Serial.write(control);
    Serial.write(value);
  }
}
