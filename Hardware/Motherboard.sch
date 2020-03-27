EESchema Schematic File Version 4
LIBS:Motherboard-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title "Clock 2 motherboard"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 1500 3550 1300 1000
U 5E7ACE5B
F0 "Sensors_RTC" 50
F1 "Sensors_RTC.sch" 50
F2 "RTC_SCL" I R 2800 3700 50 
F3 "RTC_SDA" B R 2800 3800 50 
F4 "BME680_SCK" I R 2800 4100 50 
F5 "BME680_SDO" O R 2800 4200 50 
F6 "BME680_SDI" I R 2800 4300 50 
F7 "BME680_CS" I R 2800 4400 50 
F8 "RTC_1HZ" O R 2800 3900 50 
$EndSheet
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5E7B1C5C
P 9100 4850
F 0 "J2" H 9072 4874 50  0000 R CNN
F 1 "JTAG" H 9072 4783 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 9100 4850 50  0001 C CNN
F 3 "~" H 9100 4850 50  0001 C CNN
	1    9100 4850
	-1   0    0    -1  
$EndComp
Text Notes 9200 4700 0    50   ~ 0
PICkit 3 standard pinout\nwithout LVP pin
$Comp
L Device:C C4
U 1 1 5E7B4EF8
P 8000 5750
F 0 "C4" H 8115 5887 50  0000 L CNN
F 1 "100n" H 8115 5796 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8038 5600 50  0001 C CNN
F 3 "~" H 8000 5750 50  0001 C CNN
F 4 "25V" H 8115 5705 50  0000 L CNN "Champ4"
F 5 "X7R" H 8115 5614 50  0000 L CNN "Champ5"
	1    8000 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E7BB06E
P 7750 5550
AR Path="/5E7ACE5B/5E7BB06E" Ref="R?"  Part="1" 
AR Path="/5E7BB06E" Ref="R4"  Part="1" 
F 0 "R4" V 7543 5550 50  0000 C CNN
F 1 "220" V 7634 5550 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7680 5550 50  0001 C CNN
F 3 "~" H 7750 5550 50  0001 C CNN
	1    7750 5550
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0111
U 1 1 5E7BC5F8
P 8000 5100
F 0 "#PWR0111" H 8000 4950 50  0001 C CNN
F 1 "+5V" H 8015 5273 50  0000 C CNN
F 2 "" H 8000 5100 50  0001 C CNN
F 3 "" H 8000 5100 50  0001 C CNN
	1    8000 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E7BD333
P 8000 5350
AR Path="/5E7ACE5B/5E7BD333" Ref="R?"  Part="1" 
AR Path="/5E7BD333" Ref="R3"  Part="1" 
F 0 "R3" H 7930 5304 50  0000 R CNN
F 1 "10K" H 7930 5395 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7930 5350 50  0001 C CNN
F 3 "~" H 8000 5350 50  0001 C CNN
	1    8000 5350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E7C6C3E
P 8000 6000
F 0 "#PWR0112" H 8000 5750 50  0001 C CNN
F 1 "GND" H 8005 5827 50  0000 C CNN
F 2 "" H 8000 6000 50  0001 C CNN
F 3 "" H 8000 6000 50  0001 C CNN
	1    8000 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5E7CC116
P 8350 5000
F 0 "#PWR0113" H 8350 4750 50  0001 C CNN
F 1 "GND" H 8355 4827 50  0000 C CNN
F 2 "" H 8350 5000 50  0001 C CNN
F 3 "" H 8350 5000 50  0001 C CNN
	1    8350 5000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5E7CC521
P 8550 5000
F 0 "#PWR0114" H 8550 4850 50  0001 C CNN
F 1 "+5V" H 8565 5173 50  0000 C CNN
F 2 "" H 8550 5000 50  0001 C CNN
F 3 "" H 8550 5000 50  0001 C CNN
	1    8550 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	8900 5050 8800 5050
