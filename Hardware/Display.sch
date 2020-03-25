EESchema Schematic File Version 4
LIBS:Motherboard-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 3
Title "4 lines x 20 characters LCD display"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x06_Male J3
U 1 1 5E7D0A45
P 4500 2950
F 0 "J3" H 4608 3331 50  0000 C CNN
F 1 "Conn_01x06_Male" H 4608 3240 50  0000 C CNN
F 2 "" H 4500 2950 50  0001 C CNN
F 3 "~" H 4500 2950 50  0001 C CNN
	1    4500 2950
	1    0    0    -1  
$EndComp
Text Notes 4200 3700 0    50   ~ 0
DB0
Text Notes 4200 3800 0    50   ~ 0
DB1
Text Notes 4200 3900 0    50   ~ 0
DB2
Text Notes 4200 4000 0    50   ~ 0
DB3
Text Notes 4200 4100 0    50   ~ 0
DB4
Text Notes 4200 4200 0    50   ~ 0
DB5
Text Notes 4200 4300 0    50   ~ 0
DB6
Text Notes 4200 4400 0    50   ~ 0
DB7
Text Notes 4200 2800 0    50   ~ 0
VSS
Text Notes 4200 2900 0    50   ~ 0
VDD
$Comp
L Connector:Conn_01x10_Male J4
U 1 1 5E7D7996
P 4500 4050
F 0 "J4" H 4608 4631 50  0000 C CNN
F 1 "Conn_01x10_Male" H 4608 4540 50  0000 C CNN
F 2 "" H 4500 4050 50  0001 C CNN
F 3 "~" H 4500 4050 50  0001 C CNN
	1    4500 4050
	1    0    0    -1  
$EndComp
Text Notes 4200 3000 0    50   ~ 0
V0
Text Notes 4200 3100 0    50   ~ 0
RS
Text Notes 4200 3200 0    50   ~ 0
R/W
Text Notes 4200 3300 0    50   ~ 0
E
Text Notes 4200 4500 0    50   ~ 0
LED-
Text Notes 4200 4600 0    50   ~ 0
LED+
$Comp
L power:GND #PWR0119
U 1 1 5E7DC996
P 5800 2400
F 0 "#PWR0119" H 5800 2150 50  0001 C CNN
F 1 "GND" H 5805 2227 50  0000 C CNN
F 2 "" H 5800 2400 50  0001 C CNN
F 3 "" H 5800 2400 50  0001 C CNN
	1    5800 2400
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5E7E4239
P 5300 2650
AR Path="/5E7E4239" Ref="C?"  Part="1" 
AR Path="/5E7CFAFC/5E7E4239" Ref="C7"  Part="1" 
F 0 "C7" H 5415 2787 50  0000 L CNN
F 1 "100n" H 5415 2696 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5338 2500 50  0001 C CNN
F 3 "~" H 5300 2650 50  0001 C CNN
F 4 "25V" H 5415 2605 50  0000 L CNN "Champ4"
F 5 "X7R" H 5415 2514 50  0000 L CNN "Champ5"
	1    5300 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM 10K1
U 1 1 5E7DEAB7
P 6950 2650
F 0 "10K1" H 6880 2696 50  0000 R CNN
F 1 "R_POT_TRIM" H 7450 2850 50  0000 R CNN
F 2 "" H 6950 2650 50  0001 C CNN
F 3 "~" H 6950 2650 50  0001 C CNN
	1    6950 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7EC9B4
P 5800 2650
AR Path="/5E7EC9B4" Ref="C?"  Part="1" 
AR Path="/5E7CFAFC/5E7EC9B4" Ref="C8"  Part="1" 
F 0 "C8" H 5915 2787 50  0000 L CNN
F 1 "470n" H 5915 2696 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5838 2500 50  0001 C CNN
F 3 "~" H 5800 2650 50  0001 C CNN
F 4 "25V" H 5915 2605 50  0000 L CNN "Champ4"
F 5 "X7R" H 5915 2514 50  0000 L CNN "Champ5"
	1    5800 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C9
