# Atividade Avaliativa Prática 2/6 — Leitura de sensor

ESP32-S3 DevKitC-1 + MPU6050 no Wokwi, usando C e ESP-IDF 5.4.2.
O programa confere `WHO_AM_I == 0x68`, configura ±2 g e ±250 graus/s,
desperta o sensor e imprime os seis eixos a cada 500 ms com `ESP_LOGI`.
`vTaskDelay()` libera o processador entre as amostras.

Compilação local concluída sem erros em 19/09/2026; registro em
`evidencias/build.log`. Repositório de entrega:
https://github.com/rodrigodondesenai/atividade-02-sensor

## Circuito

| ESP32-S3 | MPU6050 | Função |
| --- | --- | --- |
| 3V3 | VCC | Alimentação |
| GND | GND | Referência comum |
| GPIO 8 | SDA | Dados I2C |
| GPIO 9 | SCL | Clock I2C, 100 kHz |
| GND | AD0 | Endereço 0x68 |

INT, XDA e XCL não são usados. O firmware habilita pull-ups internos.
O circuito está em `diagram.json`.

## Biblioteca e compatibilidade

A biblioteca oficial `espressif/mpu6050` 1.2.1 está incluída em
`components/mpu6050`, com licença e procedência em `ORIGEM.md`.
A dependência `driver` foi acrescentada no CMake para ESP-IDF >= 5.3,
conforme a página 76 da Aula 2. A correção acompanha o Git.
As funções da biblioteca retornam aceleração em **g** e giro em **graus/s**;
1 g corresponde a 9,80665 m/s².

## Compilar neste computador

1. Abra esta pasta no VS Code.
2. Pressione **Ctrl+Shift+B** e execute **Atividade 02: compilar ESP-IDF**.
3. Espere a mensagem `Project build complete`.

Alternativa pelo terminal PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File scripts/build.ps1
```

O script lê o registro local `.tools/eim_idf.json`, configura a sessão e
salva a saída em `evidencias/build.log`. SDK, ferramentas e caches não entram
no Git. Há uma cópia corrigida do compilador em `.tools/toolchain`, pois a
extração inicial feita pelo EIM 0.19.0 deixou arquivos vazios no lugar de
diretórios. O ZIP foi conferido pelo SHA256 publicado em `tools/tools.json`.

Em outro computador com ESP-IDF 5.4.2 configurado, use seu terminal ESP-IDF:

```text
idf.py set-target esp32s3
idf.py build
```

## Licença Wokwi e simulação

1. Pressione **F1 → Wokwi: Request a New License**.
2. Autorize abrir o navegador, entre na conta e clique **GET YOUR LICENSE**.
3. Autorize voltar ao VS Code e confirme `License activated`.
4. Após compilar, pressione **F1 → Wokwi: Start Simulator**.
5. Confira `WHO_AM_I=0x68 OK` e `MPU6050 inicializado` no monitor serial.
6. Clique no MPU6050 e altere seus controles de aceleração e rotação.

O `wokwi.toml` carrega `build/flasher_args.json` (aplicação, bootloader e
tabela de partições) e `build/atividade_02_sensor.elf`.
Também permite capturar a serial pela porta local 4000. Com o simulador
visível, execute `scripts/capture-serial.py` usando o Python do ESP-IDF
(com `pyserial` instalado) para acrescentar 30 segundos a `evidencias/serial.log`.

## Roteiro de validação e evidências

Valores abaixo são **resultados esperados**, não medições já realizadas.

| Etapa | Ação | Resultado esperado |
| --- | --- | --- |
| Inicial | Iniciar com os atributos do diagrama | ACC ≈ (0, 0, 1) g; GYRO ≈ (0, 0, 0) graus/s |
| Aceleração | Ajustar X para 0,5 g e Y para -0,5 g | X ≈ +0,500; Y ≈ -0,500 |
| Giroscópio | Ajustar Z para 90 graus/s | GYRO Z ≈ +90,000 |
| Retorno | Restaurar os controles | Leituras voltam aos valores iniciais |
| Erro I2C | Parar, desconectar SDA e reiniciar | Log de erro; não confirmar inicialização |

Após o teste de erro, restaure SDA no GPIO 8 e reinicie. Em falhas de leitura,
o programa descarta a amostra e tenta novamente após 500 ms. Falhas na
inicialização encerram `app_main` com diagnóstico, sem imprimir dados falsos.

Guarde em `evidencias/`:

- `01-extensoes.png`: extensões ESP-IDF e Wokwi.
- `02-sdk.png`: versão do SDK/compilação no VS Code.
- `03-wokwi-ativo.png`: confirmação da licença, sem expor a chave.
- `04-circuito.png`: placa, sensor e ligações.
- `05-leitura-inicial.png`: identidade e leituras iniciais.
- `06-leitura-alterada.png`: controles alterados e resposta serial.
- `07-final-vscode.png`: VS Code com circuito, código e leituras visíveis.
- `build.log`: registro real da compilação.

No Windows, use **Win+Shift+S** e salve a captura na pasta `evidencias`.
A entrega exige o link do repositório Git e o screenshot final no VS Code.
Consulte `evidencias/STATUS.md` para separar verificações concluídas de pendências.

## Referências

- Aula 2 fornecida pelo curso: páginas 19–42 e 68–82.
- https://docs.wokwi.com/vscode/getting-started
- https://docs.wokwi.com/vscode/project-config
- https://docs.wokwi.com/parts/wokwi-mpu6050
- https://components.espressif.com/components/espressif/mpu6050/versions/1.2.1
