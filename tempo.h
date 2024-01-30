#ifndef TEMPO_H
#define TEMPO_H

#include <M5Cardputer.h>

extern M5Canvas sub_title2;

class Tempo {
public:
  void begin();
  void update();
  void setSeconds(int newSeconds);
  int getSeconds();
  void setMinutes(int newMinutes);
  int getMinutes();
  void setHours(int newHours);
  int getHours();
  void getTime();

private:
  int seconds;
  int minutes;
  int hours;
};

#endif
