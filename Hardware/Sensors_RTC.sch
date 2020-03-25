EESchema Schematic File Version 4
LIBS:Motherboard-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title "Sensors and real-time clock"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 5E7B014E
P 8150 2350
AR Path="/5E7B014E" Ref="H?"  Part="1" 
AR Path="/5E7ACE5B/5E7B014E" Ref="H1"  Part="1" 
F 0 "H1" H 8250 2399 50  0000 L CNN
F 1 "MountingHole_Pad" H 8250 2308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_Pad" H 8150 2350 50  0001 C CNN
F 3 "~" H 8150 2350 50  0001 C CNN
	1    8150 2350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 5E7B0154
P 9150 2350
AR Path="/5E7B0154" Ref="H?"  Part="1" 
AR Path="/5E7ACE5B/5E7B0154" Ref="H2"  Part="1" 
F 0 "H2" H 9250 2399 50  0000 L CNN
F 1 "MountingHole_Pad" H 9250 2308 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_Pad" H 9150 2350 50  0001 C CNN
F 3 "~" H 9150 2350 50  0001 C CNN
	1    9150 2350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x07_Male J?
U 1 1 5E7B015A
P 8650 2850
AR Path="/5E7B015A" Ref="J?"  Part="1" 
AR Path="/5E7ACE5B/5E7B015A" Ref="J1"  Part="1" 
F 0 "J1" V 8485 2828 50  0000 C CNN
F 1 "Conn_01x07_Male" V 8576 2828 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 8650 2850 50  0001 C CNN
F 3 "~" H 8650 2850 50  0001 C CNN
	1    8650 2850
	0    -1   1    0   
$EndComp
Wire Notes Line
	10050 2050 10050 3200
Wire Notes Line
	10050 3200 7400 3200
Wire Notes Line
	7400 3200 7400 2050
Wire Notes Line
	7400 2050 10050 2050
Text Notes 7450 2150 0    50   ~ 0
Adafruit BME680
$Comp
L power:+5V #PWR?
U 1 1 5E7B0165
P 8350 3400
AR Path="/5E7B0165" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7B0165" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 8350 3250 50  0001 C CNN
F 1 "+5V" H 8365 3573 50  0000 C CNN
F 2 "" H 8350 3400 50  0001 C CNN
F 3 "" H 8350 3400 50  0001 C CNN
	1    8350 3400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7B016B
P 8550 3400
AR Path="/5E7B016B" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7B016B" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 8550 3150 50  0001 C CNN
F 1 "GND" H 8555 3227 50  0000 C CNN
F 2 "" H 8550 3400 50  0001 C CNN
F 3 "" H 8550 3400 50  0001 C CNN
	1    8550 3400
	1    0    0    -1  
$EndComp
NoConn ~ 8450 3050
$Comp
L power:GND #PWR?
U 1 1 5E7B0172
P 8150 2550
AR Path="/5E7B0172" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7B0172" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 8150 2300 50  0001 C CNN
F 1 "GND" H 8155 2377 50  0000 C CNN
F 2 "" H 8150 2550 50  0001 C CNN
F 3 "" H 8150 2550 50  0001 C CNN
	1    8150 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7B0178
P 9150 2550
AR Path="/5E7B0178" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7B0178" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 9150 2300 50  0001 C CNN
F 1 "GND" H 9155 2377 50  0000 C CNN
F 2 "" H 9150 2550 50  0001 C CNN
F 3 "" H 9150 2550 50  0001 C CNN
	1    9150 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 2550 9150 2450
Wire Wire Line
	8150 2550 8150 2450
Wire Wire Line
	8350 3050 8350 3300
$Comp
L Timer_RTC:DS3231M U2
U 1 1 5E7B0716
P 3450 4000
F 0 "U2" H 3650 3650 50  0000 C CNN
F 1 "DS3231M" H 3750 3550 50  0000 C CNN
F 2 "Package_SO:SOIC-16W_7.5x10.3mm_P1.27mm" H 3450 3400 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231.pdf" H 3720 4050 50  0001 C CNN
	1    3450 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7B71D3
P 3350 2950
AR Path="/5E7B71D3" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7B71D3" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 3350 2800 50  0001 C CNN
F 1 "+5V" H 3365 3123 50  0000 C CNN
F 2 "" H 3350 2950 50  0001 C CNN
F 3 "" H 3350 2950 50  0001 C CNN
	1    3350 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E7B7D0E
