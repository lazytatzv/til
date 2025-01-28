# Set the Fully Qualified Board Name (FQBN) and serial port
FQBN = arduino:renesas_uno:minima
MONITOR_PORT = /dev/ttyACM3  # Change this to the correct port
BUILD_DIR = build

# Arduino CLI command
ARDUINO_CLI = arduino-cli

# Default target: compile the Arduino sketch
all:
	$(ARDUINO_CLI) compile --output-dir $(BUILD_DIR) --fqbn $(FQBN) $(CURDIR)/$(notdir $(CURDIR)).ino

# Upload the compiled sketch to Arduino
upload:
	$(ARDUINO_CLI) upload -p $(MONITOR_PORT) --fqbn $(FQBN) --input-dir $(BUILD_DIR) $(CURDIR)/$(notdir $(CURDIR)).ino -v

# Upload using USBasp programmer
ispload:
	$(ARDUINO_CLI) upload -p $(MONITOR_PORT) -P usbasp --fqbn $(FQBN) --input-dir $(BUILD_DIR) $(CURDIR)/$(notdir $(CURDIR)).ino

# Burn the bootloader using USBasp programmer
burn_bootloader:
	$(ARDUINO_CLI) burn-bootloader -P usbasp --fqbn $(FQBN) -v

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)

# Open serial monitor
monitor:
	screen $(MONITOR_PORT) 115200

# Check if the USB device is properly mounted
check_device:
	ls /dev/ttyUSB* /dev/ttyACM* || echo "Device not found. Please check the USB connection."
