#include "EmonLib.h"
EnergyMonitor emonl;
float ruido = 0.033; 
int tensao = 5;
#define LAMP 8


int LDR;
int cont;
int i; 


void setup()
{
  Serial.begin(9600); 
  pinMode(LAMP,OUTPUT); 
  digitalWrite(LAMP, HIGH);
  
   emonl.current(A1, 10);
    
    
}
void loop()
{
    
  delay(1000);
  
  double Irms = emonl.calcIrms(1480);
  Irms = (Irms - ruido) * 1000;       
  
  if (Irms < 0)
    {
        Irms = 0;
    }  
  
  char ls = Serial.read();
    
  if (ls == 'R') 
    {
        
        digitalWrite(LAMP, !digitalRead(LAMP));   
    }
  
  if (LDR > 600) 
    {
        Serial.println("Luz Desligada");    
    }
  else if (LDR <= 600)
    {
        Serial.println("Luz Ligada");
    }
    
  
  Serial.print("Corrente: ");
  Serial.print(Irms);
  Serial.println(" A");
  delay(500);
    
          
  LDR=0; 
  for(i=0;i<=10;i++)
  {
  cont=analogRead(A0);
  LDR = LDR+cont; 
  delay(10); 
  }
  LDR=LDR/10;
  Serial.println(LDR);

  (LDR >= 600) ? (digitalWrite(LAMP,HIGH)) : (digitalWrite(LAMP,LOW));  
}
