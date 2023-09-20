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
}

void loop() {
  EventBits_t uxBits;
  pwr_estado_t alimentacion;

  uxBits = xEventGroupWaitBits(
            xEventGroup,   /* The event group being tested. */
            EVENTO_ALL, /* The bits within the event group to wait for. */
            pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
            pdFALSE,       /* Don't wait for both bits, either bit will do. */
            portMAX_DELAY );/* Esperar para siempre. */

  Serial.printf("Evento: 0x%X\n", (int)uxBits);
  if(uxBits & EVENTO_PWR){
    alimentacion = alimentacion_get_state();
    switch(alimentacion){
      case BATERIA_CRITICA:
        if(a2dp_get_estado()){
          Serial.println("Apagando BT");
          detener_a2dp();
        }
        bajo_consumo();
      break;
      case BATERIA_NA:
      //Esperamos a que haya un estado de alimentacion definido
      break;
      default:
        if(!a2dp_get_estado()){
          Serial.println("Arrancando BT");
          arrancar_a2dp();
        }
      break;
    }
  }
}
