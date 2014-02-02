/*
------------------------------------------------------------------------------------------------------
|                                                                                                    |
|    ARDUINO                                                                                         |
|                                                                                                    |
| GND  5V  2         3         4         5          6          7         8        10          A5     |
---|---|---|---------|---------|---------|----------|----------|---------|--------|-----------|-------
   |   |   |         |         |         |          |          |         |        |           |
+==[===|===[=|=======[=|=======[=|=======[=|========[=|========[=|=======[=|======[=====|==+  |
-|=|=======$=|=======$=|=======$=|=======$=|========$=|========$=|=======$=|======[===|=|==-  |
  S         B         B         B         B          B          B         B       |    P......|
+=|===============================================================================|========+



+==+ : Positive Bus
-==- : Negative Bus
S : Speaker
B : Button
P : petentiometer
$ : resistor
| , ... : wire
[ : wire which passes over the bus
*/

boolean prevVal= HIGH;
int notes[] = {
  31250, //c
  27777, //d
  25000, //e
  23809, //f
  20408, //g
  18518, //a
  16666  //b
};

void setup() {
  pinMode(10, OUTPUT); //speaker
  for(int i = 2; i <= 8; i++) //setting the arduino to read from all of the buttons
    pinMode(i, INPUT);
}

boolean safeRead(int pin) { //for eliminating electrical interference
  if(digitalRead(pin) == prevVal)
    delay(1);
  return digitalRead(pin);
}

void loop() {
  int octave = analogRead(A5) * 5 / 1023; //reading from the petentiometer and converting to an integer from 1 - 5
  for(int i = 0; i < 7; i++) {
    if(safeRead(i + 2)) { //send the note to the speaker if the button is pressed
      digitalWrite(10, HIGH);
      delayMicroseconds(notes[i] / pow(2, octave));
      digitalWrite(10, LOW);
      delayMicroseconds(notes[i] / pow(2, octave));
    }
  }
}
