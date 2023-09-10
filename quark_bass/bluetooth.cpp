#include "BluetoothA2DPSink.h"
#include "config.h"

//Instancia de la clase 'BluetoothA2DPSink' de la libreria 'ESP32-A2DP'. 
BluetoothA2DPSink a2dp_sink = BluetoothA2DPSink();

i2s_config_t i2s_config = {
        .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100, // corrected by info from bluetooth
        .bits_per_sample = (i2s_bits_per_sample_t) 32, /* the A2DP 16 bits will be expanded to 32 bits */
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = 0, // default interrupt priority
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true // avoiding noise in case of data unavailability
    };
    
i2s_pin_config_t i2s_pin_config = {
    .bck_io_num   = BCK_IO_NUM,
    .ws_io_num    = WS_IO_NUM,
    .data_out_num = DATA_OUT_IO_NUM,
};

/**
* Le da arranque al proceso de recepcion A2DP.
*/
void arrancar_a2dp() {
    a2dp_sink.set_pin_config(i2s_pin_config);
    a2dp_sink.set_i2s_config(i2s_config);
    a2dp_sink.start(NOMBRE_DISPOSITIVO, true);
}

/**
* Detiene el proceso A2DP.
*/
void detener_a2dp(void){
  a2dp_sink.end(false);
}
