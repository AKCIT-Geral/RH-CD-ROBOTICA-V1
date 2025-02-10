// Código em C++ para Arduino
// Projeto: Pisca LED e Buzzer com som intermitente

void setup()
{
  pinMode(6, OUTPUT);  // Configura o pino 6 como saída para o LED
  pinMode(13, OUTPUT); // Configura o pino 13 como saída para o buzzer
}

void loop()
{
  digitalWrite(6, HIGH);  // Liga o LED no pino 6
  tone(13, 523, 1000);    // Toca um som de 523 Hz (nota Dó) no buzzer por 1000ms
  delay(500);             // Aguarda 500ms
  
  digitalWrite(6, LOW);   // Desliga o LED no pino 6
  noTone(13);             // Para o som do buzzer no pino 13
  delay(500);             // Aguarda 500ms antes de repetir o ciclo
}
