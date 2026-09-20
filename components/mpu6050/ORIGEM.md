# Origem e ajuste local

Componente oficial **espressif/mpu6050 1.2.1**, distribuído sob Apache-2.0
(ver `license.txt`). Fontes originais preservadas; apenas `CMakeLists.txt`
recebeu a dependência `driver` no ramo ESP-IDF >= 5.3.

- Registro: https://components.espressif.com/components/espressif/mpu6050/versions/1.2.1
- Identificação da versão original (commit): `604890dd0abbf11f5d77461bc864dcfb153b0b45`
- Pasta original: `components/mpu6050` em `espressif/esp-bsp`.
- SHA256 do ZIP original: `65f65efea437b8eb96340c9c75163f6218fcc28d2737425f27dc164da594fca6`.

O arquivo de declarações da biblioteca inclui `driver/i2c.h`, que pertence
à interface I2C antiga. Para compilar com ESP-IDF 5.4.2, a biblioteca precisa
declarar também a dependência `driver`. É o ajuste da página 76 da Aula 2.

A biblioteca e a correção estão salvas no Git, na pasta `components/mpu6050`.
Assim, quem baixar o projeto recebe os mesmos arquivos e não precisa
repetir a correção manualmente depois de baixar a biblioteca.

Alteração feita:

```diff
-    set(REQ esp_driver_gpio esp_driver_i2c)
+    set(REQ esp_driver_gpio esp_driver_i2c driver)
```
