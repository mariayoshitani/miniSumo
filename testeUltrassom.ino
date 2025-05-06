#include "Motor.h"
#include <HCSR04.h>

Motor Motor1, Motor2;

void setup() {
  Serial.begin(9600); // comunicação com motor serial para impressão dos valores lidos pelo ultra
  Motor1.setPinos(5, 6); // entradas 5 e 6 para motor 1
  Motor2.setPinos(10, 11); // entradas 10 e 11 para motor 2
}

void loop() {
  long distancia = Ultra1.dist();
  Serial.print(distancia); //imprime o valor da variável distancia
  Serial.println("cm");
  

  if (distancia > 20.00) { // se distancia maior que 20, motores param
    Motor1.setVelocidade(0);
    Motor2.setVelocidade(0);
    
  } else { // senão, velocidade aumenta conforme proximidade
    Motor1.setVelocidade(map(distancia, 20, 0, 0, 100));
    Motor2.setVelocidade(map(distancia, 20, 0, 0, 100));
  }

  Motor1.avanca(Motor1.getVelocidade());
  Motor2.avanca(Motor2.getVelocidade());
}
