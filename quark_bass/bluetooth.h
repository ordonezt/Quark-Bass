#pragma once

/**
* Le da arranque al proceso de recepcion A2DP.
* @return The test results
*/
void arrancar_a2dp();
/**
* Detiene el proceso A2DP.
*/
void detener_a2dp(void);

/**
* Retorna el estado del A2DP
* @return true esta encendido, false esta apagado.
*/
bool a2dp_get_estado(void);
