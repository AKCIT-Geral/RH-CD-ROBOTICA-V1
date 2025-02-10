/*
PINO 6 - SENSOR DIREITO
PINO 7 - SENSOR ESQUERDO
PINO 5 - MOTOR ESQUERDO AVANTE
PINO 4 - MOTOR ESQUERDO REVERSO
PINO 3 - MOTOR DIREITO AVANTE
PINO 2 - MOTOR DIREITO REVERSO
PINO 11 - ATIVA MOTORES
*/

void setup()
{
  // Configuração dos sensores infravermelhos como entrada
  pinMode(6, INPUT);  // Sensor direito
  pinMode(7, INPUT);  // Sensor esquerdo

  // Configuração dos motores como saída
  pinMode(5, OUTPUT);  // Motor esquerdo avante
  pinMode(4, OUTPUT);  // Motor esquerdo reverso
  pinMode(3, OUTPUT);  // Motor direito avante
  pinMode(2, OUTPUT);  // Motor direito reverso

  pinMode(11, OUTPUT); // Ativação dos motores
  pinMode(13, OUTPUT); // LED indicador (não usado no código atual)

  // Garante que os motores começam desligados
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);

  // Habilita a alimentação dos motores
  digitalWrite(11, HIGH);
} // Fecha setup

void loop()
{
  // Ambos sensores detectam a superfície clara → Robô segue em frente
  if (digitalRead(7) == 0 && digitalRead(6) == 0) {
    digitalWrite(5, HIGH); // Motor esquerdo avante
    digitalWrite(3, HIGH); // Motor direito avante
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
  }

  // Apenas o sensor esquerdo detecta a linha escura → Curva para a direita
  if (digitalRead(7) == 0 && digitalRead(6) == 1) {
    digitalWrite(5, HIGH); // Motor esquerdo avante
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);  // Motor direito parado
    digitalWrite(2, LOW);
  }

  // Apenas o sensor direito detecta a linha escura → Curva para a esquerda
  if (digitalRead(7) == 1 && digitalRead(6) == 0) {
    digitalWrite(5, LOW);  // Motor esquerdo parado
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH); // Motor direito avante
    digitalWrite(2, LOW);
  }

  // Ambos sensores detectam a linha escura → Robô para
  if (digitalRead(7) == 1 && digitalRead(6) == 1) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  }

} // Fecha loop
