idf_component_register(SRCS "src/string_nvs" "src/softAP.c" "src/packet_gen.c" "pwmfsk.c"  "src/convolutional_encoder.c" "src/reedSolomonEncoder.c"
    INCLUDE_DIRS "include")

spiffs_create_partition_image(www "${CMAKE_CURRENT_SOURCE_DIR}/../frontend" FLASH_IN_PROJECT)
