#include <Servo.h>

Servo motorEsquerdo;
Servo motorDireito;

const int S1 = 2; // Sensor 1 (Extrema Esquerda)
const int S2 = 3; // Sensor 2 (Meio Esquerda)
const int S3 = 4; // Sensor 3 (Centro)
const int S4 = 5; // Sensor 4 (Meio Direita)
const int S5 = 6; // Sensor 5 (Extrema Direita)

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  motorEsquerdo.attach(9);
  motorDireito.attach(10);
  
  delay(2000); 
}

void loop() {
  int le1 = digitalRead(S1);
  int le2 = digitalRead(S2);
  int le4 = digitalRead(S4);
  int le5 = digitalRead(S5);

  // O Sensor manda LOW quando vê PRETO (LED apaga)
  // O Sensor manda HIGH quando vê BRANCO (LED acende)

  // --- REGRA 1: Esquerda viu preto (Sensor 1 ou 2 apaga o LED) ---
  if (le1 == LOW || le2 == LOW) {
    virarEsquerda(); 
  } 
  // --- REGRA 2: Direita viu preto (Sensor 5 ou 4 apaga o LED) ---
  else if (le5 == LOW || le4 == LOW) {
    virarDireita();
  } 
  // --- REGRA 3: Nenhum viu preto (Tudo no BRANCO / LEDs Acesos) ---
  else {
    andarFrente(); 
  }
  
  delay(20); 
}

// --- AS SUAS REGRAS DE MOVIMENTO ---

void andarFrente() {
  // Ambas as rodas giram
  motorEsquerdo.writeMicroseconds(2000);
  motorDireito.writeMicroseconds(1000);
}

void virarEsquerda() {
  // Roda DIREITA gira, Roda ESQUERDA para (Ajusta a posição para a esquerda)
  motorEsquerdo.writeMicroseconds(1500); // Esquerda para
  motorDireito.writeMicroseconds(1000);  // Direita gira
}

void virarDireita() {
  // Roda ESQUERDA gira, Roda DIREITA para (Ajusta a posição para a direita)
  motorEsquerdo.writeMicroseconds(2000); // Esquerda gira
  motorDireito.writeMicroseconds(1500);  // Direita para
}
