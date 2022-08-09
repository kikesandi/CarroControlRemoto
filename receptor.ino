#include "SPI.h"
#include "NRFLite.h"




struct ComboDatos // Any packet up to 32 bytes can be sent.
{
  float acelX;
  float acelY;
  float acelZ;
};

float valorX, valorY, valorZ;


NRFLite _radio;
ComboDatos _comboDatos;

void setup()
{
  // Leds
  pinMode(A5, OUTPUT);// ROJO DERECHA
  pinMode(A6, OUTPUT); // VERDE CENTRO
  pinMode(A7, OUTPUT); // VERDE IZQUIERDA


  // Driver Motor
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  
    Serial.begin(115200);
    _radio.init(0, 9, 10); // Set radio to Id = 0, along with its CE and CSN pins
}

void loop()
{
    while (_radio.hasData())
    {
        _radio.readData(&_comboDatos);
        /*Serial.print("Valor en X: ");
        Serial.print(_comboDatos.acelX);
        Serial.print(", valor en Y: ");
        Serial.print(_comboDatos.acelY);
        Serial.print(", valor en Z: ");
        Serial.println(_comboDatos.acelZ);*/

        valorX = _comboDatos.acelX; 
        valorY = _comboDatos.acelY; 
        valorZ = _comboDatos.acelZ;

        ZavanzaRetrocede(valorZ, valorX);        
    }
 
}





/*
            Funciones adicionales
*/



// Si X es mayor a 0.4, entonces se está doblando a la izquierda
// Si X es menor a -0.4 entonces se está doblando a la izquierda
// Si Z es mayor a 0.2 está avanzando
// Si z está entre 0 y 0.2 está detenido
// Si Z es menor a 0 entonces está retrocediendo
//

void XesMayor(){
  Serial.println("dobla izquierda");
  encenderVerdeIzq();
}


void XesIgual(){
  Serial.println("directo");
  encenderVerdeCen();
}

void XesMenor(){
  Serial.println("dobla derecha");
  encenderRojoDer();
}

void ZavanzaRetrocede(float valZ, float valX){
      /*Serial.print("Valor de z: ");
      Serial.print(valZ);
      Serial.print(", Valor de x: ");
      Serial.println(valX);*/
 
  if(valZ > 0.65){
    //Avanzando... hay que ver hacia donde
     if (valX > 0.3){
      //Avanza a la izquierda
      avanzaIzq();
      
     }else if((valX >= -0.3) && (valX <= 0.3)){
      //Avanza directo
       avanza();
     }else{
     
      //Avanza hacia la derecha
       avanzaDer();
     }

  }else if((valZ >=0.3) && (valZ <=0.65)){
    //Detenido ... se ejecuta detenerse
     Serial.println("Detenido");
   
  }else{
    // Reversa... hay que ver hacia donde
    if(valX > 0.2){
      //Retrocede a la izquierda
      retrocedeIzq();
    }else if((valX >= -0.2)&& (valX <=0.2)){
      //Retrocede en linea recta
      retrocede();
    }else{
      //Retrocede a la derecha
      retrocedeDer();
    }
     
  } 
}

// LEDS
void encenderVerdeIzq(){
  analogWrite(A5, LOW);
  digitalWrite(A6, LOW);
  analogWrite(A7, HIGH);
}

void encenderVerdeCen(){
  digitalWrite(A5, LOW);
  analogWrite(A6, HIGH);
  analogWrite(A7, 200);  
}

void encenderRojoDer(){
  digitalWrite(A5, HIGH);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
}

// CONDUCCIÓN

void avanza(){
  
  Serial.println("Avanza directo");
  //ENABLE ENCENDIDO
  analogWrite(3, 250);
  analogWrite(5, 250);
  //MOTOR 1
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  //MOTOR 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}// 






void retrocede(){
  Serial.println("Retrocede línea recta");
  //ENABLE ENCENDIDO
  analogWrite(3, 150);
  analogWrite(5, 150);
  //MOTOR 1
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  //MOTOR 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}


void avanzaDer(){
   Serial.println("Avanza derecha");
  //ENABLE ENCENDIDO
  analogWrite(3, 250);
  analogWrite(5, 0);
  //MOTOR 1
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  //MOTOR 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

void avanzaIzq(){
  Serial.println("Avanza izquierda");
  //ENABLE ENCENDIDO
  analogWrite(3, 0);
  analogWrite(5, 250);
  //MOTOR 1
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  //MOTOR 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}



void retrocedeDer(){
  Serial.println("Retrocede a la derecha");
  //ENABLE ENCENDIDO
  analogWrite(3, 0);
  analogWrite(5, 150);
  //MOTOR 1
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  //MOTOR 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW); 
}

void retrocedeIzq(){
  Serial.println("Retrocede a la izquierda");
  //ENABLE ENCENDIDO
  analogWrite(3, 150);
  analogWrite(5, 0);
  //MOTOR 1
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  //MOTOR 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW); 
}

void detener(){
  encenderRojoDer();
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  Serial.println("Detenido");
}
