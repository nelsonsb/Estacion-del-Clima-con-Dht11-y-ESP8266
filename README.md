# Estación del Clima con Dht11 y ESP8266
Código para programar tu ESP9266 en conjunto con un DHT11 para reportar los datos a un servidor Web

El objetivo de este proyecto fué tomar las lecturas de temperatura y humedad de un sensor DHT11 y transmitirlas a un servidor web, utilizando para ello el chip ESP8266.

El código muestra un script básico que envía a una Url los datos ya mencionados utilizando una petición tipo GET.

Del lado de servidor se elaboró un script sencillo en PHP que recibe tales valores y los almacena en una base de datos, para su posterior visualización en una aplicación móvil.

Pueden encontrar más detalles de todo el proyecto en nuestro blog:

[Estación clima con DHT11 y ESP8266](http://www.moviltracing.com/blog/estacion-del-clima-con-esp8266)

Veamos el diagrama de conexiones :

<img src="http://moviltracing.com/iot/images/esp8266_dht11_.png" width="500px" />

El resultado:

<img src="http://moviltracing.com/iot/images/20180309_210203.jpg" width="500px" />

Esperamos que sea de gran ayuda en sus proyectos de IoT.


##Actualización (Julio/2018)

Se incluye un nuevo script en el cual la información se envía ahora a un servidor MMQTT montado en la plataforma openhab.


Saludos

El equipo Moviltracing

www.moviltracing.com

contacto@moviltracing.com
