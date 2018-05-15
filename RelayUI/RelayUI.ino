void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  for (int i=14; i < 54; i++){
    digitalWrite(i, HIGH );
  }
  for (int i=14; i < 54; i++){
    pinMode(i,OUTPUT);
  }
  //attachInterrupt( digitalPinToInterrupt( 2 ), wake2, RISING );
  //attachInterrupt( digitalPinToInterrupt( 3 ), wake3, RISING );
}

int sleeping = 0;

int posmap[] = { 
    23, 27, 31, 35, 
    39, 43, 47, 51, 
    22, 26, 30, 34, 
    38, 42, 46, 50, 
    14, 16, 18, 20 
};

int negmap[] = { 
    25, 29, 33, 37, 
    41, 45, 49, 53, 
    24, 28, 32, 36, 
    40, 44, 48, 52, 
    15, 17, 19, 21 
};

int protocolState = 0;
int accum = 0;
void loop() {
  if (Serial.available() > 0) {
    int incomingByte; 
    // read the incoming byte:
    incomingByte = Serial.read();
    if( protocolState == 0 ) {
      if( incomingByte == 'P' ) {
        protocolState = 1;
      }
      if( incomingByte == 'N' ) {
        protocolState = 3;
      }
    }
    else if( protocolState == 1 || protocolState == 3 ) {
       if( incomingByte >= '0' && incomingByte <= '9' ){
          accum = incomingByte - '0';
          protocolState++;
       }else protocolState = 0;
    }
    else if( protocolState == 2 || protocolState == 4 ) {
       if( incomingByte >= '0' && incomingByte <= '9' ) {
          accum *= 10;
          accum += incomingByte - '0';
          if( protocolState == 2 ) {
              digitalWrite( posmap[accum], LOW );
              delay( 50 );
              digitalWrite( posmap[accum], HIGH );
          } else {
              digitalWrite( negmap[accum], LOW );
              delay( 50 );
              digitalWrite( negmap[accum], HIGH );
          }
          accum = 0;
          protocolState = 0;
            
       }else protocolState = 0;
       
    }
  }
}

void wake2() {

}

void wake3() {

}

