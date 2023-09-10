#include "bluetooth.h"
#include "alimentacion.h"
#include "io.h"
#include "config.h"

EventGroupHandle_t xEventGroup;

void setup() {
#ifdef DEBUGGING
  Serial.begin(115200);
  Serial.println("Iniciando...");
#endif

  xEventGroup = xEventGroupCreate();
  
  if(xEventGroup == NULL){
    while(1);
  }
  
  xTaskCreate(
    tarea_alimentacion
    ,  "Tarea alimentacion" // A name just for humans
    ,  2048        // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    ,  NULL // Task parameter which can modify the task behavior. This must be passed as pointer to void.
    ,  0  // Priority
    ,  NULL // Task handle is not used here - simply pass NULL
    );

  xTaskCreate(
    tarea_io
    ,  "Tarea io" // A name just for humans
    ,  2048        // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    ,  NULL // Task parameter which can modify the task behavior. This must be passed as pointer to void.
    ,  0  // Priority
    ,  NULL // Task handle is not used here - simply pass NULL
    );

    //arrancar_a2dp();
}

void loop() {
  EventBits_t uxBits;

  uxBits = xEventGroupWaitBits(
            xEventGroup,   /* The event group being tested. */
            EVENTO_ALL, /* The bits within the event group to wait for. */
            pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
            pdFALSE,       /* Don't wait for both bits, either bit will do. */
            portMAX_DELAY );/* Esperar para siempre. */

  Serial.printf("Evento: 0x%X\n", (int)uxBits);
  if(uxBits & EVENTO_SW){
    if(sw_pwr_get_estado()){
      Serial.println("Arrancando BT");
      arrancar_a2dp();
    }else{
      Serial.println("Apagando BT");
      detener_a2dp();
    }
  }
}

void modo_apagado(void){
  //ToDo: Hacer cosas de apagado
  //Entrar a bajo consumo
  esp_sleep_enable_ext0_wakeup((gpio_num_t)SW_PWR_IO_NUM, LOW);
  esp_deep_sleep_start();
}
