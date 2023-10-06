// C++ code
//
const int pinoVermelhoTransito = 2;
const int pinoAmareloTransito = 3;
const int pinoVerdeTransito = 4;
const int pinoVermelhoPedestre = 5;
const int pinoVerdePedestre = 6;
const int pinoBotaoPedestre1 = 7;
const int pinoBotaoPedestre2 = 8;
const int pinoTrigSonar = 9;
const int pinoEchoSonar = 10;
const int pinoLEDMulta = 11;

long tempoAnterior = 0;
long intervalo = 15000;  
long tempoTravessiaPedestre = 5000;  
bool travessiaPedestreAtiva = false;

void setup() {
  pinMode(pinoVermelhoTransito, OUTPUT);
  pinMode(pinoAmareloTransito, OUTPUT);
  pinMode(pinoVerdeTransito, OUTPUT);
  pinMode(pinoVermelhoPedestre, OUTPUT);
  pinMode(pinoVerdePedestre, OUTPUT);
  pinMode(pinoBotaoPedestre1, INPUT_PULLUP);
  pinMode(pinoBotaoPedestre2, INPUT_PULLUP);
  pinMode(pinoLEDMulta, OUTPUT);
  pinMode(pinoTrigSonar, OUTPUT);
  pinMode(pinoEchoSonar, INPUT);

  semaforoTransito();
}

void loop() {
  if (carroDetectado()) {
    digitalWrite(pinoLEDMulta, HIGH);
    delay(1000);  
    digitalWrite(pinoLEDMulta, LOW);
  }

  if (digitalRead(pinoBotaoPedestre1) == LOW || digitalRead(pinoBotaoPedestre2) == LOW) {
    travessiaPedestreAtiva = true;
    semaforoPedestre();
    delay(tempoTravessiaPedestre); 
    travessiaPedestreAtiva = false;
  }

  unsigned long tempoAtual = millis();
  if (!travessiaPedestreAtiva && tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;
    semaforoTransito();
  }
}

void semaforoTransito() {
  digitalWrite(pinoVermelhoPedestre, HIGH);
  digitalWrite(pinoVerdeTransito, HIGH);
  delay(2000);  
  digitalWrite(pinoVerdeTransito, LOW);
  digitalWrite(pinoAmareloTransito, HIGH);
  delay(2000);  
  digitalWrite(pinoVermelhoTransito, HIGH);
  digitalWrite(pinoAmareloTransito, LOW);
}

void semaforoPedestre() {
  digitalWrite(pinoVerdeTransito, LOW);
  digitalWrite(pinoAmareloTransito, LOW);
  digitalWrite(pinoVermelhoTransito, LOW);
  digitalWrite(pinoVerdePedestre, HIGH);
  delay(2000);  
  digitalWrite(pinoVerdePedestre, LOW);
  digitalWrite(pinoVermelhoPedestre, LOW);
  delay(500);  
  digitalWrite(pinoVermelhoPedestre, HIGH);
  delay(500);  
}
 
bool carroDetectado() {
  digitalWrite(pinoTrigSonar, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrigSonar, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrigSonar, LOW);

  long duracao = pulseIn(pinoEchoSonar, HIGH);
  return duracao < 1000;  
}
