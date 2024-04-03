```markdown
# Bot de Telegram con Arduino

Este proyecto demuestra cómo crear un bot de Telegram utilizando Arduino para controlar un LED y leer datos de sensores como temperatura, humedad y nivel de luz.

## Requisitos
- Placa Arduino
- Módulo WiFi
- LED
- Sensor DHT (DHT11, DHT21 o DHT22)
- Sensor LDR
- Biblioteca UniversalTelegramBot
- Biblioteca WiFi
- Biblioteca WiFiClientSecure
- Biblioteca DHT

## Instalación
1. Instala las bibliotecas requeridas:
   - UniversalTelegramBot
   - WiFi
   - WiFiClientSecure
   - DHT

2. Configura tu Arduino con los componentes necesarios (LED, sensor DHT, sensor LDR) conectados a los pines especificados.

3. Obten un token de bot de Telegram de Botfather y reemplázalo en el código con tu token.

4. Establece el SSID de tu red WiFi y la contraseña en el código (`WIFI_SSID` y `WIFI_PASSWORD`).

5. Asegúrate de que el certificado raíz para `api.telegram.org` esté añadido usando la función `setCACert()`.

## Uso
1. Sube el código a tu placa Arduino.

2. Una vez que Arduino esté conectado a la red WiFi e inicializado, comenzará a escuchar comandos del bot de Telegram.

3. Envía comandos al bot desde tu aplicación de Telegram:
   - `/start`: Inicializa el bot y muestra los comandos disponibles.
   - `/ledon`: Enciende el LED.
   - `/ledoff`: Apaga el LED.
   - `/status`: Devuelve el estado actual del LED.
   - `/sensores`: Devuelve los datos actuales de los sensores, incluyendo temperatura, humedad y nivel de luz.

4. El bot responderá según los comandos enviados.

## Notas
- Asegúrate de que los componentes estén conectados correctamente a los pines especificados.
- Modifica las configuraciones de pines y tipos de sensores según sea necesario.
- Este código asume el uso del sensor DHT11, modifica la constante `DHT_TYPE` si estás usando un sensor diferente.
- Personaliza las respuestas y funcionalidades del bot según sea necesario.

```
