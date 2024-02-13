# Crow OS
Sistema para M5 Cardputer.
![crowos](https://github.com/JonasLacerda/crowos/assets/65193517/ee262874-0888-4b85-a8d9-d1258c3f7bbb)

Os apps que estou desenvolvendo (tentando fazer funcionar):
- Teclado USB
  - [x] Parcialmente feito, está funcional, mas precisa reiniciar o Carputer para voltar à serial. Só usa o teclado para inserir no dispositivo se estiver com o app de teclado na tela.
  - [x] Melhorei o atalho do brilho, utilizando opt + b para mudar o brilho. Se o app de teclado estiver aberto, ele tecla 'b'... vou corrigir isso quando me perturbar.
- IR
  - [x] Em desenvolvimento. Minha TV é TCL e não encontrei os comandos dela. Isso me implica em montar um Arduino para capturar os inputs do controle IR e depois programar para o Carputer.
  - [ ] custoimizar os controles.
  - [ ] ter opção de configuracao do led ir
- Tempo
  - [x] Parcialmente feito. Criei as funções para definir o tempo correto, e o tempo corre bem favorável. Existe uma diferença de segundos que será corrigida com wifi no futuro.
  - [ ] Quero adicionar no app Tempo a técnica Pomodoro.
  - [ ] Capturar os tempos estilo de corrida. Acho legal um app assim para saber quanto tempo leva cada etapa de um problema ou de uma produção.
  - [ ] Mesmo que eu não tenha paciência para fazer, quero criar um alarme e adicionar uma função de start para que execute um determinado programa em um determinado horário.

Feito isso, vou programar a parte de Wi-Fi e Bluetooth. Só após isso vou iniciar os estudos para adaptar os módulos. Até o momento, o código compilado está usando 20% da memória do ESP32S3.

nota:
 esptool.py --chip esp32s3 merge_bin --output Crow.bin 0x0000 Crow.ino.bootloader.bin 0x8000 Crow.ino.partitions.bin 0x10000 Crow.ino.bin

 esptool.py --port /dev/ttyACM0 write_flash 0x0 Crow.bin
