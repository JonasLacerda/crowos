#ifndef IR_H
#define IR_H

#include <IRremote.hpp>
#include <ArduinoJson.h>
#include <SD.h> 

class Ir {
  public:
    void beginir();
    void setFrequencia(int newFrequencia);
    void setPulsoMarcacao(int newPulsoMarcacao);
    void setIntervaloMarcacao(int newIntervaloMarcacao);
    void setPulsoEspaco(int newPulsoEspaco);
    void setIntervaloEspaco(int newIntervaloEspaco);
    void setPulsoInicio(int newPulsoInicio);
    void setIntervaloInicio(int newIntervaloInicio);
    std::vector<String> getNomesBotoes(int b);

  private:
    static const int numBotoes = 15;
    String nomesBotoes[numBotoes];
    StaticJsonDocument<1024> doc;
    void nomeBotao(int botao);

    int botao;
    int i;
    int count;
    int frequencia; //30
    int pulso_marcacao; // 4050
    int intervalo_marcacao; // 3950
    int pulso_espaco; //550
    int intervalo_espaco; // 2000
    int pulso_inicio; //550
    int intervalo_inicio; // 1000
};

#endif