Wire Wire Line
	8800 5050 8800 5550
Wire Wire Line
	8900 4950 8550 4950
Wire Wire Line
	8550 4950 8550 5000
Wire Wire Line
	8900 4850 8350 4850
Wire Wire Line
	8350 4850 8350 5000
Wire Wire Line
	7900 5550 8000 5550
Wire Wire Line
	8000 5550 8000 5500
Connection ~ 8000 5550
Wire Wire Line
	8000 5550 8800 5550
Wire Wire Line
	8000 5550 8000 5600
Wire Wire Line
	8000 5200 8000 5100
Wire Wire Line
	8000 5900 8000 6000
$Comp
L MCU_Microchip_PIC18:PIC18F46K22-xPT U1
U 1 1 5E7EF1E1
P 5950 3500
F 0 "U1" H 6250 2350 50  0000 C CNN
F 1 "PIC18F46K22-xPT" H 6550 2250 50  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 5800 3300 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001412G.pdf" H 5900 3100 50  0001 C CNN
	1    5950 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 5550 7250 5550
Text Label 7250 5550 0    50   ~ 0
RE3
Wire Wire Line
	7250 2500 7650 2500
Text Label 7650 2500 2    50   ~ 0
RE3
Wire Wire Line
	4550 4100 2800 4100
Wire Wire Line
	2800 4200 4550 4200
Wire Wire Line
	4550 4300 2800 4300
Wire Wire Line
	2800 4400 4550 4400
Wire Wire Line
	3150 3700 3150 2900
Wire Wire Line
	3150 2900 4550 2900
Wire Wire Line
	2800 3700 3150 3700
Wire Wire Line
	2800 3800 3250 3800
Wire Wire Line
	3250 3800 3250 3000
Wire Wire Line
	3250 3000 4550 3000
Wire Wire Line
	4550 3100 3350 3100
Wire Wire Line
	3350 3100 3350 3900
Wire Wire Line
	3350 3900 2800 3900
$Comp
L power:GND #PWR0115
U 1 1 5E7B8383
P 5950 4800
F 0 "#PWR0115" H 5950 4550 50  0001 C CNN
F 1 "GND" H 5955 4627 50  0000 C CNN
F 2 "" H 5950 4800 50  0001 C CNN
F 3 "" H 5950 4800 50  0001 C CNN
	1    5950 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4800 5950 4700
$Comp
L Device:C C5
U 1 1 5E7B8F01
P 6200 1850
F 0 "C5" H 6315 1987 50  0000 L CNN
F 1 "100n" H 6315 1896 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6238 1700 50  0001 C CNN
F 3 "~" H 6200 1850 50  0001 C CNN
F 4 "25V" H 6315 1805 50  0000 L CNN "Champ4"
F 5 "X7R" H 6315 1714 50  0000 L CNN "Champ5"
	1    6200 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5E7BA919
P 6700 1850
F 0 "C6" H 6815 1987 50  0000 L CNN
F 1 "4.7u" H 6815 1896 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6738 1700 50  0001 C CNN
F 3 "~" H 6700 1850 50  0001 C CNN
F 4 "25V" H 6815 1805 50  0000 L CNN "Champ4"
F 5 "X7R" H 6815 1714 50  0000 L CNN "Champ5"
	1    6700 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5E7BB4EF
P 6450 2100
F 0 "#PWR0116" H 6450 1850 50  0001 C CNN
F 1 "GND" H 6455 1927 50  0000 C CNN
F 2 "" H 6450 2100 50  0001 C CNN
F 3 "" H 6450 2100 50  0001 C CNN
	1    6450 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2000 6200 2050
Wire Wire Line
	6200 2050 6450 2050
Wire Wire Line
	6700 2050 6700 2000
Wire Wire Line
	6450 2050 6450 2100
Connection ~ 6450 2050
Wire Wire Line
	6450 2050 6700 2050
