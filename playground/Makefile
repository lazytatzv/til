# Makefile for Arduino

# Set the Fully Qualified Board Name (FQBN) and serial port
FQBN = arduino:avr:uno
MONITOR_PORT = /dev/ttyUSB0

# Default target: compile the Arduino sketch
all:
	arduino-cli compile --output-dir=build --fqbn $(FQBN) $(notdir $(CURDIR)).ino

# Upload the compiled sketch to the Arduino
upload:
	arduino-cli upload --input-dir=build -b $(FQBN) -p $(MONITOR_PORT) $(CURDIR)

# Flash using USBasp programmer
ispload:
	arduino-cli upload --input-dir=build -b $(FQBN) -P usbasp $(CURDIR)

# Burn the bootloader using USBasp programmer
burn_bootloader:
	arduino-cli burn-bootloader -b $(FQBN) -P usbasp -v $(CURDIR)

# Clean the build directory
clean:
	rm -rf $(CURDIR)/build

# Open the serial monitor
monitor:
	screen $(MONITOR_PORT) 115200
