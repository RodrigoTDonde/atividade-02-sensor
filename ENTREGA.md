# Atividade Avaliativa Prática 2/6 — Leitura de sensor

## Dados para envio

**Repositório:** https://github.com/rodrigodondesenai/atividade-02-sensor

**Screenshot final:** [evidencias/07-final-vscode.png](evidencias/07-final-vscode.png)

## Texto para o campo de descrição, se houver

Projeto em C com ESP-IDF 5.4.2, ESP32-S3 DevKitC-1 e MPU6050 no Wokwi.
Comunicação I2C com SDA no GPIO 8 e SCL no GPIO 9, usando a biblioteca
espressif/mpu6050. O firmware verifica WHO_AM_I, inicializa o sensor e
imprime aceleração em g e giroscópio em graus/s a cada 500 ms.
Compilação concluída sem erros. A simulação confirmou a resposta às
alterações dos controles: aceleração X de 0 para 0,5 g e rotação Z de
0 para 90 graus/s. Código, circuito, logs e capturas estão no repositório.

## Conferência antes de concluir o envio

- [x] Repositório com código, circuito e documentação publicados.
- [x] Compilação validada e log preservado.
- [x] Leituras iniciais e alteradas documentadas.
- [x] Screenshot final salvo.
- [ ] Captura explícita das mensagens de inicialização.
- [ ] Link e screenshot enviados na plataforma da disciplina.
- [ ] Confirmação de entrega conferida na plataforma.

Este arquivo prepara a entrega; não comprova envio na plataforma.
