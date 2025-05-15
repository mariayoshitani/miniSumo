int pushbutton = 10; // declara o push button na porta 10
int led = 8; // declara led na porta 8
bool estadoled = 1; // variavel de controle

void setup()
{
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(led, OUTPUT);// define LED como saida
  digitalWrite(led, LOW);        
}

void loop()
{
  if (digitalRead(pushbutton) == LOW) // Se o botão for pressionado
  {
    estadoled = !estadoled; // troca o estado do LED
    digitalWrite(led, estadoled);
    while (digitalRead(pushbutton) == LOW);
    delay(100);
  }
}