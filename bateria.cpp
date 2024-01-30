#include "bateria.h"

int Bateria::verificador() {
  float batteryADCValue = analogRead(G10) * 2.0f;
  float batteryVoltage = (batteryADCValue / 4095.0) * 3300.0; 
  int batteryPercentage = map(batteryVoltage, 3200.0f, 4200.0f, 0, 100);
  batteryPercentage = constrain(batteryPercentage, 0, 100);
  int batteryLevel = batteryPercentage;
  //Serial.println(batteryLevel);
  return batteryLevel;  // Correção: Retorne o valor ao invés de usar "void"
}

Bateria::Bateria() {
  // Implementação do construtor, se necessário
}