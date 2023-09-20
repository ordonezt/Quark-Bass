#pragma once

//Borrador
/**
* Le da arranque al proceso de recepcion A2DP.
* @param a an integer argument.
* @param s a constant character pointer.
* @see Javadoc_Test()
* @see ~Javadoc_Test()
* @see testMeToo()
* @see publicVar()
* @return The test results
*/

#define DEBUGGING
//#define DEBUGGIN_IO
#define DEBUGGING_PWR

#define UNUSED(x) (void)(sizeof((x), 0))

//Bluetooth
#define NOMBRE_DISPOSITIVO "Quark Bass"

//DAC
#define BCK_IO_NUM      26
#define WS_IO_NUM       25
#define DATA_OUT_IO_NUM 22

//Alimentacion
#define BATT_ANALOG_IO_NUM  4
#define LED_BAT_BAJA_IO_NUM 2
#define NIVEL_BATERIA_CRITICA 3300//mV
#define NIVEL_BATERIA_BAJA    3700//mV
#define CTE_DIVISOR_BATERIA 1.37037037//V/V
#define CARGANDO_IO_NUM     34
#define BAT_HISTERESIS      50//mV

//IO
#define BTN_PAIRING_IO_NUM  0
#define SW_PWR_IO_NUM       35
#define TIEMPO_DEBOUNCE_MS  50

//Eventos
#define EVENTO_SW           0b1
#define EVENTO_BTN          0b10
#define EVENTO_PWR          0b100
#define EVENTO_ALL          (EVENTO_SW | EVENTO_BTN | EVENTO_PWR)
