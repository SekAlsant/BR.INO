#include <Servo.h>



Servo motorEsquerdo;

Servo motorDireito;



// =================================================================

// ⚙️ AJUSTE DE VELOCIDADE (De 1 a 5)

// 1 = Muito Lento | 2 = Lento (Original) | 3 = Médio | 4 = Rápido | 5 = Máximo

int velocidadeRobo = 4; 

// =================================================================



const int S1 = 2; 

const int S2 = 3; 

const int S3 = 4; 

const int S4 = 5; 

const int S5 = 6; 



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

  int le3 = digitalRead(S3);

  int le4 = digitalRead(S4);

  int le5 = digitalRead(S5);



  if (le2 == LOW && le3 == LOW && le4 == LOW) {

    andarFrente();

    delay(150); 

  }

  else if ( (le1 == LOW && le2 == LOW && le3 == LOW && le4 == LOW && le5 == LOW) || 

       (le1 == LOW && le5 == LOW) ) {

    atravessarCruzamento(); 

  }

  else if (le2 == LOW && le3 == LOW && le4 == LOW && le1 == HIGH && le5 == HIGH) {

    andarFrente(); 

  }

  else if (le1 == LOW && le2 == LOW && le3 == LOW && le4 == HIGH && le5 == HIGH ){

    virarEsquerdaFechada();

  }

  else if (le1 == HIGH && le2 == HIGH && le3 == LOW && le4 == LOW && le5 == LOW ){

    virarDireitaFechada();

  }

  else if (le1 == LOW && le2 == LOW && le4 == LOW) {

    virarEsquerdaFechada();

  }

  else if (le1 == LOW && le4 == LOW) {

    virarEsquerdaFechada();

  }

  else if (le5 == LOW && le2 == LOW) {

    virarDireitaFechada();

  }

  else if (le2 == LOW && le4 == LOW) {

    andarFrente();

    delay(40); 

  }

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

  else if (le1 == HIGH && le2 == HIGH && le3 == HIGH && le4 == LOW && le5 == LOW) {

    virarDireitaFechada();

  }

  else if (le5 == LOW) {

    virarDireitaFechada();

    delay(400); 

  }

  else if (le4 == LOW) {

    virarDireitaSuave(); 

  }

  else if (le3 == LOW) {

    andarFrente();

  }

  else {

    andarFrente();

  }

  

  delay(20); 

}



void andarFrente() {

  int velEsquerda = 1500 + (velocidadeRobo * 100);

  int velDireita = 1500 - (velocidadeRobo * 100);



  if (velEsquerda > 2000) velEsquerda = 2000;

  if (velDireita < 1000) velDireita = 1000;



  motorEsquerdo.writeMicroseconds(velEsquerda);

  motorDireito.writeMicroseconds(velDireita);

}



void virarEsquerdaSuave() {

  int velCurva = 1500 - (velocidadeRobo * 100); 

  if (velCurva < 1000) velCurva = 1000;

  

  motorEsquerdo.writeMicroseconds(velCurva); 

  motorDireito.writeMicroseconds(velCurva);  

}



void virarEsquerdaFechada() {

  motorEsquerdo.writeMicroseconds(1000); 

  motorDireito.writeMicroseconds(1000);  

}



void virarEsquerda90Graus() {

  int velCurva = 1500 - (velocidadeRobo * 100); 

  if (velCurva < 1000) velCurva = 1000;

  

  motorEsquerdo.writeMicroseconds(velCurva); 

  motorDireito.writeMicroseconds(velCurva);  

}



void virarDireitaSuave() {

  int velCurva = 1500 + (velocidadeRobo * 100);

  if (velCurva > 2000) velCurva = 2000;

  

  motorEsquerdo.writeMicroseconds(velCurva); 

  motorDireito.writeMicroseconds(velCurva);  

}



void virarDireitaFechada() {

  motorEsquerdo.writeMicroseconds(2000); 

  motorDireito.writeMicroseconds(2000);  

}



void virarDireita90Graus() {

  int velCurva = 1500 + (velocidadeRobo * 100);

  if (velCurva > 2000) velCurva = 2000;

  

  motorEsquerdo.writeMicroseconds(velCurva); 

  motorDireito.writeMicroseconds(velCurva);  

}



void atravessarCruzamento() {

  motorEsquerdo.writeMicroseconds(2000); 

  motorDireito.writeMicroseconds(1000);  

  delay(400); 

} 