$Comp
L power:+5V #PWR0117
U 1 1 5E7BF04F
P 5950 1600
F 0 "#PWR0117" H 5950 1450 50  0001 C CNN
F 1 "+5V" H 5965 1773 50  0000 C CNN
F 2 "" H 5950 1600 50  0001 C CNN
F 3 "" H 5950 1600 50  0001 C CNN
	1    5950 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 1600 5950 1650
Wire Wire Line
	5950 1650 6200 1650
Wire Wire Line
	6700 1650 6700 1700
Wire Wire Line
	6200 1650 6200 1700
Connection ~ 6200 1650
Wire Wire Line
	6200 1650 6700 1650
Wire Wire Line
	5950 1650 5950 2300
Connection ~ 5950 1650
$Sheet
S 8750 2000 1300 2050
U 5E7CFAFC
F0 "Display" 50
F1 "Display.sch" 50
F2 "DISPLAY_RS" I L 8750 3750 50 
F3 "DISPLAY_RW" I L 8750 3850 50 
F4 "DISPLAY_E" I L 8750 3950 50 
F5 "DISPLAY_DB0" B L 8750 3100 50 
F6 "DISPLAY_DB1" B L 8750 3200 50 
F7 "DISPLAY_DB2" B L 8750 3300 50 
F8 "DISPLAY_DB3" B L 8750 3400 50 
F9 "DISPLAY_DB4" B L 8750 3500 50 
F10 "DISPLAY_DB5" B L 8750 3600 50 
F11 "DISPLAY_DB6" B L 8750 2800 50 
F12 "DISPLAY_DB7" B L 8750 2700 50 
F13 "DISPLAY_BACKLIGHT" I L 8750 2200 50 
$EndSheet
Wire Wire Line
	7250 2700 8750 2700
Wire Wire Line
	8750 2800 7250 2800
Wire Wire Line
	7250 3100 8750 3100
Wire Wire Line
	8750 3200 7250 3200
Wire Wire Line
	7250 3300 8750 3300
Wire Wire Line
	8750 3400 7250 3400
Wire Wire Line
	7250 3500 8750 3500
Wire Wire Line
	8750 3600 7250 3600
Wire Wire Line
	7250 4300 8650 4300
Wire Wire Line
	8650 4300 8650 3950
Wire Wire Line
	8650 3950 8750 3950
Wire Wire Line
	7250 4200 8550 4200
Wire Wire Line
	8550 4200 8550 3850
Wire Wire Line
	8550 3850 8750 3850
Wire Wire Line
	7250 4100 8450 4100
Wire Wire Line
	8450 4100 8450 3750
Wire Wire Line
	8450 3750 8750 3750
Wire Wire Line
	4550 4000 3750 4000
Text Label 3750 4000 0    50   ~ 0
DISPLAY_BACKLIGHT
Wire Wire Line
	7900 2200 8750 2200
Text Label 7900 2200 0    50   ~ 0
DISPLAY_BACKLIGHT
Wire Wire Line
	8650 4400 8650 4650
Wire Wire Line
	8650 4650 8900 4650
Wire Wire Line
	7250 4400 8650 4400
Wire Wire Line
	8900 4750 8550 4750
Wire Wire Line
	8550 4750 8550 4500
Wire Wire Line
	8550 4500 7250 4500
$Comp
L Device:Buzzer BZ1
U 1 1 5E7EB9A5
P 3700 3650
F 0 "BZ1" H 3800 3850 50  0000 C CNN
F 1 "ABI-009-RC or SV12-5" H 3450 3400 50  0000 C CNN
F 2 "Buzzer_Beeper:MagneticBuzzer_ProSignal_ABI-009-RC" V 3675 3750 50  0001 C CNN
F 3 "~" V 3675 3750 50  0001 C CNN
	1    3700 3650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5E7F7B03
