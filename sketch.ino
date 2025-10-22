#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS A0  // pino do sensor DS18B20

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

class alertaTemperatura {
  int lf, lq, buz;
public:
  alertaTemperatura(int lf_, int lq_, int buz_) {
    lf = lf_;
    lq = lq_;
    buz = buz_;
  }

  void checar(float temp) {
    if (temp > 28) {
      digitalWrite(lf, LOW);
      digitalWrite(lq, HIGH);
      tone(buz, 1000);
    } else {
      digitalWrite(lf, LOW);
      digitalWrite(lq, LOW);
      noTone(buz);
    }
  }
};

// Criando o objeto do alerta
alertaTemperatura alerta(2, 3, 4);

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  sensors.begin();  // inicializa o sensor
}

void loop() {
  sensors.requestTemperatures();  // pede a temperatura ao sensor
  float temp = sensors.getTempCByIndex(0);
  Serial.println(temp);
  alerta.checar(temp);
  delay(1000);
}
