#include <SoftwareSerial.h>   // Include SoftwareSerial library  

SoftwareSerial NIBP(A2,A3);    // Define pins RX y TX of Arduino 

byte startManualMode[10] = {02,'0','1',';',';','D','7',03}; // Start manual measurement
byte setManualMode[10] = {02,'0','3',';',';','D','9',03}; // Stop automatic measurement and switch to manualmeasurement mode
byte measurementResult[10] = {02,'1','8',';',';','D','F',03}; // Return system status (return result of last measurement)
double second,starttime,minute;
int measuring=0, out=0;
char data;

void setup()
{
  NIBP.begin(4800);       // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  Serial.println("NIBP Test - ABATON");
  init_NIBP();
  Serial.println("SetUp");
  starttime = millis();
  
}
 
void loop()
{
  if(NIBP.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    data=NIBP.read();
    Serial.print(data);
    if(data=='9'){
      out++;}
    else{
      out=0;}

    if(out==3){
      delay(1000);
      Serial.println("");
      status_NIBP();
      }
    
  }
  second = (millis() - starttime)/1000;
  if(second >=10){
    minute++;
    starttime = millis();
    measuring =1;
  }

  if((minute == 1) && (measuring ==1) ){
      Get_NIBP();
      measuring = 0 ;
      Serial.println("Start Measurement");
  }
}

void Get_NIBP(){  
  NIBP.write(startManualMode,8);  
}

void init_NIBP(){
  NIBP.write(setManualMode,8);
}

void status_NIBP(){
  NIBP.write(measurementResult,8);
}
