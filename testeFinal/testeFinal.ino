#include <HCSR04.h>

#define M1_PINO1 5  // 5: amarelo
#define M1_PINO2 6  // 6: laranja
#define M2_PINO1 10 // 10: azul
#define M2_PINO2 11 // 11: verde

#define TRIGGER1 3
#define ECHO1 4
#define TRIGGER2 7
#define ECHO2 8

#define INFRA1 A4
#define INFRA2 A5

#define BRANCO 100

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

Motor Motor1, Motor2;
HCSR04 Ultra1(TRIGGER1, ECHO1), Ultra2(TRIGGER2, ECHO2);

void setup()
{
    Serial.begin(9600);
    Motor1.setPinos(M1_PINO1, M1_PINO2);
    Motor2.setPinos(M2_PINO1, M2_PINO2);
}

void loop()
{
    // código ultra
    // MOTOR1
    // se objeto a menos de 5 cm, ré
    // senão, para frente
    long distancia1 = Ultra1.dist();
    Serial.print(distancia1); // imprime o valor da dist lida pelo ultra1
    Serial.println("cm");

    long distancia2 = Ultra2.dist();
    Serial.print(distancia2); // imprime o valor da dist lida pelo ultra1
    Serial.println("cm");

    if (distancia1 <= 5.00)
    { // se distancia menor ou igual a 5, motor1 avanca
        Motor1.avanca(10);
    }
    else
    { // senão, motor1 dá ré
        Motor1.re(10);
    }

    // código infra
    // MOTOR2
    // se identifica (lê) <= BRANCO, ré
    // senão, para frente
    long lumi1 = analogRead(INFRA1); // le a luminosidade pela entrada analógica
    long lumi2 = analogRead(INFRA2);
    Serial.println(lumi1); // imprime o valor da variável lumi1
    Serial.println(lumi2); // imprime o valor da variável lumi2

    if ((lumi1 < BRANCO) || (lumi2 < BRANCO))
    { // se branco, motor2 dá ré a 10% da velocidade máxima
        Motor2.re(10);
    }
    else
    { // senão, motor2 avança
        Motor2.avanca(10);
    }
}