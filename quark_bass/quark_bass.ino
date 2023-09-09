#include "bluetooth.h"
#include "alimentacion.h"
#include "io.h"
#include "config.h"

void setup() {
#ifdef DEBUGGING
    Serial.begin(115200);
#endif

  //arrancar_a2dp();
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
}

void loop() {
  delay(500);
}
