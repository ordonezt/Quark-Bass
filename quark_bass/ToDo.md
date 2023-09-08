La idea es hacer una maquina de estados controlada por eventos.
El micro esta en bajo consumo, si el switch de encendido esta ON chequea el
nivel de bateria, si la bateria esta critica vuelve al bajo consumo.
Si no arranca el proceso A2DP.

Hilos:
    Control de bateria:
        +Bateria critica
        +Bateria baja
        +Bateria normal
        +Bateria cargando
        +Bateria llena

    Interaccion del usuario:
        +Boton de pairing
        +Encendido/Apagado

