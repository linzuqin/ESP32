idf_component_register(
    SRCS "ALILOT_OTA.c"
    INCLUDE_DIRS    "."
    REQUIRES    esp_https_ota   esp_partition   mbedtls
)