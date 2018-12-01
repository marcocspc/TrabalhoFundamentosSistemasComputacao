// ------------ VARIAVEIS IMPORTANTES ------------------

//tempo entre sensores
const unsigned short int TEMPO_DELAY_ENTRE_SENSORES = 500;

//tipos de debug
const unsigned short int NO_DEBUG = 0;
const unsigned short int VIEW_SENSORS_DETECTION = 1;

//ver mais ou menos mensagens
unsigned short int debug_level = NO_DEBUG;

//guarda o numero de pessoas dentro da sala
unsigned short int numPessoas = 0;

//um struct para deteccao externa e outro para interna
boolean deteccao_interna = false;
boolean deteccao_externa = false;

//pinos onde serao conectados os detectores de presenca
//escolhi os pinos 6 e 7 DIGITAIS do arduino
//caso queira conectar em pinos diferentes, basta alterar
// o numero aqui
unsigned short int sensorInterno = 6;
unsigned short int sensorExterno = 10;

// ------------ FIM DAS VARIAVEIS ------------------



void setup() {
  //inicializar serial
  Serial.begin(9600);

  //inicializar portas dos sensores
  pinMode(sensorInterno, INPUT);
  pinMode(sensorExterno, INPUT);

  Serial.println("Serial inicializado e sensores preparados.");
}

void loop() {  
  //verificar deteccao no sensor externo
  if (digitalRead(sensorExterno) == HIGH && deteccao_externa == false) {
    Serial.println("Aguarde sensor externo...");
    aguardaSensor(sensorExterno);
    Serial.println("Passe mestre.");
    
    //registrar deteccao
    deteccao_externa = true;

    if (deteccao_interna == true) {
      //caso a deteccao interna tenha ocorrido primeiro, diminuir numero de pessoas dentro
      //da salafalse
      if (numPessoas > 0) {
        numPessoas = numPessoas - 1;
      }

      Serial.println("Verifiquei que uma pessoa saiu da sala!");
      Serial.print("Numero atual de pessoas: ");
      Serial.println(numPessoas);

      //resetar estado das deteccoes    
      deteccao_interna = false;
      deteccao_externa = false;
    }
  }

  //verificar deteccao no sensor interno
  if (digitalRead(sensorInterno) == HIGH && deteccao_interna == false) {
    Serial.println("Aguarde sensor interno...");
    aguardaSensor(sensorInterno);
    Serial.println("Passe mestre.");
    //registrar deteccao
    deteccao_interna = true;

    if (deteccao_externa == true) {
      //caso a deteccao externa tenha ocorrido primeiro, diminuir numero de pessoas dentro
      //da sala
      numPessoas = numPessoas + 1;

      Serial.println("Verifiquei que uma pessoa entrou na sala!");
      Serial.print("Numero atual de pessoas: ");
      Serial.println(numPessoas);

      //resetar estado das deteccoes    
      deteccao_interna = false;
      deteccao_externa = false;
    }
  }

  delay(TEMPO_DELAY_ENTRE_SENSORES);
}

void aguardaSensor (int sensor) {
  while (digitalRead(sensor) == 1) {}
}
