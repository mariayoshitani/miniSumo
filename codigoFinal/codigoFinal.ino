#include <HCSR04.h>

#define MOTOR_ESQ_PINO1 5 
#define MOTOR_ESQ_PINO2 6  
#define MOTOR_DIR_PINO1 3 
#define MOTOR_DIR_PINO2 11

#define TRIGGER_ESQ 12
#define ECHO_ESQ 9
#define TRIGGER_DIR 7
#define ECHO_DIR 8

#define INFRA_ESQ A4
#define INFRA_DIR A5

#define BRANCO 150
#define DIST_OPONENTE 60
#define VEL_MIN 20
#define VEL_MAX 60

class Motor 
{
    int velocidade = 0;
    int pino1; // horário
    int pino2; // anti-horário

public:
    void setPinos(int in1, int in2)
    {
        pino1 = in1;
        pino2 = in2;
        pinMode(pino1, OUTPUT);
        pinMode(pino2, OUTPUT);
    }

    int getPino1() { return pino1; }
    int getPino2() { return pino2; }

    void setVelocidade(int v) { velocidade = v; }
    int getVelocidade() { return velocidade; }

    // recebem velocidade de 0 a 100 e chamam analogWrite

    void avanca(int v)
    {
        setVelocidade(map(v, 0, 100, 0, 255));
        digitalWrite(pino2, LOW);
        analogWrite(pino1, velocidade);
    }

    void re(int v)
    {
        setVelocidade(map(v, 0, 100, 0, 255));
        digitalWrite(pino1, LOW);
        analogWrite(pino2, velocidade);
    }

    void freio()
    {
        digitalWrite(pino1, LOW);
        digitalWrite(pino2, LOW);
    }
};

Motor MotorEsq, MotorDir;
HCSR04 UltraEsq(TRIGGER_ESQ, ECHO_ESQ), UltraDir(TRIGGER_DIR, ECHO_DIR);

void setup()
{
    Serial.begin(9600);
    MotorEsq.setPinos(MOTOR_ESQ_PINO1, MOTOR_ESQ_PINO2);
    MotorDir.setPinos(MOTOR_DIR_PINO1, MOTOR_DIR_PINO2);

    // começa com os motores parados
    MotorEsq.freio();
    MotorDir.freio();
    delay(5000); // o robô deve ficar parado por 5 segundos antes de iniciar a batalha
}

void loop() {

    long distEsq = UltraEsq.dist();
    long distDir = UltraDir.dist();
    long infraEsq = analogRead(INFRA_ESQ);
    long infraDir = analogRead(INFRA_DIR);
    bool linhaEsq = infraEsq < BRANCO;
    bool linhaDir = infraDir < BRANCO;
    
    // se linha branca
    if (linhaEsq || linhaDir) {

        // dá ré
        MotorEsq.re(25);
        MotorDir.re(25);

        delay(500);
        
        if (linhaEsq) { // Gira para direita
            MotorEsq.avanca(25);
            MotorDir.re(25); 

        } else if (linhaDir) { // Gira para esquerda
            MotorEsq.re(25); 
            MotorDir.avanca(25);
        }
        delay (500);

    }


    // Se não estiver recuando nem girando, procura oponente
    // Verifica se algum dos ultra leu 0

    if (distEsq && distDir) {
        if (distEsq <= DIST_OPONENTE || distDir <= DIST_OPONENTE) {
            
            MotorEsq.avanca(map(distDir, DIST_OPONENTE, 1, VEL_MIN, VEL_MAX)); //quanto mais perto pela direita, motor esq vai mais rápido
            MotorDir.avanca(map(distEsq, DIST_OPONENTE, 1, VEL_MIN, VEL_MAX)); // //quanto mais perto pela esquerda, motor dir vai mais rápido
        }
    } else if (distEsq && ((distEsq <= DIST_OPONENTE))) {
        // se distEsq é valida e menor ou igual a DIST_OPONENTE, vai reto
        MotorEsq.avanca(map(distEsq, DIST_OPONENTE, 1, VEL_MIN, VEL_MAX));
        MotorDir.avanca(map(distEsq, DIST_OPONENTE, 1, VEL_MIN, VEL_MAX));

    } else if (distDir && ((distDir<= DIST_OPONENTE))) {
        // se distDir é valida e menor ou igual a DIST_OPONENTE, vai reto
        MotorEsq.avanca(map(distDir, DIST_OPONENTE, 1, VEL_MIN, VEL_MAX));
        MotorDir.avanca(map(distDir, DIST_OPONENTE, 1, VEL_MIN, VEL_MAX));

    } else {
        // se as duas distâncias não são válidas ou se são maiores que DIST_OPONENTE
        // procura girando proprio eixo
        MotorEsq.avanca(VEL_MIN);
        MotorDir.re(VEL_MIN);
    }  

}
