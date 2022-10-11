
int buzzer = 31;
bool tocarAgora = true;
int ledVerde = 17;
int ledVermelha = 16;
int ledAmarela = 18;


//PACMAN

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempoP = 105;


// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melodyP[] = {

  // Pacman
  // Score available at https://musescore.com/user/85429/scores/107109
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notesP = sizeof(melodyP) / sizeof(melodyP[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenoteP = (60000 * 4) / tempoP;

int dividerP = 0, noteDurationP = 0;





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
#define potL 80

// Potencia do motor secundario quando anda para os lados
// Este parametro define quao abrupto a robo realiza as curvas
#define potS 6

// Potencia quando o robo anda para frente
#define potF 130
#define potF2 230

// Valor de referencia da LINHA a ser seguida (adquirido pelos sensores)
#define linha 500

//Ultrasonic ultrasonic(dist_trig,dist_echo);

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
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelha, OUTPUT);
  pinMode(ledAmarela, OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  musica();
}

bool esta_esquerda = true;
bool esta_direita = false;
bool black_found = false;
int sensor_branco;

void loop() {

  sensor_branco = digitalRead(2);
  while ((sensor_branco == 1) && (esta_esquerda == true)) {
    digitalWrite(ledAmarela, 0);
    digitalWrite(ledVerde, 1);
    digitalWrite(ledVermelha, 0);
    control('r');
    delay(10);
    control('s');
    delay(25);
    sensor_branco = digitalRead(2);
  }
  control('s');
  delay(30);
  if ((sensor_branco == 0) && (esta_esquerda == true)){
      
    while(sensor_branco==0){
      digitalWrite(ledAmarela, 1);
      digitalWrite(ledVerde, 0);
      digitalWrite(ledVermelha, 0);
      control('r');
      delay(10);
      control('s');
      delay(25);
      sensor_branco = digitalRead(2);
    }
    control('w');
    control('w');
    control('w');
    control('w');
    control('s');
    delay(30);
    esta_esquerda = false;
    esta_direita = true;
  }
  while ((sensor_branco == 1) && (esta_direita == true)) {
    digitalWrite(ledAmarela, 0);
    digitalWrite(ledVerde, 1);
    digitalWrite(ledVermelha, 0);
    control('l');
    delay(10);
    control('s');
    delay(25);
    sensor_branco = digitalRead(2);
  }
  control('s');
  delay(100);
  if ((sensor_branco == 0) && (esta_direita == true)){
    while(sensor_branco==0){
      digitalWrite(ledAmarela, 1);
      digitalWrite(ledVerde, 0);
      digitalWrite(ledVermelha, 0);
      control('l');
      delay(10);
      control('s');
      delay(25);
      sensor_branco = digitalRead(2);
    }
    control('w');
    control('w');
    control('w');
    control('w');
    delay(30);
    control('s');
    delay(30);
    esta_esquerda = true;
    esta_direita = false;
  }
}

void sensor(){ // atribui a variavel distancia o valor de distancia do sensor ultrassonico
  digitalWrite(dist_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(dist_trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(dist_trig, LOW);
//  distancia = (ultrasonic.Ranging(CM));
}

void musica(){
  for (int thisNote = 0; thisNote < notesP * 2; thisNote = thisNote + 2) {
          // calculates the duration of each note
          dividerP = melodyP[thisNote + 1];
          if (dividerP > 0) {
            // regular note, just proceed
            noteDurationP = (wholenoteP) / dividerP;
          } else if (dividerP < 0) {
            // dotted notes are represented with negative durations!!
            noteDurationP = (wholenoteP) / abs(dividerP);
            noteDurationP *= 1.5; // increases the duration in half for dotted notes
          }

          // we only play the note for 90% of the duration, leaving 10% as a pause
          tone(buzzer, melodyP[thisNote], noteDurationP * 0.9);

          // Wait for the specief duration before playing the next note.
          delay(noteDurationP);

          // stop the waveform generation before the next note.
          noTone(buzzer);
        }
  
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
           analogWrite(m2C_pin, potF2);
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
           digitalWrite(m1A_pin, LOW);
           digitalWrite(m1B_pin, LOW);
           analogWrite(m1C_pin, potF);
           digitalWrite(m2A_pin, LOW);
           digitalWrite(m2B_pin, LOW);
           analogWrite(m2C_pin, potF);
           break;
     
      case 'l':
           digitalWrite(m2A_pin, HIGH);
           digitalWrite(m2B_pin, LOW);
           analogWrite(m1C_pin, 150);
           digitalWrite(m1B_pin, LOW);
           digitalWrite(m1A_pin, LOW);
           break;

      case 'r':
           analogWrite(m2C_pin, 70);
           digitalWrite(m2B_pin, LOW);
           digitalWrite(m2A_pin, LOW);
           digitalWrite(m1A_pin, HIGH);
           digitalWrite(m1B_pin, LOW);
           break;
         
           break;
      }  
}