/*
Programa Robo Seguidor de Linha
Exemplo de como controlar um robo para seguir um caminho no chao
utilizando 2 sensores de linha, o ArduinoUno e a Ponte H L298N para controlar 2 motores DC
e Sensor infravermelho.

Criado dia 20 de Fevereiro de 2015
por Alex Jos para apresentao no TCC: Urbanizao inteligente.

https://www.circuitar.com.br/projetos/Rodo-linha/
*/


// Parametros do Nanoshield Motor
//OBS: Estes sao os parametros a serem mudados caso seu carrinho nao esteja andando 
//na direcao correta:

// Motor 1 (Esquerda)
#define m1A_pin 6
#define m1B_pin 7
#define m1C_pin 9

// Motor 2 (Direita)
#define m2A_pin 4
#define m2B_pin 5
#define m2C_pin 3


// Potencias do motor:
// Potencia do motor principal quando anda para os lado
// Este parametro define quao rapido o robo realiza as curvas
#define potL 210

// Potencia do motor secundario quando anda para os lados
// Este parametro define quao abrupto a robo realiza as curvas
#define potS 6

// Potencia quando o robo anda para frente
#define potF 115

// Valor de referencia da LINHA a ser seguida (adquirido pelos sensores)
#define linha 500


void setup() {
  // Inicializa os pinos dos motores como saida
  pinMode(m1A_pin, OUTPUT);
  pinMode(m1B_pin, OUTPUT);
  pinMode(m1C_pin, OUTPUT);
  pinMode(m2A_pin, OUTPUT);
  pinMode(m2B_pin, OUTPUT);
  pinMode(m2C_pin, OUTPUT);
}

void loop() {
  // Adquire os valores do sensor esquerdo e direito (portas A0 e A1)
  int s1=analogRead(2);
  control('w');
  delay(3000);
  control('s');
  delay(3000);             
}

//Funcao que controla os motores
void control(char dir){
    switch(dir){
       //Anda para frente   
       case 'w':
           digitalWrite(m1A_pin, HIGH);
           digitalWrite(m1B_pin, LOW);
           analogWrite(m1C_pin, potF);
           digitalWrite(m2A_pin, HIGH);
           digitalWrite(m2B_pin, LOW);
           analogWrite(m2C_pin, potF);
           break;
              
       //Anda para tras   
       case 'z':
           digitalWrite(m1A_pin, LOW);
           digitalWrite(m1B_pin, HIGH);
           analogWrite(m1C_pin, potF);
           digitalWrite(m2A_pin, LOW);
           digitalWrite(m2B_pin, HIGH);
           analogWrite(m2C_pin, potF);
           break;
              
       //Anda para direita   
       case 'd':
           digitalWrite(m1A_pin, HIGH);
           digitalWrite(m1B_pin, LOW);
           analogWrite(m1C_pin, potL);
           analogWrite(m2C_pin, potS);
           digitalWrite(m2A_pin, HIGH);
           digitalWrite(m2B_pin, LOW);
           break;
              
       //Anda para esquerda
       case 'a':
           digitalWrite(m1A_pin, HIGH);
           digitalWrite(m1B_pin, LOW);
           analogWrite(m1C_pin, potS);
           analogWrite(m2C_pin, potL);
           digitalWrite(m2A_pin, HIGH);
           digitalWrite(m2B_pin, LOW);
           break;

       //Para o carrinho
       case 's':
           digitalWrite(m1A_pin, HIGH);
           digitalWrite(m1B_pin, HIGH);
           analogWrite(m1C_pin, potF);
           digitalWrite(m2A_pin, HIGH);
           digitalWrite(m2B_pin, HIGH);
           analogWrite(m2C_pin, potF);
           
      }       
}
