# Atividade Avaliativa Prática 2/6 — Leitura de sensor

## Dados para envio

**Repositório:** https://github.com/rodrigodondesenai/atividade-02-sensor

**Screenshot final:** [evidencias/07-final-vscode.png](evidencias/07-final-vscode.png)

**Evidência de inicialização:** [evidencias/08-inicializacao.png](evidencias/08-inicializacao.png)

## Texto para o campo de descrição, se houver

Nesta atividade, usei um ESP32-S3 DevKitC-1 para ler o sensor MPU6050 no
Wokwi. O programa foi escrito em C com ESP-IDF 5.4.2, usando a biblioteca
espressif/mpu6050. As ligações de dados são SDA no GPIO 8 e SCL no GPIO 9.

O programa identifica o sensor, faz sua configuração inicial e mostra a
aceleração em g e a rotação em graus por segundo a cada 500 ms. A compilação
terminou sem erros. No simulador, alterei a aceleração X para 0,5 g e a
rotação Z para 90 graus/s, e o terminal mostrou esses mesmos valores.
O repositório contém o código, o circuito, os registros e as capturas dos testes.

## Conferência antes de concluir o envio

- [x] Repositório com código, circuito e documentação publicados.
- [x] Compilação validada e log preservado.
- [x] Leituras iniciais e alteradas documentadas.
- [x] Screenshot final salvo.
- [x] Captura explícita das mensagens de inicialização.
- [ ] Link e screenshot enviados na plataforma da disciplina.
- [ ] Confirmação de entrega conferida na plataforma.

Este arquivo prepara a entrega; não comprova envio na plataforma.
