# Home Assistant Extras

Various Home Assistant scripts and tools.

## IR receiver

One easy way to use a TV remote with Home Assistant is to use an Arduino Uno with a IR receiver like TSOP38238.

How to get started:
* Install Arduino IDE or arduino-cli.
* Wire up Arduino Uno and an IR receiver. Vss to 3v, GND to GND and data to pin 11.
* Build and uppload the code found in ´arduino_ir_recv´:
  1. `make compile`
  2. `make upload` (you may have to adjust the port in the Makefile)
* Connect the Arduino Uno via USB to the Home Assistant host.
* Configure Home Assistant to use serial sensor platform: https://www.home-assistant.io/integrations/serial/
* Add

### Home Assistant config example and automation

configuration.yaml:

```
sensor:
  - platform: serial
    serial_port: /dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_A413237393535151A022-if00
    baudrate: 9600
```

It is also useful to add some extra logging to see if anything is received from the Arduino. The logs will appear in the Core logs (http://homeassistant.local:8123/hassio/system). With this you can also discover the various codes sent by the remote:
```
logger:
    default: warning
    logs:
        homeassistant.components.serial: debug
```

Automation:

```
alias: Play radio
description: Play radio on Sonos speaker when yellow button is pressed on remote
trigger:
  - platform: state
    entity_id: sensor.serial_sensor
    to: '{"encoding":"NEC","address":4,"command":114}'
condition: []
action:
  - service: media_player.select_source
    data:
      source: Radio Gaga
    target:
      device_id: 34322342342342342
mode: single
```
