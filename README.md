# Crow OS
Sistema pro M5 Cardputer.
![crowos](https://github.com/JonasLacerda/crowos/assets/65193517/ee262874-0888-4b85-a8d9-d1258c3f7bbb)

os app que estou desenvolvendo (tentando fazer funcionar):
-Teclado usb
  -[x] parcialmente feito, está funcional mais muito mal feito tendo que reiniciar o carputer pra ele voltar a serial, so usa o telcado para inserir no dispositivo se tiver com o app de teclado na tela;
  -[x] melhorei o atalho do brilho tendo que usar opt + b para mudar o blilho, se tiver com o app de teclado aberto ele tecla b... vontade de chorar, corrigir isso tbm é chato (quando isso me pertubar vai ser corrigido);
-IR
  -[] está em desenvolvimento, minha tv é TCL nao achei os comandos dela... ai me implica em moontar um arduino so pra capiturar os inputes do controle ir pra depois programar pro cardputer;
-Tempo
  -[x] parcialmente feito, criei as funçoes para setar o tempo correto,  e o tempo corre bem favoravel... existe sim uma diferença de segundos que no futuro vai ser corrigido com wifi
  -[] quero colocar dentro do app tempo o pomodoro
  -[] capiturar os tempos estilo de corrida acho legal um app assim pra saber quanto tempo leva cada etapa de um problema ou de uma producao
  -[] mesmo que nao tenho saco pra fazer quero fazer um alarme e acresentar uma funçao de start para que se executa um determinado programa em um determinado horario.

Feito isso vou programar a parte de wifi e bluetooth.
e so apos isso vou iniciar os estudos para adapitar os modulos.
ate o momento o codigo compulilado esta usando 20% da memoria do esp32s3.
