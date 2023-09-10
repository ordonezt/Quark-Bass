#pragma once

/* Tarea de interfaz de usuario. */
void tarea_io( void * pvParameters );
/**
* Retorna el estado del boton de pairing.
* @return TRUE presionado, FALSE no presionado.
*/
bool btn_pairing_get_estado(void);
/**
* Retorna el estado del switch de alimentacion.
* @return TRUE ON, FALSE OFF.
*/
bool sw_pwr_get_estado(void);
