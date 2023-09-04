#include "Arduino.h"
#include "config.h"
#include "alimentacion.h"

pwr_estado_t pwr_estado;

/**
* Inicializa las cosas necesarias para la monitorizacion de la alimentacion.
* @return Nada
*/
int alimentacion_init(void){

#ifdef DEBUGGINGbrousse

    Serial.begin(115200);
#endif
    //Entrada analogica
    //set the resolution to 12 bits (0-4096)
    analogReadResolution(12);

    //Entradas digitales
    //Cargador conectado
    //Bateria cargando
    //Bateria cargada

    //Salidas digitales
    //Led bateria baja
    pinMode(LED_BAT_BAJA_IO_NUM, OUTPUT);
    //Led bateria cargando
    //Led bateria cargada
}

/**
* Retorna la tension de la bateria.
* @return Tension de la bateria en milivolts
*/
uint32_t get_tension_bateria_mV(void){
  return analogReadMilliVolts(BATT_ANALOG_IO_NUM);
}

/**
* Prende un led.
* @param io_num Salida digital conectada al led.
* @return Nada.
*/
void prender_led(int io_num){
  digitalWrite(io_num, HIGH);
}

/**
* Apaga un led.
* @param io_num Salida digital conectada al led.
* @return Nada.
*/
void apagar_led(int io_num){
  digitalWrite(io_num, LOW);
}

/**
* Proceso de monitorizacion de la alimentacion.
* @return 0.
*/
int alimentacion_tarea(void){
  uint32_t tension;

  tension = get_tension_bateria_mV();

  if(tension < NIVEL_BATERIA_CRITICA){
    pwr_estado = BATERIA_CRITICA;
  } else if(tension < NIVEL_BATERIA_BAJA){
    pwr_estado = BATERIA_BAJA;
  } else {
    pwr_estado = BATERIA_OK;
  }

  switch(pwr_estado){
    case BATERIA_CRITICA:
      apagar_led(LED_BAT_BAJA_IO_NUM);
    break;
    case BATERIA_BAJA:
      prender_led(LED_BAT_BAJA_IO_NUM);
    break;
    case BATERIA_OK:
      apagar_led(LED_BAT_BAJA_IO_NUM);
    break;
    case BATERIA_CARGANDO:
    break;
    case BATERIA_CARGADA:
    break;
    default:
    break;
  }

#ifdef DEBUGGING
  Serial.printf("ADC millivolts value = %d\n", tension);
  Serial.printf("Estado bateria: %d\n", (int)pwr_estado);
#endif
  return 0;
}

