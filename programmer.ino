int WE = 7; //Write enable pin
int addr1=2, addr2=3, addr3=4, addr4=5, addr5=6, addr6=A1; //Address pins that this program will write to on the EEPROM. Any other pin not referanced should be tied to ground
int IO1=8, IO2=9, IO3=10, IO4=11, IO5=12, IO6=13, IO7=A0; //The input pins for the EEPROM. Every IO pin that wasn't referanced should be tied to ground
int loop_stop = 0; //this stops the programmer from re-running
int digit1 = 0, digit2 = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(WE,OUTPUT);
  digitalWrite(WE, HIGH);
  
  pinMode(addr1, OUTPUT);
  pinMode(addr2, OUTPUT);
  pinMode(addr3, OUTPUT);
  pinMode(addr4, OUTPUT);
  pinMode(addr5, OUTPUT);
  pinMode(addr6, OUTPUT);

  pinMode(IO1, OUTPUT);
  pinMode(IO2, OUTPUT);
  pinMode(IO3, OUTPUT);
  pinMode(IO4, OUTPUT);
  pinMode(IO5, OUTPUT);
  pinMode(IO6, OUTPUT);
  pinMode(IO7, OUTPUT);
}

void writetoEEPROM(){ //this will enable the write bit to EEPROM
  digitalWrite(WE, HIGH);
  delay(1000);
  digitalWrite(WE, LOW);
  delay(50);
  digitalWrite(WE,HIGH);
}

void IO_SevenSegSet(int number) { //this will set the values in the given addr for Seven segment display
// _________
//|    c    |
//|  -----  |
//|b|     |d|
//| |     | |
//|  --a--  |
//|e|     |g|
//| |     | |
//|  --f--  |
//|_________|
//
  if (number == 0) {
    digitalWrite(IO1, HIGH); //a
    digitalWrite(IO2, LOW); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, LOW); //e
    digitalWrite(IO6, LOW); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 1) {
    digitalWrite(IO1, HIGH); //a
    digitalWrite(IO2, HIGH); //b
    digitalWrite(IO3, HIGH); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, HIGH); //e
    digitalWrite(IO6, HIGH); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 2) {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, HIGH); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, LOW); //e
    digitalWrite(IO6, LOW); //f
    digitalWrite(IO7, HIGH); //g
  } else if (number == 3) {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, HIGH); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, HIGH); //e
    digitalWrite(IO6, LOW); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 4) {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, LOW); //b
    digitalWrite(IO3, HIGH); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, HIGH); //e
    digitalWrite(IO6, HIGH); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 5) {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, LOW); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, HIGH); //d
    digitalWrite(IO5, HIGH); //e
    digitalWrite(IO6, LOW); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 6) {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, LOW); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, HIGH); //d
    digitalWrite(IO5, LOW); //e
    digitalWrite(IO6, LOW); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 7) {
    digitalWrite(IO1, HIGH); //a
    digitalWrite(IO2, HIGH); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, HIGH); //e
    digitalWrite(IO6, HIGH); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 8) {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, LOW); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, LOW); //e
    digitalWrite(IO6, LOW); //f
    digitalWrite(IO7, LOW); //g
  } else if (number == 9) {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, LOW); //b
    digitalWrite(IO3, LOW); //c
    digitalWrite(IO4, LOW); //d
    digitalWrite(IO5, HIGH); //e
    digitalWrite(IO6, HIGH); //f
    digitalWrite(IO7, LOW); //g
  } else {
    digitalWrite(IO1, LOW); //a
    digitalWrite(IO2, HIGH); //b
    digitalWrite(IO3, HIGH); //c
    digitalWrite(IO4, HIGH); //d
    digitalWrite(IO5, HIGH); //e
    digitalWrite(IO6, HIGH); //f
    digitalWrite(IO7, HIGH); //g
  }
}

void ADDR_Set(int addr, int addrbit) { //this is for the addrs. addrbit must be a binary value
  int pinstate = 0;
  
  if (addrbit == 0)
    pinstate = 0;
  else
    pinstate = 1;
  
  if (addr == 0) //addr = 0 points to addr1
    digitalWrite(addr1,pinstate);
  else if (addr == 1) //addr = 0 points to addr1
    digitalWrite(addr2,pinstate);
  else if (addr == 2) //addr = 0 points to addr1
    digitalWrite(addr3,pinstate);
  else if (addr == 3) //addr = 0 points to addr1
    digitalWrite(addr4,pinstate);
  else if (addr == 4) //addr = 0 points to addr1
    digitalWrite(addr5,pinstate);
}

void loop() {
  for (int i=B00000; (i <= B11110) && loop_stop == 0; i++) { // loop until i reaches 30
    
    //this will set the binary value of i to the specific addresses on the EEPROM
    for (int x=0; x < 5; x++) { 
      ADDR_Set(x, bitRead(i,x)); //x tells the function what addr to point to. bitRead gives the value to the addr
    }

    //There is a clock signal attached to a address pin on the EEPROM. This allows me to use 1 EEPROM to be attached to 2 seven segment displays.
    //When the clock is LOW, it will display the first digit on the right display.
    //When the clock is HIGH, it will display the second digit on the left display. Since this is done really fast, the human eye cant see any flickering
    //This IF statment accounts for the clock
    if (i >= 10) {
      digit1 = i % 10; //lets say i= 14. this will get the 4
      digit2 = (i / 10) % 10; //this will get the 1
      
      digitalWrite(addr6,LOW); // when the calc is actually running, and it recieves a LOW on that specific addr, then that must mean the left segment display is off. So display a 4 on the right segment if i = 14, for example
      IO_SevenSegSet(digit1);
      writetoEEPROM();

      digitalWrite(addr6,HIGH); // when the clock is HIGH, the left segment display must be on. so display a 1 if i =14, for example
      IO_SevenSegSet(digit2);
      writetoEEPROM();
    } else { //if the number is below 10 (less than two digits, display a 0 on the left segment display
      digitalWrite(addr6,HIGH);
      IO_SevenSegSet(0);
      writetoEEPROM();
      
      digitalWrite(addr6,LOW);
      IO_SevenSegSet(i);
      writetoEEPROM();
    }
    
    Serial.print("Wrote ");
    Serial.print(i);
    Serial.print(" to ADDRS: ");
    for (int x=0; x < 5; x++) { 
      Serial.print(bitRead(i,x));
    }
    Serial.print(" + 0/1 (Clock Bit)");
    Serial.println(".");

  }

  if (loop_stop == 0) { //This will stop the for loop
    Serial.println("**********************");
    Serial.println("*        Done        *");
    Serial.println("**********************");
    
    loop_stop = 1;
  }
}