P 3900 3550
F 0 "#PWR04" H 3900 3300 50  0001 C CNN
F 1 "GND" H 3905 3377 50  0000 C CNN
F 2 "" H 3900 3550 50  0001 C CNN
F 3 "" H 3900 3550 50  0001 C CNN
	1    3900 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 3750 3950 3750
Wire Wire Line
	3950 3750 3950 3900
Wire Wire Line
	3950 3900 4550 3900
Wire Wire Line
	3900 3550 3800 3550
Wire Wire Line
	7250 3800 8150 3800
Text Label 8150 3800 2    50   ~ 0
ALARM_BUTTON
Wire Wire Line
	7250 3900 8150 3900
Text Label 8150 3900 2    50   ~ 0
BACKLIGHT_BUTTON
Wire Wire Line
	7250 4000 8150 4000
Text Label 8150 4000 2    50   ~ 0
SETTINGS_BUTTON
NoConn ~ 4550 3800
NoConn ~ 4550 3600
NoConn ~ 4550 3500
NoConn ~ 4550 3400
NoConn ~ 4550 2700
NoConn ~ 4550 3200
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5E84D5D2
P 8800 1000
F 0 "J6" H 8772 974 50  0000 R CNN
F 1 "USB" H 8772 883 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8800 1000 50  0001 C CNN
F 3 "~" H 8800 1000 50  0001 C CNN
	1    8800 1000
	-1   0    0    -1  
$EndComp
Text Notes 9600 1100 0    50   ~ 0
USB power connector.\nUSB D+ and D- are not connected.
$Comp
L Device:C C15
U 1 1 5E853C46
P 8100 1050
F 0 "C15" H 8215 1187 50  0000 L CNN
F 1 "100n" H 8215 1096 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8138 900 50  0001 C CNN
F 3 "~" H 8100 1050 50  0001 C CNN
F 4 "25V" H 8215 1005 50  0000 L CNN "Champ4"
F 5 "X7R" H 8215 914 50  0000 L CNN "Champ5"
	1    8100 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 5E8541BC
P 8100 800
F 0 "#PWR09" H 8100 650 50  0001 C CNN
F 1 "+5V" H 8115 973 50  0000 C CNN
F 2 "" H 8100 800 50  0001 C CNN
F 3 "" H 8100 800 50  0001 C CNN
	1    8100 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E854558
P 8100 1300
F 0 "#PWR010" H 8100 1050 50  0001 C CNN
F 1 "GND" H 8105 1127 50  0000 C CNN
F 2 "" H 8100 1300 50  0001 C CNN
F 3 "" H 8100 1300 50  0001 C CNN
	1    8100 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 800  8100 850 
Wire Wire Line
	8100 850  8550 850 
Wire Wire Line
	8550 850  8550 1000
Wire Wire Line
	8550 1000 8600 1000
Connection ~ 8100 850 
Wire Wire Line
	8100 850  8100 900 
Wire Wire Line
	8600 1100 8550 1100
Wire Wire Line
	8550 1100 8550 1250
Wire Wire Line
	8550 1250 8100 1250
Wire Wire Line
	8100 1250 8100 1200
Wire Wire Line
	8100 1250 8100 1300
Connection ~ 8100 1250
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5E7D4D02
P 1050 6400
F 0 "H3" H 1150 6449 50  0000 L CNN
F 1 "MountingHole_Pad" H 1150 6358 50  0000 L CNN
F 2 "MountingHole:MountingHole_4.5mm_Pad" H 1050 6400 50  0001 C CNN
F 3 "~" H 1050 6400 50  0001 C CNN
	1    1050 6400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5E7D5632
P 2000 6400
F 0 "H4" H 2100 6449 50  0000 L CNN
F 1 "MountingHole_Pad" H 2100 6358 50  0000 L CNN
F 2 "MountingHole:MountingHole_4.5mm_Pad" H 2000 6400 50  0001 C CNN
F 3 "~" H 2000 6400 50  0001 C CNN
	1    2000 6400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 5E7D5F44
