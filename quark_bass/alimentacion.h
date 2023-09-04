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
* Inicializa las cosas necesarias para la monitorizacion de la alimentacion.
* @return Nada
*/
int alimentacion_init(void);

/**
* Proceso de monitorizacion de la alimentacion.
* @return 0.
*/
int alimentacion_tarea(void);
