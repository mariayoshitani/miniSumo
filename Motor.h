#ifndef __MOTOR__
#define __MOTOR__

#include <Arduino.h>

class Motor {

    int velocidade = 0;
    int pino1; // horário
    int pino2; // anti-horário
    
    public:
    // recebem velocidade de 0 a 100 e chamam analogWrite
        void setPinos(int pino1, int pino2);
        int getPino1();
        int getPino2();

        void setVelocidade(int v);
        int getVelocidade();

        void avanca(int v);
        void re(int v);
        void freio();
};


#endif