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

/**
* Devuelve el estado de la alimentacion
* @return BATERIA_NA Estado incierto
          BATERIA_CRITICA Bateria inoperable
          BATERIA_BAJA Bateria proxima a acabarse
          BATERIA_OK Bateria con buen nivel de carga
          BATERIA_CARGANDO La bateria esta siendo cargada
          BATERIA_CARGADA La bateria esta totalmente cargada
*/
pwr_estado_t alimentacion_get_state(void);

/**
* Pone en bajo consumo al ESP
*/
void bajo_consumo(void);