P 2400 3250
F 0 "C1" H 2285 3113 50  0000 R CNN
F 1 "100n" H 2285 3204 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2438 3100 50  0001 C CNN
F 3 "~" H 2400 3250 50  0001 C CNN
F 4 "25V" H 2285 3295 50  0000 R CNN "Champ4"
F 5 "X7R" H 2285 3386 50  0000 R CNN "Champ5"
	1    2400 3250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7BA8C5
P 3450 4450
AR Path="/5E7BA8C5" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7BA8C5" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 3450 4200 50  0001 C CNN
F 1 "GND" H 3455 4277 50  0000 C CNN
F 2 "" H 3450 4450 50  0001 C CNN
F 3 "" H 3450 4450 50  0001 C CNN
	1    3450 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E7BB22C
P 2900 3250
F 0 "C2" H 2785 3113 50  0000 R CNN
F 1 "100n" H 2785 3204 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2938 3100 50  0001 C CNN
F 3 "~" H 2900 3250 50  0001 C CNN
F 4 "25V" H 2785 3295 50  0000 R CNN "Champ4"
F 5 "X7R" H 2785 3386 50  0000 R CNN "Champ5"
	1    2900 3250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5E7BCF59
P 2600 4200
F 0 "R2" H 2670 4246 50  0000 L CNN
F 1 "1K" H 2670 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 2530 4200 50  0001 C CNN
F 3 "~" H 2600 4200 50  0001 C CNN
	1    2600 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E7BE463
P 2200 4200
F 0 "R1" H 2270 4246 50  0000 L CNN
F 1 "1K" H 2270 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 2130 4200 50  0001 C CNN
F 3 "~" H 2200 4200 50  0001 C CNN
	1    2200 4200
	1    0    0    -1  
$EndComp
NoConn ~ 2950 4200
$Comp
L power:GND #PWR?
U 1 1 5E7BE8CF
P 2650 3500
AR Path="/5E7BE8CF" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7BE8CF" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 2650 3250 50  0001 C CNN
F 1 "GND" H 2655 3327 50  0000 C CNN
F 2 "" H 2650 3500 50  0001 C CNN
F 3 "" H 2650 3500 50  0001 C CNN
	1    2650 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3600 3350 3050
Wire Wire Line
	2400 3100 2400 3050
Wire Wire Line
	2400 3050 2900 3050
Wire Wire Line
	2900 3050 2900 3100
Wire Wire Line
	2900 3050 3350 3050
Connection ~ 2900 3050
Connection ~ 3350 3050
Wire Wire Line
	3350 3050 3350 2950
Wire Wire Line
	2400 3400 2400 3450
Wire Wire Line
	2400 3450 2650 3450
Wire Wire Line
	2900 3450 2900 3400
Wire Wire Line
	2650 3450 2650 3500
Connection ~ 2650 3450
Wire Wire Line
	2650 3450 2900 3450
$Comp
L power:+5V #PWR?
U 1 1 5E7C118A
P 2400 4450
AR Path="/5E7C118A" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7C118A" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 2400 4300 50  0001 C CNN
F 1 "+5V" H 2415 4623 50  0000 C CNN
F 2 "" H 2400 4450 50  0001 C CNN
F 3 "" H 2400 4450 50  0001 C CNN
	1    2400 4450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 4350 2200 4400
Wire Wire Line
	2200 4400 2400 4400
Wire Wire Line
	2400 4400 2400 4450
Wire Wire Line
	2400 4400 2600 4400
Wire Wire Line
	2600 4400 2600 4350
Connection ~ 2400 4400
Wire Wire Line
	2950 3900 2600 3900
Wire Wire Line
	2600 3900 2600 4050
Wire Wire Line
	2200 3800 2200 4050
Wire Wire Line
	2200 3800 2950 3800
Wire Wire Line
	2200 3800 1650 3800
Connection ~ 2200 3800
Wire Wire Line
	2600 3900 1650 3900
Connection ~ 2600 3900
Wire Wire Line
	3450 4450 3450 4400
NoConn ~ 3950 3800
Text HLabel 1650 3800 0    50   Input ~ 0
RTC_SCL
Text HLabel 1650 3900 0    50   BiDi ~ 0
RTC_SDA
Wire Wire Line
	8650 4350 7700 4350
