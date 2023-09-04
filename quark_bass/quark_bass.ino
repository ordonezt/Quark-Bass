#include "bluetooth.h"
#include "alimentacion.h"

void setup() {
  arrancar_a2dp();
  alimentacion_init();
}

void loop() {
  alimentacion_tarea();
  delay(100);
}
