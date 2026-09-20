# Registro de execução — atualizado em 20/09/2026

## Confirmado

- Pasta: `C:\Users\rodrigo.donde\Documents\IA EMBARCADA\atividade-02-sensor`.
- Extensão ESP-IDF: **2.2.0** (a versão 1.10.2 informada anteriormente já havia mudado).
- Extensão Wokwi: **3.7.0**.
- EIM CLI: **0.19.0**.
- ESP-IDF instalado: **5.4.2**, commit `f5c3654a1c2d2a01f7f67def7a0dc48e691f63c0`.
- Licença Wokwi: usuário confirmou a mensagem **License activated**.
- Biblioteca: **espressif/mpu6050 1.2.1**, com correção reproduzível de `driver`.
- Repositório indicado: https://github.com/rodrigodondesenai/atividade-02-sensor
- Consulta inicial ao remoto: vazio, sem referências Git.
- Compilação concluída com código de saída **0** e `Project build complete`.
- Firmware: **230400 bytes** (`0x38400`); partição de aplicação com 78% livres.
- Bootloader: **20928 bytes** (`0x51c0`).
- Log real da compilação: `evidencias/build.log`.
- Diagrama JSON válido; biblioteca original comparada com a cópia local:
  única alteração funcional em `CMakeLists.txt`.
- Execução no Wokwi confirmada: captura serial real em `serial.log`,
  com ACC (0, 0, 1) g e GYRO (0, 0, 0) graus/s, em intervalos de 500 ms.
- Capturas fornecidas pelo usuário em 20/09/2026, copiadas sem edição:
  - `04-circuito-leitura-inicial.png`: circuito, licença e leituras iniciais.
  - `05-controles-iniciais.png`: controles em (0, 0, 1) g e giro nulo.
  - `06-leitura-alterada.png`: controle X = 0,5 g e rotação Z = 90 graus/s;
    serial confirma ACC X = +0,500 g e GYRO Z = +90,000 graus/s.
  - `07-final-vscode.png`: captura final fornecida como `simulador4.png`,
    mostrando o painel Wokwi no VS Code, circuito, licença ativa e leituras
    alteradas, com os controles do sensor fechados. É um recorte dos painéis,
    sem o Explorer do projeto; não é uma captura da janela inteira.
  - `08-inicializacao.png`: captura fornecida como `simulador5.png`, com
    `WHO_AM_I=0x68 OK`, `MPU6050 inicializado`, SDA=8, SCL=9, endereço 0x68,
    escalas de +/-2 g e +/-250 graus/s e leituras alteradas.
- Inicialização e resposta à alteração dos valores confirmadas pelas capturas.
  O aviso do SDK sobre o driver I2C legado está visível; a execução prossegue
  com inicialização e leituras corretas usando a biblioteca prevista na atividade.

## Checagem final

A revisão confirmou os quatro critérios informados para a atividade:
ambiente configurado, circuito correto, compilação sem erros e leituras
corretas. O README apresenta os critérios com seus respectivos pesos.

O comando de compilação foi executado novamente e terminou com código 0
e a mensagem `Project build complete`. O resultado está em
`revisao-final-build.log`; o log da primeira compilação foi preservado.
Essa checagem foi incremental: aproveitou os arquivos já compilados.
O resumo das verificações está em [revisao-final.txt](revisao-final.txt).

Foram revisados o código C, as ligações do diagrama, as configurações de
compilação e simulação, os scripts de apoio e as capturas fornecidas.
As leituras no simulador são comprovadas pelas capturas anteriores;
a revisão final não representa uma nova execução no Wokwi.

## Ajustes feitos durante a instalação

O SDK foi instalado em `.tools/espressif/v5.4.2/esp-idf`. Embora o caminho
base tivesse sido informado dentro do projeto, o EIM usou seus padrões
absolutos `C:\Espressif\tools` e `C:\Espressif\dist` para as ferramentas e
downloads, e informou criação de atalho no Desktop. Essa ocorrência foi
comunicada ao usuário; não se declara que toda a instalação ficou no projeto.
Não foram removidos arquivos externos.

A instalação inicial deixou incompleta uma pasta do compilador, chamada
`libexec`. Por isso, apareceu o erro `cannot execute cc1`. A integridade do
pacote baixado foi conferida pelo código SHA256
`62ae704777d73c30689efff6e81178632a1ca44d1a2d60f4621eb997e040e028`
e ele foi extraído corretamente para `.tools/toolchain`.

O nome da pasta do projeto contém espaços. Isso fez as ferramentas
abreviarem o nome do compilador e causou outro erro. Os arquivos em
`scripts/` ajustam esse caminho para permitir a compilação. O projeto
permaneceu na mesma pasta.

Alguns arquivos extraídos tinham datas futuras, o que fazia a configuração
se repetir. As datas desses arquivos foram corrigidas.

## Ainda pendente

- Enviar o link do repositório e o screenshot final no ambiente da disciplina.

Capturas adicionais das extensões e da compilação complementam os logs já
guardados. Os testes de retorno, eixo Y negativo e desconexão I2C do roteiro
não foram documentados como executados; são verificações complementares.
