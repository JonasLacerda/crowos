#include "ir.h"

#define IR_TX_PIN 44
#define SD_SPI_CS_PIN 12

void Ir::beginir() {
  IrSender.begin(DISABLE_LED_FEEDBACK);  // Start with IR_SEND_PIN as send pin
  IrSender.setSendPin(IR_TX_PIN);
}

void Ir::setFrequencia(int newFrequencia) {
  frequencia = newFrequencia;
}

void Ir::setPulsoMarcacao(int newPulsoMarcacao) {
  pulso_marcacao = newPulsoMarcacao;
}

void Ir::setIntervaloMarcacao(int newIntervaloMarcacao) {
  intervalo_marcacao = newIntervaloMarcacao;
}

void Ir::setPulsoEspaco(int newPulsoEspaco) {
  pulso_espaco = newPulsoEspaco;
}

void Ir::setIntervaloEspaco(int newIntervaloEspaco) {
  intervalo_espaco = newIntervaloEspaco;
}

void Ir::setPulsoInicio(int newPulsoInicio) {
  pulso_inicio = newPulsoInicio;
}

void Ir::setIntervaloInicio(int newIntervaloInicio) {
  intervalo_inicio = newIntervaloInicio;
}

/*
    "tvtcl": {
      "protocol": "custom",
      "config": {
        "frequencia": 38,
        "pulso_marcacao": 4050,
        "intervalo_marcacao": 3950,
        "pulso_espaco": 550,
        "intervalo_espaco": 2000,
        "pulso_inicio": 550,
        "intervalo_inicio": 1000,
        "tt": 24
      },
      "comand": {
        "P": ["p", "0xAB054F"],
        "H":  ["h", "0xEF010F"],
        "esc":  ["`", "0x1B0E4F"],
        "menu":  ["m", "0xB34CFE01"],
        "^":    [";", "0x6509AF"],
        "":  [".", "0xE501AF"],
        "<":  [",", "0x9506AF"],
        ">": ["/", "0x150EAF"],
        "ok":    ["ok", "0xD002FF"],
        "vol+":  ["f", "0xB0F4F"],
        "vol-":  ["c", "0x8B074F"],
        "ch+":   ["d", "0x4B0B4F"],
        "ch-":   ["x", "0xCB034F"],
        "...": ["i", "0x3A0C5F"],
        "ent": ["o", ""]
      }
    },
*/

void Ir::nomeBotao(int botao) {
  File jsonFile =SD.open("irComand.json");
  
  if (!jsonFile) {
    Serial.println("Erro ao abrir o arquivo JSON!");
    return;
  }

  DeserializationError error = deserializeJson(doc, jsonFile);
  if (error) {
    Serial.print("Falha ao ler o JSON: ");
    Serial.println(error.f_str());
    return;
  }

  // Acessa o objeto "tvtcl" do JSON primeiro objeto
  JsonObject botoes = doc[botao];

  // Verifica se o objeto foi encontrado
  if (!botoes.isNull()) {
    Serial.println("Botão não encontrado no JSON.");
    jsonFile.close();
    return;
  }
  
  // Acessa o objeto "comand" dentro de "tvtcl"
  JsonObject comand = botoes["comand"];
  
  // Variável de contador para o array de botões
  i = 0;
  // Limpa o array nomesBotoes
  //std::fill(std::begin(nomesBotoes), std::end(nomesBotoes), "");
  for (int j = 0; j < numBotoes; j++) {
    nomesBotoes[j] = "";
  }

  // Itera sobre as chaves do objeto "comand" e armazena no array nomesBotoes
  
  for (JsonPair p : comand) {
    if (i < numBotoes) {
      nomesBotoes[i] = p.key().c_str();  // Armazena o nome do botão
      i++;
    }
  }

  // Fecha o arquivo JSON
  jsonFile.close();
  
  // Exibe os nomes dos botões para verificação
  for (int j = 0; j < i; j++) {
    Serial.println(nomesBotoes[j]);
    //retornar o arrey com o nome dos botoes
  }
}

std::vector<String> Ir::getNomesBotoes(int b) {
  nomeBotao(b);  // Chama a função para preencher o array de botões

  std::vector<String> botoes;  // Usando vector para retornar os botões

  // Adiciona os nomes ao vector
  for (int i = 0; i < numBotoes; i++) {
    if (nomesBotoes[i] != "") {  // Verifica se o nome do botão não está vazio
      botoes.push_back(nomesBotoes[i]);
    }
  }

  return botoes;  // Retorna o vector com os nomes dos botões
}
