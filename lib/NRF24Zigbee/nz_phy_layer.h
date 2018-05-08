#ifndef NZ_PHY_LAYER_H
#define NZ_PHY_LAYER_H
#include "NRF24Zigbee.h"

#define CE_PIN 8
#define CSN_PIN 9
#define CHANNEL 100
#define PAYLOAD_LENGTH 32
#define RETRY_TIMES 5
#define RETRY_DURTION 1250
#define SOFTWARE_RETRY_RATIO 10

bool phy_layer_init(uint8_t *src_addr);
bool phy_layer_data_ready(void);
void phy_packet_trace(phy_packet_handle * packet, uint8_t mode);
void phy_layer_reset_node(rx_node_handle *node);
bool phy_layer_send_slice_packet(phy_packet_handle * packet, uint32_t max_retry);
void phy_layer_listener(void);
uint16_t phy_layer_fifo_endpoint_size(void);
uint16_t phy_layer_fifo_pop_data(uint8_t *data, uint16_t max_length);
void phy_layer_set_src_addr(uint8_t src_addr[2]);
void phy_layer_get_src_addr(uint8_t src_addr[2]);
void phy_layer_set_dst_addr(uint8_t *addr, uint8_t length);
bool phy_layer_send_raw_data(uint8_t *dst_mac_addr, uint8_t *raw_data, uint32_t length);

#endif