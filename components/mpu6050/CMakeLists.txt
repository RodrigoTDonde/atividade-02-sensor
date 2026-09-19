if("${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}" VERSION_GREATER_EQUAL "5.3")
    # Aula 2, pagina 76: a API I2C legada ainda depende de driver.
    set(REQ esp_driver_gpio esp_driver_i2c driver)
else()
    set(REQ driver)
endif()

idf_component_register(
    SRCS "mpu6050.c"
    INCLUDE_DIRS "include"
    REQUIRES ${REQ}
)
