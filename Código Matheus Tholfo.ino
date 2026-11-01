#include <Servo.h>

Servo motorEsquerdo;
Servo motorDireito;

const int S1 = 2; 
const int S2 = 3; 
const int S3 = 4; 
const int S4 = 5; 
const int S5 = 6; 
const int buzzerPin = 7; 

// Pinos do Ultrassom
const int trigPin = 13;
const int echoPin = 12;

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
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
    tone(buzzerPin, 1000);
    motorEsquerdo.writeMicroseconds(1500); 
    motorDireito.writeMicroseconds(1500);
    delay(100);
    desviarObstaculo();
  } else {
    noTone(buzzerPin);
  }

  // Lê a placa infravermelha NORMALMENTE (Sensor 4 restaurado!)
  int le1 = digitalRead(S1);
  int le2 = digitalRead(S2);
  int le3 = digitalRead(S3);
  int le4 = digitalRead(S4);
  int le5 = digitalRead(S5);

  // --- NOVA REGRA: INTERSECÇÃO 2, 3 e 4 ---
  // Dá um pulso para frente ao cruzar a intersecção
  if (le2 == LOW && le3 == LOW && le4 == LOW) {
    andarFrente();
    delay(150); // Pulso para frente (ajuste se precisar)
  }
  // --- NOVA REGRA 0: Cruzamento Simples (+) ---
  else if ( (le1 == LOW && le2 == LOW && le3 == LOW && le4 == LOW && le5 == LOW) || 
       (le1 == LOW && le5 == LOW) ) {
    atravessarCruzamento(); 
  }
  
  // --- 1. REGRA CRUCIAL: O Empurrãozinho da curva de 90° ---
  else if (le2 == LOW && le3 == LOW && le4 == LOW && le1 == HIGH && le5 == HIGH) {
    andarFrente(); 
  }
  
  // --- 2. REGRAS DE CURVA MÁXIMA (3 SENSORES) ---
  else if (le1 == LOW && le2 == LOW && le3 == LOW && le4 == HIGH && le5 == HIGH ){
    virarEsquerdaFechada();
  }
  else if (le1 == HIGH && le2 == HIGH && le3 == LOW && le4 == LOW && le5 == LOW ){
    virarDireitaFechada();
  }

  // =====================================================================
  // ===> NOVA REGRA: PRIORIDADE ESQUERDA 45 GRAUS (Matheus Tholfo) <===
  // Se o 1 e 2 virem a linha, mas o 4 também encostar, a esquerda vence!
  // =====================================================================
  else if (le1 == LOW && le2 == LOW && le4 == LOW) {
    virarEsquerdaFechada();
  }

  // --- CORREÇÃO DE LEITURA DUPLA EM DIAGONAL ---
  else if (le1 == LOW && le4 == LOW) {
    virarEsquerdaFechada();
  }
  else if (le5 == LOW && le2 == LOW) {
    virarDireitaFechada();
  }

  // --- SENSORES 2 E 4 JUNTOS ---
  else if (le2 == LOW && le4 == LOW) {
    andarFrente();
    delay(40); 
  }

  // --- 3. REGRAS DE CURVA PARA A ESQUERDA ---
  else if (le1 == LOW && le2 == LOW && le3 == HIGH && le4 == HIGH && le5 == HIGH) {
    virarEsquerdaFechada();
  }
  else if (le1 == LOW) {
    virarEsquerdaFechada();
    delay(400); 
  }
  else if (le2 == LOW) {
    virarEsquerdaSuave();
  }

  // --- 4. REGRAS DE CURVA PARA A DIREITA ---
  else if (le1 == HIGH && le2 == HIGH && le3 == HIGH && le4 == LOW && le5 == LOW) {
    virarDireitaFechada();
  }
  else if (le5 == LOW) {
    virarDireitaFechada();
    delay(400); 
  }
  else if (le4 == LOW) {
    virarDireitaSuave(); // Agora ele vai fazer a curva suave se só o 4 detectar!
  }

  // --- 5. SÓ O MEIO VIU PRETO ---
  else if (le3 == LOW) {
    andarFrente();
  }

  // --- 6. GAPS ---
  else {
    andarFrente();
  }
  
  delay(20); 
}

// --- AS REGRAS DE MOVIMENTO COM VELOCIDADE REDUZIDA ---
void andarFrente() {
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1000);  
}

void virarEsquerdaSuave() {
  motorEsquerdo.writeMicroseconds(1300); 
  motorDireito.writeMicroseconds(1300);  
}

void virarEsquerdaFechada() {
  motorEsquerdo.writeMicroseconds(1000); 
  motorDireito.writeMicroseconds(1000);  
}

void virarEsquerda90Graus() {
  motorEsquerdo.writeMicroseconds(1300); 
  motorDireito.writeMicroseconds(1300);  
}

void virarDireitaSuave() {
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1700);  
}

void virarDireitaFechada() {
  motorEsquerdo.writeMicroseconds(2000); 
  motorDireito.writeMicroseconds(2000);  
}

void virarDireita90Graus() {
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1700);  
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
  motorEsquerdo.writeMicroseconds(1000); 
  motorDireito.writeMicroseconds(2000);  
  delay(400); 

  virarDireitaFechada(); 
  delay(500); 

  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1300);  
  delay(1000); 

  virarEsquerdaSuave(); 
  
  while(true) {
    int l1 = digitalRead(S1);
    int l2 = digitalRead(S2);
    int l3 = digitalRead(S3);
    int l4 = digitalRead(S4);
    int l5 = digitalRead(S5);
    
    if (l1 == LOW || l2 == LOW || l3 == LOW || l4 == LOW || l5 == LOW) {
      motorEsquerdo.writeMicroseconds(1500); 
      motorDireito.writeMicroseconds(1500);
      delay(200); 
      break; 
    }
  }
}
