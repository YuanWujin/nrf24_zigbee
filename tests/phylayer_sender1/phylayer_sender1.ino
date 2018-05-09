#include <NRF24Zigbee.h>
#include "nz_phy_layer.h"

void print_buffer(uint8_t *base, uint16_t length)
{
  for (uint16_t i = 0; i < length; i ++) {
    if (i % 10 == 0 && i != 0)
      debug_printf("\n");
    debug_printf("0x%02X ", base[i]);
  }
  debug_printf("\n");
}

void setup()
{
  Serial.begin(1000000);
  printf_begin();
  printf("Begin config!");
  phy_layer_init("06");
}

int count = 0;
int start = 0;
uint8_t seq_num = 0;
uint8_t failed_times = 0;
uint32_t loop_time = 0;
#define MAX_RETRY_TIME 10

uint32_t last_check_time = 0;

void loop()
{
  if (millis() - last_check_time > 100) {
    #define test_size 111
    uint8_t data[test_size];
    data[0] = seq_num ++;
    for (uint8_t i = 1; i < test_size-1; i++)
      data[i] = random(256);

    data[test_size - 1] = crc_calculate(data, test_size-1);
    pr_info("Call phy_layer_send_raw_data,crc = 0x%02X\n\n", data[test_size-1]);
    phy_layer_send_raw_data("01", data, test_size);
    last_check_time = millis();
  }

  phy_layer_listener();

  uint8_t data_length;
  if ((data_length = phy_layer_fifo_top_node_size()) > 0) {
    uint8_t *data = new uint8_t(data_length);
    data_length = phy_layer_fifo_pop_data(data);
    debug_printf("read_size=%u crc_raw=0x%02X crc_calc=0x%02X \n\n", data_length, data[data_length-1], crc_calculate(data, data_length-1));
    free(data);
  }

}
