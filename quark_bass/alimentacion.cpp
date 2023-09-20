#include "Arduino.h"
#include "config.h"
#include "alimentacion.h"

extern EventGroupHandle_t xEventGroup;
pwr_estado_t pwr_estado;

/**
* Inicializa las cosas necesarias para la monitorizacion de la alimentacion.
* @return Nada
*/
void alimentacion_init(void){

// #ifdef DEBUGGING
//     Serial.begin(115200);
// #endif
    //Entrada analogica
    //set the resolution to 12 bits (0-4096)
    analogReadResolution(12);

    //Entradas digitales
    //Cargador conectado
    pinMode(CARGANDO_IO_NUM, INPUT); //Bateria cargando
    //Bateria cargada

    //Salidas digitales
    pinMode(LED_BAT_BAJA_IO_NUM, OUTPUT); //Led bateria baja
    //Led bateria cargando
    //Led bateria cargada
}

/**
* Retorna la tension de la bateria.
* @return Tension de la bateria en milivolts
*/
uint32_t get_tension_bateria_mV(void){
  return CTE_DIVISOR_BATERIA * analogReadMilliVolts(BATT_ANALOG_IO_NUM);
}

/**
* Retorna el estado del pin que indica la carga.
* @return true cargando, false no cargando.
*/
bool get_pin_cargando(void){
  return !(bool)digitalRead(CARGANDO_IO_NUM);
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
*/
void tarea_alimentacion(void * pvParameters){
  pwr_estado_t estado_anterior = BATERIA_NA;
  bool cargando;

  alimentacion_init();

  while(1){
    uint32_t tension;

    tension = get_tension_bateria_mV();
    cargando = get_pin_cargando();

    if(cargando){
      pwr_estado = BATERIA_CARGANDO;
    } else {
      switch(pwr_estado){
        case BATERIA_CRITICA:
          if(tension > NIVEL_BATERIA_BAJA){
            pwr_estado = BATERIA_OK;
          } else if(tension > (NIVEL_BATERIA_CRITICA + BAT_HISTERESIS)){
            pwr_estado = BATERIA_BAJA;
          } else{
            pwr_estado = BATERIA_CRITICA;
          }
        break;
        case BATERIA_BAJA:
          if(tension > (NIVEL_BATERIA_BAJA + BAT_HISTERESIS)){
            pwr_estado = BATERIA_OK;
          } else if(tension > (NIVEL_BATERIA_CRITICA - BAT_HISTERESIS)){
            pwr_estado = BATERIA_BAJA;
          } else{
            pwr_estado = BATERIA_CRITICA;
          }
        break;
        case BATERIA_OK:
          if(tension > (NIVEL_BATERIA_BAJA - BAT_HISTERESIS)){
            pwr_estado = BATERIA_OK;
          } else if(tension > NIVEL_BATERIA_CRITICA){
            pwr_estado = BATERIA_BAJA;
          } else{
            pwr_estado = BATERIA_CRITICA;
          }
        break;
        default:
          if(tension > NIVEL_BATERIA_BAJA){
            pwr_estado = BATERIA_OK;
          } else if(tension > NIVEL_BATERIA_CRITICA){
            pwr_estado = BATERIA_BAJA;
          } else{
            pwr_estado = BATERIA_CRITICA;
          }
        break;
      }
    }

    if(pwr_estado != estado_anterior){
      estado_anterior = pwr_estado;
      xEventGroupSetBits(xEventGroup, EVENTO_PWR);
    }
    
    switch(pwr_estado){
      case BATERIA_BAJA:
        prender_led(LED_BAT_BAJA_IO_NUM);
      break;
      default:
        apagar_led(LED_BAT_BAJA_IO_NUM);
      break;
    }

#ifdef DEBUGGING_PWR
    Serial.printf("ADC millivolts value = %d\n", tension);
    Serial.printf("Estado bateria: %d\n", (int)pwr_estado);
#endif

    delay(100);
  }
}

/**
* Devuelve el estado de la alimentacion
* @return BATERIA_NA Estado incierto
          BATERIA_CRITICA Bateria inoperable
          BATERIA_BAJA Bateria proxima a acabarse
          BATERIA_OK Bateria con buen nivel de carga
          BATERIA_CARGANDO La bateria esta siendo cargada
          BATERIA_CARGADA La bateria esta totalmente cargada
*/
pwr_estado_t alimentacion_get_state(void){
  return pwr_estado;
}

/**
* Pone en bajo consumo al ESP
*/
void bajo_consumo(void){
  esp_deep_sleep_start();
}
