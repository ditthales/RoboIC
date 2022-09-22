#include <Ultrasonic.h>

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

// Sensor Ultrassonico
#define dist_echo 10
#define dist_trig 8


// Potencias do motor:
// Potencia do motor principal quando anda para os lado
// Este parametro define quao rapido o robo realiza as curvas
#define potL 60

// Potencia do motor secundario quando anda para os lados
// Este parametro define quao abrupto a robo realiza as curvas
#define potS 6

// Potencia quando o robo anda para frente
#define potF 50

// Valor de referencia da LINHA a ser seguida (adquirido pelos sensores)
#define linha 500

int distancia;

Ultrasonic ultrasonic(dist_trig,dist_echo);

void setup() {
  // Inicializa os pinos dos motores como saida
  pinMode(m1A_pin, OUTPUT);
  pinMode(m1B_pin, OUTPUT);
  pinMode(m1C_pin, OUTPUT);
  pinMode(m2A_pin, OUTPUT);
  pinMode(m2B_pin, OUTPUT);
  pinMode(m2C_pin, OUTPUT);
  pinMode(dist_echo, INPUT);
  pinMode(dist_trig, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  int s1=digitalRead(2); //le se ta no preto ou branco
  sensor(); //ativa o sensor de distancia
    
  if (distancia < 30){    //se achar algum obstaculo a menos de 30cm desvia indo pra esquerda até não achar mais
    desvio();
  }else{
    seguirPreto(s1);       //se não achar ele segue a linha preta
  }
               
}

void seguirPreto(int s1){
  if (s1 == 0){  //se o sensor retornar preto ele anda em frente
    control('w');
    Serial.println("deveria andar pra frente");
  }else{   //se nao retornar, faz zigue zague até achar a linha preta novamente, girando pelo próprio eixo e aumentando a amplitude do movimento a cada repetição.
    int tempo = 10; // variavel que vai dizer quantos ms durará cada virada
    bool flag = false; //variavel para sair do loop
    while(true){
      Serial.println("deveria fazer zigzag");
      int s2=digitalRead(2); //leitura do sensor
      control('a'); //vira a esquerda
      for(int i = 0;i<tempo;i=i+10){  //durante (tempo) milissegundos
        delay(10);
        s2 = digitalRead(2); //le novamente o sensor e se achar preto sai do for
        if (s2==0){
           flag = true;
           break;
        }
      }
      if(flag==true){ //sai do while se achar preto anteriormente
        break;
      }
      tempo = tempo + 10; //soma +10 ms no tempo
      Serial.println("deveria fazer zigzag");
      control('d'); //repete tudo para a direita
      for(int i = 0;i<tempo;i=i+10){
        delay(10);
        s2 = digitalRead(2);
        if (s2==0){
           flag = true;
           break;
        }
      }
      if(flag==true){
        break;
      }
      tempo = tempo + 10;
      
    }
  }
}

void desvio(){ //apenas vira a esquerda ate nao achar mais nada
  control('a');
}

void sensor(){ // atribui a variavel distancia o valor de distancia do sensor ultrassonico
  digitalWrite(dist_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(dist_trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(dist_trig, LOW);
  distancia = (ultrasonic.Ranging(CM));
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
           analogWrite(m2C_pin, potL);
           digitalWrite(m2A_pin, LOW);
           digitalWrite(m2B_pin, HIGH);
           break;
              
       //Anda para esquerda
       case 'a':
           digitalWrite(m1A_pin, LOW);
           digitalWrite(m1B_pin, HIGH);
           analogWrite(m1C_pin, potL);
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
