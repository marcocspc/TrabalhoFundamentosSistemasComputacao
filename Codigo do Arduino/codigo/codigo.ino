// ------------ VARIAVEIS IMPORTANTES ------------------

//contara um 'tempo' de loop, ele sera util para 
//verificar se uma pessoa entrou ou saiu da sala
int tempo = 0;

//guarda o numero de pessoas dentro da sala
unsigned short int numPessoas = 0;

//struct que auxiliara na deteccao da entrada e saida de pessoas
struct Deteccao {
  boolean detected;
  int timeOfLastDetection;
};

//um struct para deteccao externa e outro para interna
Deteccao deteccao_interna = {false, 0};
Deteccao deteccao_externa = {false, 0};

//pinos onde serao conectados os detectores de presenca
//escolhi os pinos 6 e 7 DIGITAIS do arduino
//caso queira conectar em pinos diferentes, basta alterar
// o numero aqui
unsigned short int sensorInterno = 6;
unsigned short int sensorExterno = 7;

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
  if (digitalRead(sensorExterno) == HIGH) {
    //registrar deteccao
    deteccao_externa.detected = true;
    deteccao_externa.timeOfLastDetection = tempo;

    Serial.print("Detectei algo no sensor externo! Momento:");
    Serial.println(detccao_externa.timeOfLastDetection);
  }

  //verificar deteccao no sensor interno
  if (digitalRead(sensorInterno) == HIGH) {
    //registrar deteccao
    deteccao_interna.detected = true;
    deteccao_interna.timeOfLastDetection = tempo;

    Serial.print("Detectei algo no sensor interno! Momento:");
    Serial.println(deteccao_interna.timeOfLastDetection);
  }

  //verificar se houve deteccao nos dois sensores
  if (deteccao_externa.detected && deteccao_interna.detected) {
    Serial.println("Opa! Detectei que houve movimentacao na porta da sala!");
    
    //verificar, caso tenha ocorrido deteccao nos dois sensores, qual dos dois
    //marcou a deteccao primeiro
    if (deteccao_externa.timeOfLastDetection < deteccao_interna.timeOfLastDetection) {
      //caso a deteccao externa tenha ocorrido primeiro, aumentar numero de pessoas dentro
      //da sala
      numPessoas++;

      Serial.println("Verifiquei que uma pessoa entrou na sala!");
      Serial.print("Numero atual de pessoas: ");
      Serial.println(numPessoas);
    } else if (deteccao_externa.timeOfLastDetection > deteccao_interna.timeOfLastDetection) {
      //caso a deteccao interna tenha ocorrido primeiro, diminuir numero de pessoas dentro
      //da sala
      numPessoas--;

      Serial.println("Verifiquei que uma pessoa saiu da sala!");
      Serial.print("Numero atual de pessoas: ");
      Serial.println(numPessoas);
    }

    //resetar estado das deteccoes    
    deteccao_interna.detected = false;
    deteccao_externa.detected = false;
  }

  tempo++;
}