U 1 1 5E7EE2A7
P 6300 2650
F 0 "C9" H 6182 2559 50  0000 R CNN
F 1 "220u" H 6182 2650 50  0000 R CNN
F 2 "" H 6338 2500 50  0001 C CNN
F 3 "~" H 6300 2650 50  0001 C CNN
F 4 "25V" H 6182 2741 50  0000 R CNN "Champ4"
	1    6300 2650
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 2750 5050 2450
Wire Wire Line
	5800 2450 5800 2500
Wire Wire Line
	4700 2750 5050 2750
Wire Wire Line
	5800 2450 5800 2400
Connection ~ 5800 2450
Wire Wire Line
	5800 2450 6300 2450
Wire Wire Line
	6300 2450 6300 2500
Wire Wire Line
	5300 2450 5300 2500
Connection ~ 5300 2450
Wire Wire Line
	5300 2450 5800 2450
Wire Wire Line
	6300 2800 6300 2850
Connection ~ 6300 2850
Wire Wire Line
	5800 2800 5800 2850
Connection ~ 5800 2850
Wire Wire Line
	5800 2850 6300 2850
Wire Wire Line
	5300 2800 5300 2850
Connection ~ 5300 2850
Wire Wire Line
	5300 2850 5800 2850
Wire Wire Line
	4700 2850 5300 2850
Wire Wire Line
	5050 2450 5300 2450
Wire Wire Line
	6300 2450 6950 2450
Wire Wire Line
	6950 2450 6950 2500
Connection ~ 6300 2450
Wire Wire Line
	6950 2850 6950 2800
Wire Wire Line
	6300 2850 6950 2850
Connection ~ 6950 2850
Wire Wire Line
	7650 2950 7650 2650
Wire Wire Line
	7650 2650 7100 2650
Wire Wire Line
	4700 2950 7650 2950
Wire Wire Line
	7100 2850 6950 2850
$Comp
L power:+5V #PWR0120
U 1 1 5E7DD692
P 7100 2850
F 0 "#PWR0120" H 7100 2700 50  0001 C CNN
F 1 "+5V" V 7115 2978 50  0000 L CNN
F 2 "" H 7100 2850 50  0001 C CNN
F 3 "" H 7100 2850 50  0001 C CNN
	1    7100 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 3050 5050 3050
Wire Wire Line
	4700 3150 5050 3150
Wire Wire Line
	4700 3250 5050 3250
Wire Wire Line
	4700 3650 5050 3650
Wire Wire Line
	4700 3750 5050 3750
Wire Wire Line
	4700 3850 5050 3850
Wire Wire Line
	4700 3950 5050 3950
Wire Wire Line
	4700 4050 5050 4050
Wire Wire Line
	4700 4150 5050 4150
Wire Wire Line
	4700 4250 5050 4250
Wire Wire Line
	4700 4350 5050 4350
Wire Wire Line
	4700 4550 4850 4550
Text HLabel 5050 3050 2    50   Input ~ 0
DISPLAY_RS
Text HLabel 5050 3150 2    50   Input ~ 0
DISPLAY_RW
Text HLabel 5050 3250 2    50   Input ~ 0
DISPLAY_E
Text HLabel 5050 3650 2    50   BiDi ~ 0
DISPLAY_DB0
Text HLabel 5050 3750 2    50   BiDi ~ 0
DISPLAY_DB1
Text HLabel 5050 3850 2    50   BiDi ~ 0
DISPLAY_DB2
Text HLabel 5050 3950 2    50   BiDi ~ 0
DISPLAY_DB3
Text HLabel 5050 4050 2    50   BiDi ~ 0
DISPLAY_DB4
Text HLabel 5050 4150 2    50   BiDi ~ 0
DISPLAY_DB5
Text HLabel 5050 4250 2    50   BiDi ~ 0
DISPLAY_DB6
Text HLabel 5050 4350 2    50   BiDi ~ 0
DISPLAY_DB7
$Comp
L power:+5V #PWR0121
U 1 1 5E821DC4
P 4850 4550
F 0 "#PWR0121" H 4850 4400 50  0001 C CNN
F 1 "+5V" V 4865 4678 50  0000 L CNN
F 2 "" H 4850 4550 50  0001 C CNN
F 3 "" H 4850 4550 50  0001 C CNN
	1    4850 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E82967A
