#include "Arduino.h"
#include "config.h"

extern EventGroupHandle_t xEventGroup;
bool btn_pairing = -1;
bool sw_pwr = -1;

void io_init(void){
  pinMode(BTN_PAIRING_IO_NUM, INPUT);
  pinMode(SW_PWR_IO_NUM, INPUT);
}

void debounce(void){
  static TickType_t tick_anterior = 0;
  static char entradas_anterior = -1;
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
  bool btn_anterior = -1;
  bool sw_anterior = -1;

  io_init();

  while(1){
    debounce();

    if(btn_pairing != btn_anterior){
      Serial.println("Enviando boton");
      btn_anterior = btn_pairing;
      xEventGroupSetBits(xEventGroup, EVENTO_BTN);
    }

    if(sw_pwr != sw_anterior){
      Serial.println("Enviando sw");
      sw_anterior = sw_pwr;
      xEventGroupSetBits(xEventGroup, EVENTO_SW);
    }

#ifdef DEBUGGING_IO
    Serial.printf("Boton: %d\n", btn_pairing);
    Serial.printf("Switch: %d\n", sw_pwr);
#endif
    
    delay(50);
  }
}

/**
* Retorna el estado del boton de pairing.
* @return TRUE presionado, FALSE no presionado.
*/
bool btn_pairing_get_estado(void){
  return btn_pairing;
}

/**
* Retorna el estado del switch de alimentacion.
* @return TRUE ON, FALSE OFF.
*/
bool sw_pwr_get_estado(void){
  return sw_pwr;
}

