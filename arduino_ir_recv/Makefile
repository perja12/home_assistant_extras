core := arduino:avr
port := /dev/ttyACM0
fqbn := ${core}:uno

compile:
	mkdir -p bin
	arduino-cli compile --output-dir bin -b ${fqbn} arduino_ir_recv.ino

upload:
	arduino-cli upload -b ${fqbn} -p ${port} --input-dir bin

upload-usbasp:
	arduino-cli upload -b ${fqbn} -P usbasp --verify --input-dir bin

install:
	arduino-cli core install ${core}
	arduino-cli lib install ArduinoJson IRremote

# See this forum post about setting options:
# https://forum.arduino.cc/t/fqbn-for-attiny45/953943
details:
	arduino-cli board details -b ${fqbn}

clean:
	rm -rf bin