P 5500 4850
AR Path="/5E7ACE5B/5E82967A" Ref="R?"  Part="1" 
AR Path="/5E82967A" Ref="R?"  Part="1" 
AR Path="/5E7CFAFC/5E82967A" Ref="R6"  Part="1" 
F 0 "R6" H 5430 4804 50  0000 R CNN
F 1 "12" H 5430 4895 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5430 4850 50  0001 C CNN
F 3 "~" H 5500 4850 50  0001 C CNN
	1    5500 4850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5E82B8E8
P 5650 5850
F 0 "#PWR0122" H 5650 5600 50  0001 C CNN
F 1 "GND" H 5655 5677 50  0000 C CNN
F 2 "" H 5650 5850 50  0001 C CNN
F 3 "" H 5650 5850 50  0001 C CNN
	1    5650 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E82D0F5
P 6150 5600
AR Path="/5E7ACE5B/5E82D0F5" Ref="R?"  Part="1" 
AR Path="/5E82D0F5" Ref="R?"  Part="1" 
AR Path="/5E7CFAFC/5E82D0F5" Ref="R8"  Part="1" 
F 0 "R8" H 6220 5646 50  0000 L CNN
F 1 "10K" H 6220 5555 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 6080 5600 50  0001 C CNN
F 3 "~" H 6150 5600 50  0001 C CNN
	1    6150 5600
	1    0    0    -1  
$EndComp
Text HLabel 6500 5400 2    50   Input ~ 0
DISPLAY_BACKLIGHT
Wire Wire Line
	5650 5600 5650 5800
$Comp
L Device:R R?
U 1 1 5E836C01
P 5800 4850
AR Path="/5E7ACE5B/5E836C01" Ref="R?"  Part="1" 
AR Path="/5E836C01" Ref="R?"  Part="1" 
AR Path="/5E7CFAFC/5E836C01" Ref="R7"  Part="1" 
F 0 "R7" H 5730 4804 50  0000 R CNN
F 1 "12" H 5730 4895 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5730 4850 50  0001 C CNN
F 3 "~" H 5800 4850 50  0001 C CNN
	1    5800 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5650 4450 5650 4650
Wire Wire Line
	4700 4450 5650 4450
Wire Wire Line
	5500 4700 5500 4650
Wire Wire Line
	5500 4650 5650 4650
Wire Wire Line
	5800 4700 5800 4650
Wire Wire Line
	5800 4650 5650 4650
Connection ~ 5650 4650
Wire Wire Line
	5500 5000 5500 5050
Wire Wire Line
	5500 5050 5650 5050
Wire Wire Line
	5800 5050 5800 5000
Connection ~ 5650 5050
Wire Wire Line
	5650 5050 5800 5050
Text Notes 6400 4950 0    50   ~ 0
Backlight leds forward voltage is about 4 to 4.5V.\nBacklight leds maximum current is 200mA.\nWith 6 ohm resistor, maximum current will be\nbetween (5-4)/6 = 166mA and (5-4.5)/6 = 83mA.\nResistors dissipated power is between\n(5-4)²/6 = 166mW and (5-4.5)²/6 = 42mW,\nso allow up to 500mW to be dissipated to be sure.
$Comp
L Transistor_FET:DMG3414U Q1
U 1 1 5E7C7532
P 5750 5400
F 0 "Q1" H 5956 5446 50  0000 L CNN
F 1 "DMG3414U" H 5956 5355 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5950 5325 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/ds31739.pdf" H 5750 5400 50  0001 L CNN
	1    5750 5400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5650 5800 6150 5800
Wire Wire Line
	6150 5800 6150 5750
Connection ~ 5650 5800
Wire Wire Line
	5650 5800 5650 5850
Wire Wire Line
	5950 5400 6150 5400
Wire Wire Line
	6150 5400 6150 5450
Wire Wire Line
	6150 5400 6500 5400
Connection ~ 6150 5400
Wire Wire Line
	5650 5050 5650 5200
$EndSCHEMATC
