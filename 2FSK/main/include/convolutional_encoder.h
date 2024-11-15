#include <stdint.h>
uint32_t encode_and_spread (uint8_t input);
uint64_t encode_and_spread_twice(uint8_t input);
void reset();
uint8_t whiten();
void generate_pseudo_random_payload();
void fill_buffer_in_long_range_mode_1(uint32_t* buffer, uint8_t* payload,uint8_t payload_size,uint16_t sequence_number);
void reset_pseudo_random_register();