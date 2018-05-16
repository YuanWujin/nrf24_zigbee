#include "nz_common.h"

volatile uint8_t node_identify = 0xff;

bool signal_wait(volatile uint8_t * signal, uint16_t delay_time)
{
  uint32_t record_time;
  bool result;
  TickType_t last_wake_time;

  *signal = 0;

  record_time = millis();

  while (!*signal) {
    last_wake_time = xTaskGetTickCount();
    vTaskDelayUntil(&last_wake_time, 250);
    if (millis() - record_time > delay_time)
      break;
  }

  result = (*signal != 0);
  
  *signal = 0;
  return result;
}

bool wait_event(volatile uint8_t * event_ptr, uint16_t delay_time)
{
  uint32_t record_time;
  bool result;
  TickType_t last_wake_time;


  record_time = millis();
  while (event_ptr == NULL) {
    last_wake_time = xTaskGetTickCount();
    vTaskDelayUntil(&last_wake_time, 250);
    if (millis() - record_time > delay_time)
      break;
  }

  debug_printf("leave while wait\n");

  result = (event_ptr != NULL);
  return result;
}