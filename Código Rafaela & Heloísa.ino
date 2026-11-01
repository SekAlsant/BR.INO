#include <Servo.h>

Servo motorEsquerdo;
Servo motorDireito;

const int S1 = 2; 
// Sensor 2 removido
const int S3 = 4; 
const int S4 = 5; 
const int S5 = 6; 
const int buzzerPin = 7; // Buzzer conectado no pino 7

// Pinos do Ultrassom
const int trigPin = 13;
const int echoPin = 12;

void setup() {
  pinMode(S1, INPUT);
  // Sensor 2 removido
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  motorEsquerdo.attach(9);
  motorDireito.attach(10);
  
  delay(500); 
}

void loop() {
  // NOVA REGRA ABSOLUTA (Prioridade 1): O Ultrassom
  int distanciaAtual = lerDistancia();
  
  if (distanciaAtual <= 15 && distanciaAtual > 0) { 
    // Toca o buzzer indicando obstáculo detectado!
    tone(buzzerPin, 1000);
    // Para brevemente antes de iniciar o desvio
    motorEsquerdo.writeMicroseconds(1500); 
    motorDireito.writeMicroseconds(1500);
    delay(100);
    
    // Executa o desvio
    desviarObstaculo();
  } else {
    // Se não há obstáculo, desliga o buzzer
    noTone(buzzerPin);
  }

  // --- SE ELE CHEGAR AQUI, É PORQUE NÃO TEM OBSTÁCULO ---
  
  // Lê a placa infravermelha
  int le1 = digitalRead(S1);
  // Sensor 2 removido
  int le3 = digitalRead(S3);
  int le4 = digitalRead(S4);
  int le5 = digitalRead(S5);

  // --- NOVA REGRA 0: Cruzamento Simples (+) ---
  if ( (le1 == LOW && le3 == LOW && le4 == LOW && le5 == LOW) || 
       (le1 == LOW && le5 == LOW) ) {
    atravessarCruzamento(); 
  }
  
  // --- 1. REGRA CRUCIAL: O Empurrãozinho da curva de 90° ---
  else if (le3 == LOW && le4 == LOW && le1 == HIGH && le5 == HIGH) {
    andarFrente(); 
  }
  
  // --- 2. REGRAS DE CURVA MÁXIMA (3 SENSORES) ---
  else if (le1 == LOW && le3 == LOW && le4 == HIGH && le5 == HIGH ){
    virarEsquerdaFechada();
  }
  else if (le1 == HIGH && le3 == LOW && le4 == LOW && le5 == LOW ){
    virarDireitaFechada();
  }

  // --- 3. REGRAS DE CURVA PARA A ESQUERDA (2 ou 1 sensor) ---
  else if (le1 == LOW && le3 == HIGH && le4 == HIGH && le5 == HIGH) {
    virarEsquerdaFechada();
  }
  else if (le1 == LOW) {
    virarEsquerdaFechada();
    delay(100);
  }
  // Espaço cego entre S1 e S3 tratado pela inércia

  // --- 4. REGRAS DE CURVA PARA A DIREITA (2 ou 1 sensor) ---
  else if (le1 == HIGH && le3 == HIGH && le4 == LOW && le5 == LOW) {
    virarDireitaFechada();
  }
  else if (le5 == LOW) {
    virarDireitaFechada();
  }
  else if (le4 == LOW) {
    virarDireitaSuave();
  }

  // --- 5. SÓ O MEIO VIU PRETO ---
  else if (le3 == LOW) {
    andarFrente();
  }

  // --- 6. O SEGREDO DOS GAPS (Tudo Branco) ---
  else {
    andarFrente();
  }
  
  delay(20); 
}

// --- AS REGRAS DE MOVIMENTO ---

void andarFrente() {
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1300);  
}

void virarEsquerdaSuave() {
  motorEsquerdo.writeMicroseconds(1300); 
  motorDireito.writeMicroseconds(1300);  
}

void virarEsquerdaFechada() {
  motorEsquerdo.writeMicroseconds(1000); 
  motorDireito.writeMicroseconds(1000);  
}

void virarDireitaSuave() {
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1700);  
}

void virarDireitaFechada() {
  motorEsquerdo.writeMicroseconds(2000); 
  motorDireito.writeMicroseconds(2000);  
}

void atravessarCruzamento() {
  motorEsquerdo.writeMicroseconds(2000); 
  motorDireito.writeMicroseconds(1000);  
  delay(400); 
}

int lerDistancia() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000); 
  int distance = (duration / 2) / 29.1;
  
  if (distance == 0) return 999; 
  return distance;
}

void desviarObstaculo() {
  // 1. Dar ré para desenganchar
  motorEsquerdo.writeMicroseconds(1000); 
  motorDireito.writeMicroseconds(2000);  
  delay(400); 

  // 2. Giro no próprio eixo para a direita
  virarDireitaFechada(); 
  delay(500); 

  // 3. Andar reto na diagonal
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1300);  
  delay(1000); 

  // 4. Modo Varredura: Procurar a linha (Giro para a esquerda)
  virarEsquerdaSuave(); 
  
  while(true) {
    int l1 = digitalRead(S1);
    // Sensor 2 removido
    int l3 = digitalRead(S3);
    int l4 = digitalRead(S4);
    int l5 = digitalRead(S5);
    
    // Ignorando o l2 na detecção de retorno para a linha
    if (l1 == LOW || l3 == LOW || l4 == LOW || l5 == LOW) {
      motorEsquerdo.writeMicroseconds(1500); 
      motorDireito.writeMicroseconds(1500);
      delay(200); 
      break; 
    }
  }
}