Wire Wire Line
	8750 4450 7700 4450
Wire Wire Line
	8850 4550 7700 4550
Wire Wire Line
	8950 4650 7700 4650
$Comp
L Device:C C3
U 1 1 5E7D259F
P 7900 3500
F 0 "C3" H 7785 3363 50  0000 R CNN
F 1 "100n" H 7785 3454 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7938 3350 50  0001 C CNN
F 3 "~" H 7900 3500 50  0001 C CNN
F 4 "25V" H 7785 3545 50  0000 R CNN "Champ4"
F 5 "X7R" H 7785 3636 50  0000 R CNN "Champ5"
	1    7900 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 3350 7900 3300
Wire Wire Line
	7900 3300 8350 3300
Wire Wire Line
	8350 3300 8350 3400
Connection ~ 8350 3300
$Comp
L power:GND #PWR?
U 1 1 5E7E1118
P 7900 3750
AR Path="/5E7E1118" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7E1118" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 7900 3500 50  0001 C CNN
F 1 "GND" H 7905 3577 50  0000 C CNN
F 2 "" H 7900 3750 50  0001 C CNN
F 3 "" H 7900 3750 50  0001 C CNN
	1    7900 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 3750 7900 3650
Wire Wire Line
	8650 3050 8650 4350
Wire Wire Line
	8750 3050 8750 4450
Wire Wire Line
	8850 3050 8850 4550
Wire Wire Line
	8950 3050 8950 4650
Text HLabel 7700 4350 0    50   Input ~ 0
BME680_SCK
Wire Wire Line
	8550 3050 8550 3400
Text HLabel 7700 4450 0    50   Output ~ 0
BME680_SDO
Text HLabel 7700 4550 0    50   Input ~ 0
BME680_SDI
Text HLabel 7700 4650 0    50   Input ~ 0
BME680_CS
$Comp
L Adafruit_BME680:Adafruit_BME680 U3
U 1 1 5E7A3D1F
P 8600 1250
F 0 "U3" H 9028 1296 50  0000 L CNN
F 1 "Adafruit_BME680" H 9028 1205 50  0000 L CNN
F 2 "Symbol:Symbol_Attention_CopperTop_Small" H 8600 1250 50  0001 C CNN
F 3 "" H 8600 1250 50  0001 C CNN
	1    8600 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery BT1
U 1 1 5E7A7D04
P 4300 3300
F 0 "BT1" H 4408 3346 50  0000 L CNN
F 1 "Battery" H 4408 3255 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_103_1x20mm" V 4300 3360 50  0001 C CNN
F 3 "~" V 4300 3360 50  0001 C CNN
	1    4300 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7AC503
P 4300 3550
AR Path="/5E7AC503" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7AC503" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 4300 3300 50  0001 C CNN
F 1 "GND" H 4305 3377 50  0000 C CNN
F 2 "" H 4300 3550 50  0001 C CNN
F 3 "" H 4300 3550 50  0001 C CNN
	1    4300 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3050 4300 3050
Wire Wire Line
	4300 3050 4300 3100
Wire Wire Line
	4300 3500 4300 3550
Wire Wire Line
	3450 3050 3450 3600
Text HLabel 4350 4100 2    50   Output ~ 0
RTC_1HZ
$Comp
L Device:R R5
U 1 1 5E7E2482
P 4150 4350
F 0 "R5" H 4220 4396 50  0000 L CNN
F 1 "1K" H 4220 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4080 4350 50  0001 C CNN
F 3 "~" H 4150 4350 50  0001 C CNN
	1    4150 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7E2996
P 4150 4600
AR Path="/5E7E2996" Ref="#PWR?"  Part="1" 
AR Path="/5E7ACE5B/5E7E2996" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 4150 4450 50  0001 C CNN
F 1 "+5V" H 4165 4773 50  0000 C CNN
F 2 "" H 4150 4600 50  0001 C CNN
F 3 "" H 4150 4600 50  0001 C CNN
	1    4150 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	4150 4200 4150 4100
Connection ~ 4150 4100
Wire Wire Line
	4150 4100 4350 4100
Wire Wire Line
	4150 4600 4150 4500
Wire Wire Line
	3950 4100 4150 4100
$EndSCHEMATC