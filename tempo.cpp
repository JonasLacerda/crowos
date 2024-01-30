#include "tempo.h"

void Tempo::update() {
  static unsigned long lastSecond = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastSecond >= 1000) {
    lastSecond = currentMillis;

    // Atualiza os segundos apenas a cada segundo
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours >= 24) {
          hours = 0;
        }
      }
    }
  }
}

void Tempo::setSeconds(int newSeconds) {
  seconds = newSeconds;
}

int Tempo::getSeconds() {
  return seconds;
}

void Tempo::setMinutes(int newMinutes) {
  minutes = newMinutes;
}

int Tempo::getMinutes() {
  return minutes;
}

void Tempo::setHours(int newHours) {
  hours = newHours;
}

int Tempo::getHours() {
  return hours;
}

void Tempo::getTime() {
  Serial.print("Hora: ");
  Serial.print(hours % 24); // Limita a exibição às 24 horas
  Serial.print(":");
  Serial.print(minutes % 60);
  Serial.print(":");
  Serial.println(seconds % 60);
}
