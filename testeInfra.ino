#include "Motor.h"

void setup() {
  Serial.begin(9600); // comunicação com motor serial para impressão dos valores lidos pelo infra
  Motor1.setPinos(5, 6); // entradas 5 e 6 para motor 1
  Motor2.setPinos(10, 11); // entradas 10 e 11 para motor 2
}

void loop() {
  long lumi = analogRead(A4); // le a luminosidade pela entrada analógica 4
  Serial.println(lumi); //imprime o valor da variável lumi

  if (lumi < 150) { // se branco, motores avancam a 50% da velocidade máxima
    Motor1.avanca(50);
    Motor2.avanca(50);
  } else { // senão, motores giram no sentido "ré" na mesma velocidade
    Motor1.re(50);
    Motor2.re(50);
  }
}