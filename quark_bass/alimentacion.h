#pragma once

typedef enum{
  BATERIA_NA,
  BATERIA_CRITICA,
  BATERIA_BAJA,
  BATERIA_OK,
  BATERIA_CARGANDO,
  BATERIA_CARGADA
}pwr_estado_t;

/**
* Proceso de monitorizacion de la alimentacion.
*/
void tarea_alimentacion(void * pvParameters);
