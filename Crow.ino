/*
bateria sao duas 120mAh + 1400mAh pino da bateria é G10 e tem uma correção de 2.0f
tela é de 240px * 135px ST7789

*/
#include "M5Cardputer.h"
#include "bateria.h"
#include "tempo.h"

#define tela M5Cardputer.Display

Bateria bateriaLevel;
Tempo tempo;

unsigned long tempoInicio;
const unsigned long duracaoDelay = 2000;
const unsigned long updateInterval = 1000;

int brilho[] = {50, 65, 80, 100};
int b = 1;

int menuSelecionado = 0;
int menuSelectConfig = 0;

String tituloNome;
unsigned long tempoUltimaAtualizacao = 0;

//indexTela = [menuStart(), menuConfig()]
int indexTela = 0;

// Função para exibir o título
void titulo(String nome) {
  tituloNome = nome;
  tela.fillRect(0, 0, tela.width(), 26, TFT_DARKGREEN);
  tela.setCursor(15, 5);
  tela.setTextColor(WHITE);
  tela.setTextSize(1.75);
  tela.print(tituloNome);
}

// Função para exibir o nível da bateria
void bateriaM5() {
  tela.fillRect(190, 0, 50, 26, TFT_DARKGREEN);
  tela.setCursor(190, 5);
  tela.setTextColor(WHITE);
  tela.setTextSize(1.75);
  tela.print((bateriaLevel.verificador() < 100) ? " " : "");
  tela.print(bateriaLevel.verificador());
  tela.print("%");
}

// Função para exibir a hora
void hourTile() {
  tela.fillRect(100, 0, 90, 26, TFT_DARKGREEN);
  tela.setCursor(100, 5);
  tela.setTextColor(WHITE);
  tela.setTextSize(1.75);

  // Obtendo as horas, minutos e segundos usando a instância da classe Tempo
  uint8_t hours   = tempo.getHours();
  uint8_t minutes = tempo.getMinutes();
  uint8_t seconds = tempo.getSeconds();

  // Imprimindo as horas, minutos e segundos formatados
  tela.print((hours < 10) ? "0" : "");
  tela.print(hours);
  tela.print(":");
  tela.print((minutes < 10) ? "0" : "");
  tela.print(minutes);
  tela.print(":");
  tela.print((seconds < 10) ? "0" : "");
  tela.print(seconds);
}

void brilhoTela(){
  tela.setBrightness(brilho[b]);
  b++;
  if(b > 3){
    b = 0;
  }
}

void menuStart() {
  tela.fillRect(0, 30, tela.width(), 110, TFT_DARKCYAN);

  for (int i = 0; i < 4; i++) {
    int yPosition = 30 + i * 20;

    if (i == menuSelecionado) {
      tela.fillRect(15, yPosition, 120, 23, TFT_DARKCYAN);
      tela.setTextColor(GOLD, TFT_DARKCYAN);
    } else {
      tela.setTextColor(TFT_WHITE);
    }

    tela.setCursor(20, yPosition);

    switch (i) {
      case 0:
        tela.println("Controle IR");
        break;
      case 1:
        tela.println("Tempo");
        break;
      case 2:
        tela.println("Teclado");
        break;
      case 3:
        tela.println("Configuracao");
        break;
    }
  }
}

void menuConfig(){
  tela.fillRect(0, 30, tela.width(), 110, TFT_DARKCYAN);
  for (int i = 0; i < 4; i++) {
    int yPosition = 30 + i * 20;

    if (i == menuSelectConfig) {
      tela.fillRect(15, yPosition, 120, 23, TFT_DARKCYAN);
      tela.setTextColor(GOLD, TFT_DARKCYAN);
    } else {
      tela.setTextColor(TFT_WHITE);
    }

    tela.setCursor(20, yPosition);

    switch (i) {
      case 0:
        tela.print("Hora:   ");
        tela.print((tempo.getHours() < 10) ? "0" : "");
        tela.print(tempo.getHours());
        tela.print(":");
        tela.print((tempo.getMinutes() < 10) ? "0" : "");
        tela.print(tempo.getMinutes());
        break;
      case 1:
        tela.println("Data:   01/02/2024");
        break;
      case 2:
        tela.print("Brilho(0-3):   ");
        tela.println(b+1);
        break;
      case 3:
        tela.println("Tema: padrao");
        break;
    }
  }
}

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);

  tela.setBrightness(50);
  tela.setRotation(1);

  // Cobre a tela toda
  tela.fillScreen(TFT_DARKCYAN);

  // Retângulo de título
  titulo("Home");
  menuStart();
}

void loop() {
  M5Cardputer.update();
  tempo.update();
  unsigned long tempoAtual = millis();

  // Verificando se passou pelo menos 1 segundo desde a última atualização do display
  if (tempoAtual - tempoUltimaAtualizacao >= updateInterval) {
    // Atualizando o display
    bateriaM5();
    hourTile();

    // Atualizando o tempo da última atualização
    tempoUltimaAtualizacao = tempoAtual;
  }

  if(M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)){
    switch (menuSelecionado) {
      case 3 :
        menuConfig();
        indexTela = 1;
        break;
    }
  }

  if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
    if(menuSelecionado == 3){
      indexTela = 0;
      menuStart();
    }
  }

  if (M5Cardputer.Keyboard.isChange()){
    if (M5Cardputer.Keyboard.isPressed()) {
      if (M5Cardputer.Keyboard.isKeyPressed('b')) {
        M5Cardputer.Speaker.tone(4000,50);
        brilhoTela();
      }

      if (M5Cardputer.Keyboard.isKeyPressed('.')) {
        M5Cardputer.Speaker.tone(4000,50);
        switch (indexTela) {
          case 0:
            menuSelecionado++;
            if (menuSelecionado >= 4) {
              menuSelecionado = 0;
            }
            menuStart();
            break;
          case 1:
            menuSelectConfig++;
            if (menuSelectConfig >= 4) {
              menuSelectConfig = 0;
            }
            menuConfig();
            break;
        }

      }

      if (M5Cardputer.Keyboard.isKeyPressed(';')) {
        M5Cardputer.Speaker.tone(4000,50);
        switch (indexTela) {
          case 0:
            menuSelecionado--;
            if (menuSelecionado < 0) {
              menuSelecionado = 3;
            }
            menuStart();
            break;
          case 1:
            menuSelectConfig--;
            if (menuSelectConfig < 0) {
              menuSelectConfig = 3;
            }
            menuConfig();
            break;
        }
      }

      if (M5Cardputer.Keyboard.isKeyPressed('/')) {
        M5Cardputer.Speaker.tone(4000,50);
        if (menuSelectConfig == 2) {
            b++;
            if(b > 3){
              b = 0;
            }
            menuConfig();
            tela.setBrightness(brilho[b]);
        }
      }

      if (M5Cardputer.Keyboard.isKeyPressed(',')) {
        M5Cardputer.Speaker.tone(4000,50);
        if (menuSelectConfig == 2) {
            b--;
            if(b < 0){
              b = 0;
            }
            menuConfig();
            tela.setBrightness(brilho[b]);
        }
      }


    }
  }

}



