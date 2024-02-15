/*
bateria sao duas 120mAh + 1400mAh pino da bateria é G10 e tem uma correção de 2.0f
tela é de 240px * 135px ST7789

*/

#include "PT_BR.h"
//#include "EN_US.h"
#include "M5Cardputer.h"
#include <IRremote.hpp>
#include <M5GFX.h>


#include "bateria.h"
#include "tempo.h"

#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#define tela M5Cardputer.Display

#define DISABLE_CODE_FOR_RECEIVER
#define IR_TX_PIN 44

M5Canvas dataConfig(&M5Cardputer.Display);

//13
LGFX_Button btnIr[15];

Bateria bateriaLevel;
Tempo tempo;

unsigned long tempoInicio;
const unsigned long duracaoDelay = 2000;
const unsigned long updateInterval = 1000;

int brilho[] = {0, 50, 65, 80, 100};
int b = 2;

//escrever numero
int dataC;

int menuSelecionado = 0;
int menuSelectConfig = 0;

String tituloNome;
unsigned long tempoUltimaAtualizacao = 0;

String texto;

//indexTela = [menuStart(), menuConfig(), appTeclado(), appIR()]
int indexTela = 0;

// Função para exibir o título 8 caracter
void titulo(String nome) {
  tituloNome = nome.substring(0, 8);
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
  if(b > 4){
    b = 0;
  }
}

void menuStart() {
  tela.fillRect(0, 30, tela.width(), 110, TFT_DARKCYAN);
  titulo("Home");

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
        tela.println(menu_IR);
        break;
      case 1:
        tela.println(menu_tempo);
        break;
      case 2:
        tela.println(menu_teclado);
        break;
      case 3:
        tela.println(menu_configuracao);
        break;
    }
  }
}

void menuConfig(){
  tela.fillRect(0, 30, tela.width(), 110, TFT_DARKCYAN);
  titulo("Config");

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
        tela.print(tempo_hora ":   ");
        tela.print((tempo.getHours() < 10) ? "0" : "");
        tela.print(tempo.getHours());
        tela.print(":");
        tela.print((tempo.getMinutes() < 10) ? "0" : "");
        tela.print(tempo.getMinutes());
        break;
      case 1:
        tela.print(tempo_data ":   ");
        tela.print("01");
        tela.print("/");
        tela.print("02");
        tela.print("/");
        tela.println("24");
        break;
      case 2:
        tela.print(tempo_brilho "(0-3):   ");
        tela.println(b+1);
        break;
      case 3:
        tela.println(config_tema ": " config_tema_padrao );
        break;
    }
  }
}

void appTeclado(){
  if(indexTela !=2){
    indexTela = 2;
  }else {
    Keyboard.begin();
    USB.begin();
  }
  tela.fillRect(0, 30, tela.width(), 110, TFT_DARKCYAN);
  titulo(menu_teclado);
  tela.setCursor(15, 50);
  tela.setTextScroll(true);
  tela.println(texto);
}

void appIR() {
    IrSender.begin(DISABLE_LED_FEEDBACK);  // Start with IR_SEND_PIN as send pin
    IrSender.setSendPin(IR_TX_PIN);

    tela.fillRect(0, 30, tela.width(), 110, TFT_DARKCYAN);
    titulo("IR");
    tela.setCursor(15, 50);
    tela.setTextScroll(true);
    tela.drawString("TCL", 15, 35);
    tela.setTextColor(TFT_SILVER, TFT_BLACK);
    int numLinhas = 3;
    int numColunas = 5;
    int larguraBotao = 30;
    int alturaBotao = 25;
    int espacamentoHorizontal = 5;
    int espacamentoVertical = 5;

    // Nomes dos botões
    String nomesBotoes[15] = {
        "P", "^", "H", "ch+", "vol+",
        "<", "ok", ">", "ch-", "vol-",
        "conf", "", "esc", "...", "ent"
    };

    // Inicialize e desenhe os botões
    for (int i = 0; i < 15; ++i) {
        int linha = i / numColunas;
        int coluna = i % numColunas;
        int x = espacamentoHorizontal + coluna * (larguraBotao + espacamentoHorizontal) + 75;
        int y = 50 + linha * (alturaBotao + espacamentoVertical);

        btnIr[i].initButton(&M5.Lcd, x, y, larguraBotao, alturaBotao, TFT_DARKGREEN, TFT_YELLOW, TFT_DARKGREEN, nomesBotoes[i].c_str());
        btnIr[i].drawButton();
    }
}

