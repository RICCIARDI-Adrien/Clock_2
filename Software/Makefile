PATH_INCLUDES = Includes
PATH_OBJECTS = Objects
PATH_SOURCES = Sources

CC = xc8
CCFLAGS = --chip=18F46K22 --std=c99 --objdir=$(PATH_OBJECTS) --outdir=$(PATH_OBJECTS) -I$(PATH_INCLUDES) -IBME680_driver -D_XTAL_FREQ=64000000

BINARY = Firmware.hex
SOURCES = BME680_driver/bme680.c $(PATH_SOURCES)/Display.c $(PATH_SOURCES)/Main.c $(PATH_SOURCES)/Menu_Buttons.c $(PATH_SOURCES)/Ring.c $(PATH_SOURCES)/RTC.c $(PATH_SOURCES)/Sensors.c

all: $(PATH_OBJECTS)
	$(CC) $(CCFLAGS) $(SOURCES) -O$(BINARY)
	cp $(PATH_OBJECTS)/$(BINARY) .

$(PATH_OBJECTS):
	mkdir -p $(PATH_OBJECTS)

clean:
	rm -f $(BINARY)
	rm -rf $(PATH_OBJECTS)
