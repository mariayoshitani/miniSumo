#include "Motor.h"

Motor Motor1, Motor2;

void setup() {
  Motor1.setPinos(5, 6); // entradas 5 e 6 para motor 1
  Motor2.setPinos(10, 11); // entradas 10 e 11 para motor 2
}

void loop() {

  // os 2 motores para frente a 50% da velocidade
  Motor1.avanca(50);
  Motor2.avanca(50);
  delay(3000);

  // os 2 motores dando ré a 100% da velocidade
  Motor1.re(100);
  Motor2.re(100);
  delay(3000);

  // motores param
  Motor1.freio();
  Motor2.freio();
  delay(3000);

  // motor1 a 10% e motor2 a 80% para frente
  Motor1.avanca(10);
  Motor2.avanca(80);
  delay(3000);

  // motor2 agora vai a 80% ré
  Motor2.re(80);
  delay(3000);

  // motor1 igual ao motor2
  Motor1.re(80);
  delay(3000);

  // motores param
  Motor1.freio();
  Motor2.freio();
  delay(3000);

}