P 2950 6400
F 0 "H5" H 3050 6449 50  0000 L CNN
F 1 "MountingHole_Pad" H 3050 6358 50  0000 L CNN
F 2 "MountingHole:MountingHole_4.5mm_Pad" H 2950 6400 50  0001 C CNN
F 3 "~" H 2950 6400 50  0001 C CNN
	1    2950 6400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H6
U 1 1 5E7D621E
P 3900 6400
F 0 "H6" H 4000 6449 50  0000 L CNN
F 1 "MountingHole_Pad" H 4000 6358 50  0000 L CNN
F 2 "MountingHole:MountingHole_4.5mm_Pad" H 3900 6400 50  0001 C CNN
F 3 "~" H 3900 6400 50  0001 C CNN
	1    3900 6400
	1    0    0    -1  
$EndComp
$Sheet
S 1450 1050 1300 900 
U 5E7CE147
F0 "Buttons" 50
F1 "Buttons.sch" 50
F2 "BUTTON_ALARM" O R 2750 1200 50 
F3 "BUTTON_BACKLIGHT" O R 2750 1350 50 
F4 "BUTTON_MINUS" O R 2750 1500 50 
F5 "BUTTON_PLUS" O R 2750 1650 50 
F6 "BUTTON_SETTINGS" O R 2750 1800 50 
$EndSheet
Wire Wire Line
	4550 4500 3750 4500
Text Label 3750 4500 0    50   ~ 0
PLUS_BUTTON
Wire Wire Line
	2750 1650 3750 1650
Text Label 3750 1650 2    50   ~ 0
PLUS_BUTTON
Wire Wire Line
	4550 3300 3750 3300
Text Label 3750 3300 0    50   ~ 0
MINUS_BUTTON
Wire Wire Line
	2750 1500 3750 1500
Wire Wire Line
	2750 1350 3750 1350
Wire Wire Line
	2750 1200 3750 1200
Wire Wire Line
	2750 1800 3750 1800
Text Label 3750 1200 2    50   ~ 0
ALARM_BUTTON
Text Label 3750 1350 2    50   ~ 0
BACKLIGHT_BUTTON
Text Label 3750 1500 2    50   ~ 0
MINUS_BUTTON
Text Label 3750 1800 2    50   ~ 0
SETTINGS_BUTTON
NoConn ~ 4550 2500
NoConn ~ 4550 2600
$Comp
L power:GND #PWR0123
U 1 1 5E7E3802
P 2500 6600
F 0 "#PWR0123" H 2500 6350 50  0001 C CNN
F 1 "GND" H 2505 6427 50  0000 C CNN
F 2 "" H 2500 6600 50  0001 C CNN
F 3 "" H 2500 6600 50  0001 C CNN
	1    2500 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 6500 1050 6550
Wire Wire Line
	1050 6550 2000 6550
Wire Wire Line
	2000 6550 2000 6500
Wire Wire Line
	2000 6550 2500 6550
Wire Wire Line
	2950 6550 2950 6500
Connection ~ 2000 6550
Wire Wire Line
	3900 6550 3900 6500
Wire Wire Line
	2500 6600 2500 6550
Connection ~ 2500 6550
Wire Wire Line
	2500 6550 2950 6550
Wire Wire Line
	2950 6550 3900 6550
Connection ~ 2950 6550
$Comp
L USB_Connector_MUSBD111M0:MUSBD111M0_Supply J7
U 1 1 5E7EC2F9
P 5050 7150
F 0 "J7" H 5428 7196 50  0000 L CNN
F 1 "MUSBD111M0_Supply" H 5428 7105 50  0000 L CNN
F 2 "Empty_Footprint:Empty_Footprint" H 5050 7150 50  0001 C CNN
F 3 "" H 5050 7150 50  0001 C CNN
	1    5050 7150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
