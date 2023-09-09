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

//Bluetooth
#define NOMBRE_DISPOSITIVO "Quark Bass"

//DAC
#define BCK_IO_NUM      26
#define WS_IO_NUM       25
#define DATA_OUT_IO_NUM 22

//Alimentacion
#define BATT_ANALOG_IO_NUM  4
#define LED_BAT_BAJA_IO_NUM 2
#define NIVEL_BATERIA_CRITICA 3600//mV
#define NIVEL_BATERIA_BAJA 3800//mV
#define CTE_DIVISOR_BATERIA 1.4//V/V

//IO
#define BTN_PAIRING_IO_NUM  0
#define SW_PWR_IO_NUM       35
#define TIEMPO_DEBOUNCE_MS  50
