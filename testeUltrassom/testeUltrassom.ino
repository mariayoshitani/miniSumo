// Partes do código estão comentadas para testar um sensor por vez, 
// assim é mais fácil verificar o que está errado e se as leiturs dos sensores
// estão certas

#include <HCSR04.h>

#define TRIGGER1 3 
#define ECHO1 4
#define TRIGGER2 7
#define ECHO2 8

#define M1_PINO1 5 // amarelo
#define M1_PINO2 6 // laranja
#define M2_PINO1 10 // azul 
#define M2_PINO2 11 // verde

class Motor{
  int velocidade = 0;
    int pino1; // horário
    int pino2; // anti-horário
    
    public:
        void setPinos(int in1, int in2) {
          pino1 = in1;
          pino2 = in2;
          pinMode(pino1, OUTPUT);
          pinMode(pino2, OUTPUT);
        }

        int getPino1()  { return pino1; }
        int getPino2()  { return pino2; }

        void setVelocidade(int v)  { velocidade = v; }
        int getVelocidade()  { return velocidade; }

        // recebem velocidade de 0 a 100 e chamam analogWrite

        void avanca(int v) {
          setVelocidade(map(v, 0, 100, 0, 255));
          digitalWrite(pino2, LOW);
          analogWrite(pino1, velocidade);
        }

        void re(int v) {
          setVelocidade(map(v, 0, 100, 0, 255));
          digitalWrite(pino1, LOW);
          analogWrite(pino2, velocidade);
        }

        void freio() {
          digitalWrite(pino1, LOW);
          digitalWrite(pino2, LOW);
        }
};

  Motor Motor1, Motor2;
  HCSR04 Ultra1(TRIGGER1, ECHO1);
  HCSR04 Ultra2(TRIGGER2, ECHO2);

void setup() {
  Serial.begin(9600);
  Motor1.setPinos(M1_PINO1, M1_PINO2); // entradas 5 e 6 para motor 1
  //5: amarelo
  //6: laranja
  Motor2.setPinos(M2_PINO1, M2_PINO2); // entradas 10 e 11 para motor 2
  //10: azul
  //11: verde
}

void loop() {
  
  long dist1 = Ultra1.dist();
  Serial.print(dist1); //imprime o valor da variável distancia
  Serial.println("cm");

  long dist2 = Ultra2.dist();
  Serial.print(dist2); //imprime o valor da variável distancia2
  Serial.println("cm");

  if ((dist1 != 0) && (dist2 != 0)) {
    if ((dist1 > 5) || (dist2 > 5)) { // se distancia maior que 5, motores avanca
      Motor1.avanca(10);
      Motor2.avanca(10);
      
    } else { // senão, velocidade aumenta conforme proximidade
      Motor1.re(10);
      Motor2.re(10);
    }
  }


}