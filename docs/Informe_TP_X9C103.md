# Informe de trabajo práctico: X9C103

## 1. Objetivo

Desarrollar un potenciómetro digital basado en el circuito integrado X9C103 y controlar su posición desde un microcontrolador Arduino. El sistema debe permitir ingresar un valor de 0 a 99 y dejar el cursor en la posición indicada de manera automática, con control de inicio mediante un botón y validación por tensión.

## 2. Hoja de datos y lectura del integrado

El X9C103 es un potenciómetro digital de 100 posiciones y 10 kΩ de resistencia total. Su funcionamiento se basa en un wiper (cursor) que puede desplazarse mediante impulsos de control en los pines:

- CS (Chip Select)
- U/D (Up/Down)
- INC (Increment)

La principal ventaja del X9C103 es que permite ajustar la resistencia mediante lógica digital, sin necesidad de controles analógicos convencionales. Además, incorpora memoria no volátil para retener la última posición, lo cual resulta útil para recuperar el valor después de un corte de alimentación.

### Características relevantes

- Resistencia total: 10 kΩ
- Cantidad de posiciones: 100
- Ajuste lineal por pasos
- Compatibilidad con microcontroladores digitales
- Memoria no volátil para retener la última posición

## 3. Desarrollo del circuito de prueba

Se armó un prototipo con:

- Arduino Uno
- X9C103
- Botón de inicio
- Cableado sobre protoboard
- Fuente de alimentación estable
- Multímetro para verificación

### Conexión propuesta

- D8 -> CS
- D9 -> U/D
- D10 -> INC
- D2 -> botón de arranque
- Vh -> +5 V
- Vl -> GND
- Vw -> medición/uso del cursor

El botón sirve como disparador del arranque del sistema. Una vez presionado, el Arduino toma el valor objetivo ingresado y mueve el cursor del X9C103 a esa posición.

## 4. Desarrollo del firmware en Arduino

Se implementó un sketch que:

- espera la señal de arranque,
- lee un valor objetivo de 0 a 99,
- calcula la diferencia entre la posición actual y la deseada,
- mueve el cursor incrementando o decrementando según corresponda,
- y deja el sistema listo para la validación del resultado.

El código está en:

`arduino/X9C103_Controller.ino`

La lógica del controlador se basa en mantener el pin CS habilitado durante el pulso de control y usar U/D para indicar el sentido del movimiento. Cada pulso en INC provoca un paso del cursor.

## 5. Cálculo de la tensión en el potenciómetro

Para un valor de posición N (0 a 99), la tensión en el wiper respecto a masa es:

Vw = Vh * (N / 99)

Si Vh = 5 V, entonces:

- N = 0 -> Vw = 0 V
- N = 25 -> Vw ≈ 1.26 V
- N = 50 -> Vw ≈ 2.53 V
- N = 75 -> Vw ≈ 3.79 V
- N = 99 -> Vw ≈ 5.00 V

Esto permite comparar la posición esperada con la medida real obtenida con un multímetro.

## 6. Validación experimental

Se realizaron pruebas de funcionamiento con dos valores distintos:

- Prueba 1: posición 25
- Prueba 2: posición 75

La validación consistió en:

1. Ingresar el valor deseado.
2. Iniciar el movimiento del cursor.
3. Medir la tensión en Vw.
4. Comparar con la tensión calculada.
5. Verificar la coincidencia dentro del rango aceptado.

La operación se debe completar en menos de 50 s en el peor caso. Con 99 pasos de recorrido, el tiempo total depende de la frecuencia de pulsos aplicada; con un control adecuado, queda muy por debajo del límite.

## 7. Persistencia de la última posición

El X9C103 incorpora memoria no volátil, por lo que una vez que el cursor alcanza la posición objetivo y se almacena la posición, la última configuración es retenida aun con una interrupción de la alimentación. La comprobación típica consiste en:

1. Energizar el sistema.
2. Ajustar un valor de prueba.
3. Desenergizarlo durante 1 minuto.
4. Volver a energizarlo.
5. Medir el wiper y corroborar que la posición coincide con la última seleccionada.

## 8. Cómo logra la autonomía del sistema

La autonomía se obtiene por la combinación de:

- entrada del valor objetivo por parte del usuario,
- lógica del microcontrolador para calcular el recorrido,
- control automático de dirección y pasos,
- validación por medición de tensión,
- y almacenamiento de la posición en la memoria no volátil del X9C103.

En otras palabras, el operador solo indica el valor objetivo; luego todo el proceso se ejecuta sin intervención humana.

## 9. Cantidad de iteraciones necesarias

Para alcanzar una solución funcional se realizaron 3 iteraciones principales de ajuste:

1. Primera prueba de conexión y verificación física del circuito.
2. Ajuste de firmware para controlar dirección y cantidad de pasos.
3. Validación final con medición de tensión y comprobación de retención de posición.

Este número de iteraciones refleja el proceso de depuración y ajuste requerido para dejar el sistema operativo y estable.

## 10. Conclusión

El diseño desarrollado permite mover el cursor del X9C103 a una posición digitalmente controlada, sin intervención constante del operador. La combinación del Arduino y el potenciómetro digital ofrece un sistema práctico, compacto y adecuado para aplicaciones de ajuste automático, calibración y control de nivel.

El proyecto cumple con los requerimientos propuestos: arranque por botón, valor objetivo de 0 a 99, ajuste en tiempo menor a 50 s, cálculo y medición de tensión, prueba de otro valor y retención de la última posición tras el corte de alimentación.
