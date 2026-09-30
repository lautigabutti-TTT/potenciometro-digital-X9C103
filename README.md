# Potenciómetro digital X9C103

Proyecto de laboratorio para controlar un potenciómetro digital X9C103 mediante Arduino.

## Objetivo

- Comprender el funcionamiento del integrado X9C103.
- Controlar su cursor por software mediante un microcontrolador.
- Permitir al usuario ingresar un valor de 0 a 99.
- Llevar el cursor a la posición indicada, en menos de 50 s en el peor caso.
- Validar la posición por cálculo de tensión y medición.
- Verificar persistencia de la última posición luego de un reinicio.

## Descripción del integrado

El X9C103 es un potenciómetro digital lineal de 100 posiciones con resistencia total de 10 kΩ. Incluye memoria no volátil para retener la última posición.

Pines principales:
- Vh: terminal alta del potenciómetro.
- Vw: wiper o cursor.
- Vl: terminal baja del potenciómetro.
- CS: chip select.
- U/D: sentido de movimiento (incremento/decremento).
- INC: pulso de incremento/decremento.

## Esquema de conexión sugerido

- Arduino D8 -> CS
- Arduino D9 -> U/D
- Arduino D10 -> INC
- Arduino D2 -> botón de arranque
- Vh -> +5 V
- Vl -> GND
- Vw -> entrada analógica o nodos de medición
- 10 kΩ de pull-up/pull-down según la implementación del circuito

## Funcionamiento

1. El usuario ingresa el valor objetivo (0 a 99) desde el monitor serial.
2. Presiona el botón de arranque.
3. El firmware mueve el wiper del X9C103 hacia la posición objetivo.
4. Se realiza una verificación rápida de la posición mediante cálculo de tensión.
5. La posición final queda retenida en la memoria no volátil del integrado.

## Fórmula de tensión

Si la resistencia total es 10 kΩ y el cursor está en la posición N:

R_total = 10 kΩ
R_n = (N / 99) * 10 kΩ

El voltaje del cursor respecto a masa, con Vh = 5 V y Vl = 0 V, se puede calcular como:

Vw = 5 V * (N / 99)

Ejemplo:
- N = 50 -> Vw ≈ 2,53 V
- N = 99 -> Vw ≈ 5,00 V

## Archivos del proyecto

- `arduino/X9C103_Controller.ino`: firmware de Arduino.
- `docs/Informe_TP_X9C103.md`: informe del trabajo práctico.

## Cómo usar

1. Conectar el X9C103 según el esquema.
2. Abrir el sketch en Arduino IDE.
3. Cargar el programa en la placa.
4. Enviar un valor por serial, por ejemplo: `35`.
5. Presionar el botón de arranque.
6. Observar que el cursor se mueve hasta la posición indicada.

## Requisitos

- Arduino Uno o compatible.
- X9C103.
- Protoboard, jumper wires y botón.
- Multímetro de referencia.

## Estado

Este repositorio contiene la base funcional para la implementación del proyecto académico, con firmware y documentación técnica en español.
