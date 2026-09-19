# Origem e ajuste local

Componente oficial **espressif/mpu6050 1.2.1**, distribuído sob Apache-2.0
(ver `license.txt`). Fontes originais preservadas; apenas `CMakeLists.txt`
recebeu a dependência `driver` no ramo ESP-IDF >= 5.3.

- Registro: https://components.espressif.com/components/espressif/mpu6050/versions/1.2.1
- Commit upstream: `604890dd0abbf11f5d77461bc864dcfb153b0b45`
- Diretório upstream: `components/mpu6050` em `espressif/esp-bsp`.
- SHA256 do ZIP original: `65f65efea437b8eb96340c9c75163f6218fcc28d2737425f27dc164da594fca6`.

O header público inclui `driver/i2c.h`, da API legada. No ESP-IDF 5.4.2
essa API requer o componente `driver`, além dos componentes de GPIO/I2C
declarados originalmente. É o ajuste descrito na página 76 da Aula 2.

O componente está versionado em `components/mpu6050`, em vez de editar
`managed_components` após cada download. Assim, um clone recebe exatamente
a versão e a correção utilizadas, sem depender de alterações manuais no cache.

Diff funcional:

```diff
-    set(REQ esp_driver_gpio esp_driver_i2c)
+    set(REQ esp_driver_gpio esp_driver_i2c driver)
```
