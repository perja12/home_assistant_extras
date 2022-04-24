#include <ArduinoJson.h>
#include <IRremote.hpp>

/*
  Arduino sketch to use with Home Assistant for relaying IR codes to
  Home Assistant over a serial port.  Upload the code to an Arduino
  Uno, connect it to your Home Assistant box via USB and use this in
  the configuration.yaml file:

  sensor:
    - platform: serial
      serial_port: /dev/serial/by-id/usb-Arduino...... (find the port in the Supervisor, HW info)
      baudrate: 9600
 */

const uint8_t IR_RECV_PIN = 11;

void setup() {
    Serial.begin(9600);
    Serial.println("Starting arduino_ir_recv");
    IrReceiver.begin(IR_RECV_PIN, DISABLE_LED_FEEDBACK);
}

void serial_write() {
    StaticJsonDocument<100> jsonBuffer;
    jsonBuffer["encoding"] = getProtocolString(IrReceiver.decodedIRData.protocol);
    jsonBuffer["address"] = IrReceiver.decodedIRData.address;
    jsonBuffer["command"] = IrReceiver.decodedIRData.command;
    serializeJson(jsonBuffer, Serial);
    Serial.println();
    Serial.flush();
}

void loop() {
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            return;
        }

        serial_write();

        // Wait 200 ms after sending a command.
        delay(200);

        // After receiving, this must be called to reset the receiver
        // and prepare it to receive another code.
        IrReceiver.resume();
    }
}
