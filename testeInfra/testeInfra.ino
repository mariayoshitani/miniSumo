#define BRANCO 150

#define INFRA_DIR A4 // direita
#define INFRA_ESQ A5 // esquerda

#define M1_PINO1 5   //5: amarelo
#define M1_PINO2 6   //6: laranja

#define M2_PINO1 3   //10: azul
#define M2_PINO2 11   //11: verde

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

void setup() {
  Serial.begin(9600);
  Motor1.setPinos(M1_PINO1, M1_PINO2); 
  Motor2.setPinos(M2_PINO1, M2_PINO2);
}

void loop() {
  long lumiDir = analogRead(INFRA_DIR);
  long lumiEsq = analogRead(INFRA_ESQ);
  //Serial.println(lumiDir); 
  Serial.println(lumiEsq); 

  // se um dos sensores ler  branco, dá ré
  if ((lumiEsq < BRANCO) && (lumiDir < BRANCO)) { 
    Motor1.re(15);
    Motor2.re(15);
  } else { 
    Motor1.avanca(15);
    Motor2.avanca(15);
  }
}