void sendIRSignal(char letter) {
    // Configurações específicas de sinal IR para cada letra usando switch case
    switch (letter) {
        case 'p':
          IrSender.sendPulseDistanceWidth(38, 4050, 3950, 550, 2000, 550, 1000, 0xAB054F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
          break;
        case ';':
          IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0x6509AF, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
          break;
        case 'h':
          IrSender.sendPulseDistanceWidth(38, 4100, 3950, 550, 2000, 550, 1000, 0xEF010F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
          break;
        case '\'':
            // Adicione configurações para o caractere "'" conforme necessário
            break;
        case 'd':
            IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0x4B0B4F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
            break;
        case 'f':
          IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0xB0F4F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
          break;
        case ',':
            IrSender.sendPulseDistanceWidth(38, 4100, 3950, 550, 2000, 550, 1000, 0x9506AF, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
            break;
        case 'l':
            
            break;
        case '/':
            IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0x150EAF, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
            break;
        case 'x':
          IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0xCB034F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
          break;
        case 'c':
            IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0x8B074F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
            break;
        case '1':
            // Adicione configurações para o caractere "1" conforme necessário
            break;
        case '.':
            IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0xE501AF, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
            break;
        case '`':
            IrSender.sendPulseDistanceWidth(38, 4100, 3950, 550, 2000, 550, 1000, 0x1B0E4F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
            break;
        case 'i':
            // Adicione configurações para o caractere "i" conforme necessário
            break;
        case 'o':
            IrSender.sendPulseDistanceWidth(38, 4100, 3950, 550, 2000, 550, 1000, 0x3A0C5F, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
            break;
        default:
            break;
    }
}

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  Serial.begin(115200);

  tela.setBrightness(50);
  tela.setRotation(1);

  // Cobre a tela toda
  tela.fillScreen(TFT_DARKCYAN);
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
      case 0 :
        if(indexTela != 3){
          indexTela = 3;
          appIR();
          delay(60);
        }else{
          IrSender.sendPulseDistanceWidth(38, 4050, 4000, 550, 2000, 550, 1000, 0xD002FF, 24, PROTOCOL_IS_LSB_FIRST, 0, 0);
          btnIr[6].press(true);
          btnIr[6].drawButton(true);
        }
        break;
      case 2 :
        if(indexTela != 2){
          appTeclado();
        }
        break;
      case 3 :
        if(indexTela != 1){
          menuConfig();
          indexTela = 1;
        }
        break;
    }
  }

  if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
    switch (menuSelecionado) {
      case 3 :
        if(indexTela != 0){
          indexTela = 0;
          menuStart();
        }
        break;
    }
  }

  if(M5Cardputer.BtnA.wasPressed()){
    if(indexTela != 0){
      indexTela = 0;
      menuStart();
    }
  }

  if (M5Cardputer.Keyboard.isChange()){
    if (M5Cardputer.Keyboard.isPressed()) {
      Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

      if (indexTela == 2){
        //envio do que digitar por usb
        KeyReport report = {0};
        report.modifiers = status.modifiers;
        uint8_t index    = 0;
        for (auto i : status.hid_keys) {
            report.keys[index] = i;
            index++;
            if (index > 5) {
                index = 5;
            }
        }

        Keyboard.sendReport(&report);
        Keyboard.releaseAll();

        for (auto i : status.word) {
          texto += i;
          Serial.println(texto);
          if(indexTela == 2){
            appTeclado();
          }
        }

        if (status.del) {
            texto.remove(texto.length() - 1);
            Serial.println(texto);
            if(indexTela == 2){
              appTeclado();
            }
        }

        if (status.enter) {
            texto.remove(0, 2);
            texto = "";
            appTeclado();
        }

        //fim do codigo pra enviar por usb
      }

      if (M5Cardputer.Keyboard.isKeyPressed(KEY_OPT)){
        if (M5Cardputer.Keyboard.isKeyPressed('b')) {
          M5Cardputer.Speaker.tone(4000,50);
          brilhoTela();
        }
      }

      if (M5Cardputer.Keyboard.isKeyPressed('.')) {
        //M5Cardputer.Speaker.tone(4000,50);
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
        //M5Cardputer.Speaker.tone(4000,50);
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
        //M5Cardputer.Speaker.tone(4000,50);
        switch (menuSelectConfig) {
          case 1 :
            tela.fillRect(95, 50, 103, 16, TFT_DARKCYAN);
            break;

          case 2 :
            b++;
            if(b > 4){
              b = 0;
            }
            menuConfig();
            tela.setBrightness(brilho[b]);
            break;
        }
      }

      if (M5Cardputer.Keyboard.isKeyPressed(',')) {
        //M5Cardputer.Speaker.tone(4000,50);
        switch (menuSelectConfig) {
          case 1 :
            tela.fillRect(95, 50, 103, 16, TFT_DARKCYAN);
            break;

          case 2 :
            b--;
            if(b < 0){
              b = 4;
            }
            menuConfig();
            tela.setBrightness(brilho[b]);
            break;
        }
      }
    }

    if(indexTela == 3){
      if (M5Cardputer.Keyboard.isPressed()) {
      Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
      switch (menuSelecionado){
        case 0 :
          for (auto key : status.word) {
            if (indexTela == 3) {
                Serial.println(key);
                // Mapeamento de letras para índices de botões
                String letters[] = {"p", ";", "h", "d", "f",
                                    ",", "", "/", "x", "c",
                                    "1", ".", "`", "i", "o"};
                for (int j = 0; j < 15; ++j) {
                    // Convertendo char para String antes de comparar
                    if (String(key) == letters[j]) { 
                        btnIr[j].press(true);
                        btnIr[j].drawButton(true);
                        sendIRSignal(key);
                    }
                }
            }
          }
          break;
      } 
      }else {
        switch (menuSelecionado){
          case 0 :
            // Desativa todos os botões
            for (int j = 0; j < 15; ++j) {
                btnIr[j].press(false);
                btnIr[j].drawButton(false);
            }
            break;   
        }
      }

    }
    
    delay(30);
  }
}














