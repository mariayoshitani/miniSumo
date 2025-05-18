// Partes do código estão comentadas para testar um sensor por vez, 
// assim é mais fácil verificar o que está errado e se as leiturs dos sensores
// estão certas

#include <HCSR04.h>

#define TRIGGER_ESQ 12
#define ECHO_ESQ 9
#define TRIGGER_DIR 7
#define ECHO_DIR 8

#define M1_PINO1 5 // amarelo
#define M1_PINO2 6 // laranja
#define M2_PINO1 3 // azul 
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
  HCSR04 UltraEsq(TRIGGER_ESQ, ECHO_ESQ);
  HCSR04 UltraDir(TRIGGER_DIR, ECHO_DIR);

void setup() {
  Serial.begin(9600);
  Motor1.setPinos(M1_PINO1, M1_PINO2);
  Motor2.setPinos(M2_PINO1, M2_PINO2); 
}

void loop() {

  long distEsq = UltraEsq.dist();
  //Serial.print(distEsq); //imprime a distância lida pelo ultrassom da esquerda
  //Serial.println("cm");


  long distDir = UltraDir.dist();
  Serial.print(distDir); //imprime a distância lida pelo ultrassom da direita
  Serial.println("cm");



  if (distEsq && distDir) {
    if ((distEsq <= 5) || (distDir <= 5)) { // se distancia maior que 5, motores dão ré
      Motor1.avanca(25);
      Motor2.avanca(25);
      
    } else { // senão, velocidade aumenta conforme proximidade
      Motor1.re(25);
      Motor2.re(25);
    }
  }


}