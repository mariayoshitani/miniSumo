#include "Motor.h"

void Motor::setPinos(int in1, int in2) {
    pino1 = in1;
    pino2 = in2;
    pinMode(pino1, OUTPUT);
    pinMode(pino2, OUTPUT);
}
int Motor::getPino1() { return pino1; }
int Motor::getPino2() { return pino2; }

void Motor::setVelocidade(int v) { velocidade = v; }
int Motor::getVelocidade() { return velocidade; }

void Motor::avanca(int v){
    setVelocidade(map(v, 0, 100, 0, 255));
    digitalWrite(pino2, LOW);
    analogWrite(pino1, velocidade);
}

void Motor::re(int v) {
    setVelocidade(map(v, 0, 100, 0, 255));
    digitalWrite(pino1, LOW);
    analogWrite(pino2, velocidade);
}

void Motor::freio() {
    digitalWrite(pino1, LOW);
    digitalWrite(pino2, LOW);
}


