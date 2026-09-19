#include <stdbool.h>
#include <stdint.h>
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu6050.h"

static const char *TAG = "SENSOR";
#define SENSOR_PORT I2C_NUM_0
#define SENSOR_SDA GPIO_NUM_8
#define SENSOR_SCL GPIO_NUM_9
#define SENSOR_ADDRESS 0x68
#define EXPECTED_WHO_AM_I 0x68

static bool check_result(esp_err_t result, const char *operation)
{
    if (result == ESP_OK) {
        return true;
    }
    ESP_LOGE(TAG, "%s: %s", operation, esp_err_to_name(result));
    return false;
}

void app_main(void)
{
    const i2c_config_t config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SENSOR_SDA,
        .scl_io_num = SENSOR_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
        .clk_flags = 0,
    };
    ESP_LOGI(TAG, "Atividade 2/6 - ESP32-S3 + MPU6050");
    ESP_LOGI(TAG, "I2C: SDA=8 SCL=9 100 kHz endereco=0x%02X", SENSOR_ADDRESS);
    if (!check_result(i2c_param_config(SENSOR_PORT, &config), "Configurar I2C")) {
        return;
    }
    if (!check_result(i2c_driver_install(SENSOR_PORT, config.mode, 0, 0, 0),
                      "Instalar I2C")) {
        return;
    }
    mpu6050_handle_t sensor = mpu6050_create(SENSOR_PORT, SENSOR_ADDRESS);
    if (sensor == NULL) {
        ESP_LOGE(TAG, "Nao foi possivel criar o sensor");
        check_result(i2c_driver_delete(SENSOR_PORT), "Liberar I2C");
        return;
    }

    uint8_t who_am_i = 0;
    if (!check_result(mpu6050_get_deviceid(sensor, &who_am_i), "Ler WHO_AM_I")) {
        goto cleanup;
    }
    if (who_am_i != EXPECTED_WHO_AM_I) {
        ESP_LOGE(TAG, "WHO_AM_I=0x%02X; esperado=0x%02X", who_am_i, EXPECTED_WHO_AM_I);
        goto cleanup;
    }
    ESP_LOGI(TAG, "WHO_AM_I=0x%02X OK", who_am_i);
    if (!check_result(mpu6050_config(sensor, ACCE_FS_2G, GYRO_FS_250DPS),
                      "Configurar escalas") ||
        !check_result(mpu6050_wake_up(sensor), "Despertar MPU6050")) {
        goto cleanup;
    }
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_LOGI(TAG, "MPU6050 inicializado; escalas +/-2 g e +/-250 graus/s");
    ESP_LOGI(TAG, "Amostragem a cada 500 ms; 1 g = 9.80665 m/s^2");

    while (true) {
        mpu6050_acce_value_t acceleration = {0};
        mpu6050_gyro_value_t gyro = {0};
        const esp_err_t acc_result = mpu6050_get_acce(sensor, &acceleration);
        const esp_err_t gyro_result = mpu6050_get_gyro(sensor, &gyro);
        const bool acc_ok = check_result(acc_result, "Ler aceleracao");
        const bool gyro_ok = check_result(gyro_result, "Ler giroscopio");
        if (acc_ok && gyro_ok) {
            // A biblioteca converte os registradores para g e graus/s.
            ESP_LOGI(TAG, "ACC [g] X=%+.3f Y=%+.3f Z=%+.3f | GYRO [graus/s] X=%+.3f Y=%+.3f Z=%+.3f",
                     acceleration.acce_x, acceleration.acce_y, acceleration.acce_z,
                     gyro.gyro_x, gyro.gyro_y, gyro.gyro_z);
        } else {
            ESP_LOGW(TAG, "Amostra descartada; nova tentativa em 500 ms");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }

cleanup:
    mpu6050_delete(sensor);
    check_result(i2c_driver_delete(SENSOR_PORT), "Liberar I2C");
    ESP_LOGE(TAG, "Inicializacao interrompida. Confira o circuito e reinicie.");
}
