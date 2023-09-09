#include "Arduino.h"
#include "config.h"

bool btn_pairing;
bool sw_pwr;

void io_init(void){
  pinMode(BTN_PAIRING_IO_NUM, INPUT);
  pinMode(SW_PWR_IO_NUM, INPUT);
}

void debounce(void){
  static TickType_t tick_anterior = 0;
  static char entradas_anterior = 0;
  char entradas = 0;
  TickType_t tick_actual = xTaskGetTickCount();
  
  entradas |= digitalRead(BTN_PAIRING_IO_NUM) << 0;
  entradas |= digitalRead(SW_PWR_IO_NUM) << 1;

  if(tick_actual - tick_anterior > (TIEMPO_DEBOUNCE_MS / portTICK_PERIOD_MS)){
    if(entradas == entradas_anterior){
      btn_pairing = (entradas >> 0) & 1;
      sw_pwr      = (entradas >> 1) & 1;
    }
    entradas_anterior = entradas;
    tick_anterior = tick_actual;
  }
}

/* Tarea de interfaz de usuario. */
void tarea_io( void * pvParameters )
{
  io_init();

  while(1){
    debounce();

#ifdef DEBUGGING
    Serial.printf("Boton: %d\n", btn_pairing);
    Serial.printf("Switch: %d\n", sw_pwr);
#endif
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

