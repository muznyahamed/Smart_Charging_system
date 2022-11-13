#include <SoftwareSerial.h> 
SoftwareSerial SIM900(7, 8); 

String gotmsg;   
String message = "";   
int Rly_Pin = 2; 

   

void setup()
{
  Serial.begin(115200);
  SIM900.begin(19200); 

  pinMode(Rly_Pin, OUTPUT);   
  digitalWrite(Rly_Pin, HIGH); 

  
  SIM900.print("AT+CMGF=1\r");  
  delay(100);
  
 
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  delay(100);
}

void loop()
{
  
  receive_message();

  
  if(gotmsg.indexOf("on")>=0)
  {
    digitalWrite(Rly_Pin, LOW);
    message = "status: plugin the device";
    send_message(message);
  }
  
  
  if(gotmsg.indexOf("off")>=0)
  {
    digitalWrite(Rly_Pin, HIGH);
    message = "status: plugout the device";
    send_message(message);
  }        
}



void receive_message()
{
  if (SIM900.available() > 0)
  {
    gotmsg = SIM900.readString();
    Serial.print(gotmsg); 
    delay(10); 
  }
}



void send_message(String message)
{
  SIM900.println("AT+CMGF=1");    
  delay(100);  
  SIM900.println("AT+CMGS=\"+94750769396\""); 
  delay(100);
  SIM900.println(message);  
  delay(100);
  SIM900.println((char)26);  
  delay(100);
  SIM900.println();
  delay(1000);  
}
