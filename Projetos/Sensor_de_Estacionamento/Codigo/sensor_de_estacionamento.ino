int distance = 0;  // Define a distância máxima de detecção (em cm)
double cm = 0;     // Armazena a distância calculada pelo sensor
int n = 0;         // Variável auxiliar (não utilizada diretamente)

// Função para medir a distância usando o sensor ultrassônico HC-SR04
long readUltrassonicdistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);   // Define o pino Trigger como saída
  digitalWrite(triggerPin, LOW); // Garante que o Trigger começa em nível baixo
  delayMicroseconds(1);
  digitalWrite(triggerPin, HIGH); // Envia um pulso ultrassônico
  delayMicroseconds(3);
  digitalWrite(triggerPin, LOW);  // Desliga o Trigger
  pinMode(echoPin, INPUT);        // Define o pino Echo como entrada
  return pulseIn(echoPin, HIGH);  // Mede o tempo que o pulso leva para retornar
}

// Função para calcular a distância e exibir no Serial Monitor
void calculaDistancia()
{
  distance = 300;  // Define 300 cm como limite máximo de detecção
  cm = 0.017233 * readUltrassonicdistance(12, 11);  // Converte tempo do pulso em cm
  Serial.print(cm);
  Serial.print("cm\n");  // Exibe a distância no monitor serial
}

// Configuração inicial dos pinos do Arduino
void setup()
{
  Serial.begin(11500);  // Inicializa a comunicação serial
  pinMode(3, OUTPUT);   // LED vermelho
  pinMode(5, OUTPUT);   // LED amarelo
  pinMode(6, OUTPUT);   // LED verde
  pinMode(10, OUTPUT);  // Buzzer
}

// Loop principal do programa
void loop()
{
  calculaDistancia();  // Mede a distância e atualiza a variável 'cm'

  // 🔵 Nenhum alerta: Mantém tudo desligado caso a distância seja maior que 300 cm
  do {
    digitalWrite(6, LOW);  // LED verde desligado
    digitalWrite(5, LOW);  // LED amarelo desligado
    digitalWrite(3, LOW);  // LED vermelho desligado
    noTone(10);            // Buzzer desligado
    calculaDistancia();
  } while (cm > distance);

  // 🟢 Aviso leve: Objeto entre 200 e 300 cm → Pisca LED Verde + Som Grave
  do {
    digitalWrite(6, HIGH);  // Acende LED verde
    digitalWrite(5, LOW);
    digitalWrite(3, LOW);
    tone(10, 100);          // Emite som grave (100 Hz)
    delay(300);
    digitalWrite(6, LOW);   // Apaga LED verde
    noTone(10);             // Para o som
    delay(900);
    calculaDistancia();
  } while (cm <= distance && cm > distance - 100);

  // 🟡 Alerta moderado: Objeto entre 100 e 200 cm → Pisca LED Amarelo + Som Médio
  do {
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);  // Acende LED amarelo
    digitalWrite(3, LOW);
    tone(10, 700);          // Emite tom médio (700 Hz)
    delay(300);
    digitalWrite(5, LOW);   // Apaga LED amarelo
    noTone(10);
    delay(500);
    calculaDistancia();
  } while (cm <= distance - 100 && cm > distance - 200);

  // 🔴 Alerta alto: Objeto entre 50 e 100 cm → Pisca LED Vermelho + Som Agudo
  do {
    digitalWrite(3, HIGH);  // Acende LED vermelho
    tone(10, 1500);         // Emite tom agudo (1500 Hz)
    delay(300);
    digitalWrite(3, LOW);   // Apaga LED vermelho
    noTone(10);
    delay(180);
    calculaDistancia();
  } while (cm <= distance - 200 && cm > distance - 250);

  // 🚨 Perigo: Objeto muito próximo (< 50 cm) → Todos os LEDs acesos + Som Contínuo
  do {
    digitalWrite(6, HIGH);  // Acende LED verde
    digitalWrite(5, HIGH);  // Acende LED amarelo
    digitalWrite(3, HIGH);  // Acende LED vermelho
    tone(10, 2000);         // Emite tom muito agudo (2000 Hz)
    delay(100);
    calculaDistancia();
  } while (cm <= distance - 250 && cm > distance - 300);

  delay(1);  // Pequeno atraso antes de reiniciar o loop
}
