#include <Servo.h>

Servo motorEsquerdo;
Servo motorDireito;

const int S1 = 2; // Extrema Esquerda (OUT 1)
const int S2 = 3; // Meio Esquerda (OUT 2)
const int S3 = 4; // Centro (OUT 3)
const int S4 = 5; // Meio Direita (OUT 4)
const int S5 = 6; // Extrema Direita (OUT 5)

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  motorEsquerdo.attach(9);
  motorDireito.attach(10);
  
  delay(500); 
}

void loop() {
  int le1 = digitalRead(S1);
  int le2 = digitalRead(S2);
  int le3 = digitalRead(S3); // Adicionado a leitura do sensor central
  int le4 = digitalRead(S4);
  int le5 = digitalRead(S5);

  // --- 1. REGRA CRUCIAL: O Empurrãozinho da curva de 90° ---
  if (le2 == LOW && le3 == LOW && le4 == LOW && le1 == HIGH && le5 == HIGH) {
    andarFrente(); 
  }
  // --- 2. REGRAS DE CURVA MÁXIMA (3 SENSORES) - Devem vir primeiro! ---
  // Sensores 1, 2 e 3 no preto (Esquerda extrema)
  else if (le1 == LOW && le2 == LOW && le3 == LOW && le4 == HIGH && le5 == HIGH ){
    virarEsquerdaFechada();
  }
  // Sensores 3, 4 e 5 no preto (Direita extrema)
  else if (le1 == HIGH && le2 == HIGH && le3 == LOW && le4 == LOW && le5 == LOW ){
    virarDireitaFechada();
  }

  // --- 3. REGRAS DE CURVA PARA A ESQUERDA (2 ou 1 sensor) ---
  else if (le1 == LOW && le2 == LOW) {
    virarEsquerda90Graus();
  }
  else if (le1 == LOW) {
    virarEsquerdaFechada();
  }
  else if (le2 == LOW) {
    virarEsquerdaSuave();
  }

  // --- 4. REGRAS DE CURVA PARA A DIREITA (2 ou 1 sensor) ---
  else if (le4 == LOW && le5 == LOW) {
    virarDireita90Graus();
  }
  else if (le5 == LOW) {
    virarDireitaFechada();
  }
  else if (le4 == LOW) {
    virarDireitaSuave();
  }

  // --- 5. NENHUM SENSOR VIU PRETO (Ou apenas o le3 viu preto) ---
  else {
    andarFrente(); 
  }
  
  delay(20); 
}

// --- AS REGRAS DE MOVIMENTO COM VELOCIDADE REDUZIDA 🐢 ---

void andarFrente() {
  motorEsquerdo.writeMicroseconds(1700); // Velocidade reduzida
  motorDireito.writeMicroseconds(1300);  // Velocidade reduzida
 
}

// ---- ESQUERDA ----
void virarEsquerdaSuave() {
  motorEsquerdo.writeMicroseconds(1300); 
  motorDireito.writeMicroseconds(1300);  
  
}
//Como os motores estão virados para lados opostos no carrinho..., 
//Motor Esquerdo no 2000: Ele vai para FRENTE.   Motor Direito no 1000: Ele vai para FRENTE.   
void virarEsquerdaFechada() {
  motorEsquerdo.writeMicroseconds(1000); 
  motorDireito.writeMicroseconds(1000);  
}

void virarEsquerda90Graus() {
  motorEsquerdo.writeMicroseconds(1300); 
  motorDireito.writeMicroseconds(1300);  
  
}

// ---- DIREITA ----
void virarDireitaSuave() {
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1700);  

}
//Como os motores estão virados para lados opostos no carrinho..., 
//Motor Esquerdo no 2000: Ele vai para FRENTE.   Motor Direito no 2000: Ele vai para TRÁS.   
void virarDireitaFechada() {
  motorEsquerdo.writeMicroseconds(2000); 
  motorDireito.writeMicroseconds(2000);  
}

void virarDireita90Graus() {
  motorEsquerdo.writeMicroseconds(1700); 
  motorDireito.writeMicroseconds(1700);  

}
