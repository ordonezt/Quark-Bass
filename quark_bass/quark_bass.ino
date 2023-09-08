#include "bluetooth.h"
#include "alimentacion.h"

void setup() {
  //arrancar_a2dp();
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

}
