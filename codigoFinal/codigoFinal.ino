#include <HCSR04.h>

#define MOTOR_ESQ_PINO1 5  // 5: amarelo
#define MOTOR_ESQ_PINO2 6  // 6: laranja
#define MOTOR_DIR_PINO1 10 // 10: azul
#define MOTOR_DIR_PINO2 11 // 11: verde

#define TRIGGER_ESQ 3
#define ECHO_ESQ 4
#define TRIGGER_DIR 7
#define ECHO_DIR 8

#define INFRA_ESQ A4
#define INFRA_DIR A5

#define BRANCO 100
#define DIST_OPONENTE 50
#define TEMPO_RE 200
#define TEMPO_GIRO 200

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

// Variáveis para uso do millis(), para não usar delay()
unsigned long tempoRe = 0;
unsigned long tempoGiro = 0;
bool re = false;
bool girando = false;

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

        // se não estiver dando ré nem girando
        if (!re || !girando) {

            // dá ré
            MotorEsq.re(100);
            MotorDir.re(100);
            re = true;
            tempoRe = millis(); // tempo para ré
        }
    }

    // se estiver dando ré, verifica se o tempo já passou de TEMPO_RE
    if (re && (millis() - tempoRe >= TEMPO_RE)) {
        re = false;
        if (linhaEsq) { // Gira para direita
            MotorEsq.avanca(100);
            MotorDir.re(100);

        } else if (linhaDir) { // Gira para esquerda
            MotorEsq.re(100);
            MotorDir.avanca(100);
        }
        girando = true;
        tempoGiro = millis();
    }
  
    // Se estiver girando, verifica se já terminou o tempo
    if (girando && (millis() - tempoGiro >= TEMPO_GIRO)) {
        girando = false;
        MotorEsq.freio();
        MotorDir.freio();
     }
  
    // Se não estiver recuando nem girando, procura oponente
    // Verifica se algum dos ultra leu 0
    if ((!re && !girando) && (distDir && distEsq)) {
        if (distEsq <= DIST_OPONENTE || distDir <= DIST_OPONENTE) {
            if (distEsq < distDir) { // Oponente à esquerda
                MotorEsq.avanca(60);
                MotorDir.avanca(100);

            } else if (distDir < distEsq) { // Oponente à direita
                MotorEsq.avanca(100);
                MotorDir.avanca(60);

            } else { // Oponente à frente
                MotorEsq.avanca(100);
                MotorDir.avanca(100);
            }
        }

    // oponente não detectado
    } else {
        // gira no próprio eixo devagar
        MotorEsq.avanca(40);
        MotorDir.re(40);

    }   
}
