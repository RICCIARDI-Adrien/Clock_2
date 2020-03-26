EESchema Schematic File Version 4
LIBS:Motherboard-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title "All user interface buttons"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Switch:SW_Push SW?
U 1 1 5E7DE32A
P 2400 1550
AR Path="/5E7DE32A" Ref="SW?"  Part="1" 
AR Path="/5E7CE147/5E7DE32A" Ref="SW2"  Part="1" 
F 0 "SW2" V 2354 1698 50  0000 L CNN
F 1 "Button_Minus" V 2445 1698 50  0000 L CNN
F 2 "Button_Switch_THT:SW_Tactile_SKHH_Angled" H 2400 1750 50  0001 C CNN
F 3 "~" H 2400 1750 50  0001 C CNN
	1    2400 1550
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E7DE330
P 1700 1550
AR Path="/5E7DE330" Ref="SW?"  Part="1" 
AR Path="/5E7CE147/5E7DE330" Ref="SW1"  Part="1" 
F 0 "SW1" V 1654 1698 50  0000 L CNN
F 1 "Button_Plus" V 1745 1698 50  0000 L CNN
F 2 "Button_Switch_THT:SW_Tactile_SKHH_Angled" H 1700 1750 50  0001 C CNN
F 3 "~" H 1700 1750 50  0001 C CNN
	1    1700 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 2350 3600 2350
Wire Wire Line
	2400 1350 2400 1300
Wire Wire Line
	2400 1300 1700 1300
Wire Wire Line
	1700 1300 1700 1350
$Comp
L Device:C C?
U 1 1 5E7DE33C
P 1700 2700
AR Path="/5E7DE33C" Ref="C?"  Part="1" 
AR Path="/5E7CE147/5E7DE33C" Ref="C10"  Part="1" 
F 0 "C10" H 1815 2563 50  0000 L CNN
F 1 "100n" H 1815 2654 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1738 2550 50  0001 C CNN
F 3 "~" H 1700 2700 50  0001 C CNN
F 4 "25V" H 1815 2745 50  0000 L CNN "Champ4"
F 5 "X7R" H 1815 2836 50  0000 L CNN "Champ5"
	1    1700 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5E7DE344
P 2400 2700
AR Path="/5E7DE344" Ref="C?"  Part="1" 
AR Path="/5E7CE147/5E7DE344" Ref="C11"  Part="1" 
F 0 "C11" H 2285 2563 50  0000 R CNN
F 1 "100n" H 2285 2654 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2438 2550 50  0001 C CNN
F 3 "~" H 2400 2700 50  0001 C CNN
F 4 "25V" H 2285 2745 50  0000 R CNN "Champ4"
F 5 "X7R" H 2285 2836 50  0000 R CNN "Champ5"
	1    2400 2700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7DE34A
P 2050 3000
AR Path="/5E7DE34A" Ref="#PWR?"  Part="1" 
AR Path="/5E7CE147/5E7DE34A" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 2050 2750 50  0001 C CNN
F 1 "GND" H 2055 2827 50  0000 C CNN
F 2 "" H 2050 3000 50  0001 C CNN
F 3 "" H 2050 3000 50  0001 C CNN
	1    2050 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2850 1700 2950
Wire Wire Line
	2400 2950 2400 2850
$Comp
L power:GND #PWR?
U 1 1 5E7DE352
P 1450 1400
AR Path="/5E7DE352" Ref="#PWR?"  Part="1" 
AR Path="/5E7CE147/5E7DE352" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 1450 1150 50  0001 C CNN
F 1 "GND" H 1455 1227 50  0000 C CNN
F 2 "" H 1450 1400 50  0001 C CNN
F 3 "" H 1450 1400 50  0001 C CNN
	1    1450 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1400 1450 1300
Wire Wire Line
	2400 1750 2400 2350
Wire Wire Line
	2400 2350 2400 2550
Connection ~ 2400 2350
Wire Wire Line
	1700 2550 1700 2450
Wire Wire Line
	1700 2450 1700 1750
Connection ~ 1700 2450
Wire Wire Line
	1700 2950 2050 2950
Wire Wire Line
	1450 1300 1700 1300
Connection ~ 1700 1300
Wire Wire Line
	2050 3000 2050 2950
Connection ~ 2050 2950
Wire Wire Line
	2050 2950 2400 2950
$Comp
L Device:R R?
U 1 1 5E7E26D1
P 3600 2000
AR Path="/5E7ACE5B/5E7E26D1" Ref="R?"  Part="1" 
AR Path="/5E7E26D1" Ref="R?"  Part="1" 
AR Path="/5E7CE147/5E7E26D1" Ref="R12"  Part="1" 
F 0 "R12" H 3530 1954 50  0000 R CNN
F 1 "10K" H 3530 2045 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3530 2000 50  0001 C CNN
F 3 "~" H 3600 2000 50  0001 C CNN
	1    3600 2000
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7E26D7
P 3400 1750
AR Path="/5E7E26D7" Ref="#PWR?"  Part="1" 
AR Path="/5E7CE147/5E7E26D7" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 3400 1600 50  0001 C CNN
F 1 "+5V" H 3415 1923 50  0000 C CNN
F 2 "" H 3400 1750 50  0001 C CNN
F 3 "" H 3400 1750 50  0001 C CNN
	1    3400 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E7E26DD
P 3200 2000
AR Path="/5E7ACE5B/5E7E26DD" Ref="R?"  Part="1" 
AR Path="/5E7E26DD" Ref="R?"  Part="1" 
AR Path="/5E7CE147/5E7E26DD" Ref="R11"  Part="1" 
F 0 "R11" H 3130 1954 50  0000 R CNN
F 1 "10K" H 3130 2045 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3130 2000 50  0001 C CNN
F 3 "~" H 3200 2000 50  0001 C CNN
	1    3200 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 2450 3200 2150
Wire Wire Line
	3600 2150 3600 2350
Wire Wire Line
	3200 1850 3200 1800
Wire Wire Line
	3200 1800 3400 1800
Wire Wire Line
	3400 1800 3400 1750
Wire Wire Line
	3400 1800 3600 1800
Wire Wire Line
	3600 1800 3600 1850
Connection ~ 3400 1800
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 5E7E7CAA
P 9750 2400
AR Path="/5E7E7CAA" Ref="J?"  Part="1" 
AR Path="/5E7CE147/5E7E7CAA" Ref="J5"  Part="1" 
F 0 "J5" H 9850 2600 50  0000 R CNN
F 1 "Buttons" H 9850 2700 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9750 2400 50  0001 C CNN
F 3 "~" H 9750 2400 50  0001 C CNN
	1    9750 2400
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7E7CB0
P 8850 1700
AR Path="/5E7E7CB0" Ref="#PWR?"  Part="1" 
AR Path="/5E7CE147/5E7E7CB0" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 8850 1550 50  0001 C CNN
F 1 "+5V" H 8865 1873 50  0000 C CNN
F 2 "" H 8850 1700 50  0001 C CNN
F 3 "" H 8850 1700 50  0001 C CNN
	1    8850 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 2500 9550 2500
Wire Wire Line
	9550 2300 9500 2300
Wire Wire Line
	9500 2300 9500 2500
Text Notes 9800 2300 0    50   ~ 0
Alarm button
Text Notes 9800 2500 0    50   ~ 0
Backlight button
Wire Wire Line
	7700 2200 8600 2200
Wire Wire Line
	7700 2400 9100 2400
$Comp
L power:GND #PWR?
U 1 1 5E7E7CBF
P 9100 2950
AR Path="/5E7E7CBF" Ref="#PWR?"  Part="1" 
AR Path="/5E7CE147/5E7E7CBF" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 9100 2700 50  0001 C CNN
F 1 "GND" H 9105 2777 50  0000 C CNN
F 2 "" H 9100 2950 50  0001 C CNN
F 3 "" H 9100 2950 50  0001 C CNN
	1    9100 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E7E7CC5
P 8600 1950
AR Path="/5E7ACE5B/5E7E7CC5" Ref="R?"  Part="1" 
AR Path="/5E7E7CC5" Ref="R?"  Part="1" 
AR Path="/5E7CE147/5E7E7CC5" Ref="R13"  Part="1" 
F 0 "R13" H 8530 1904 50  0000 R CNN
F 1 "10K" H 8530 1995 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8530 1950 50  0001 C CNN
F 3 "~" H 8600 1950 50  0001 C CNN
	1    8600 1950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5E7E7CCB
P 9100 1950
AR Path="/5E7ACE5B/5E7E7CCB" Ref="R?"  Part="1" 
AR Path="/5E7E7CCB" Ref="R?"  Part="1" 
AR Path="/5E7CE147/5E7E7CCB" Ref="R14"  Part="1" 
F 0 "R14" H 9030 1904 50  0000 R CNN
F 1 "10K" H 9030 1995 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 9030 1950 50  0001 C CNN
F 3 "~" H 9100 1950 50  0001 C CNN
	1    9100 1950
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5E7E7CD3
P 9100 2650
AR Path="/5E7E7CD3" Ref="C?"  Part="1" 
AR Path="/5E7CE147/5E7E7CD3" Ref="C14"  Part="1" 
F 0 "C14" H 8985 2513 50  0000 R CNN
F 1 "100n" H 8985 2604 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9138 2500 50  0001 C CNN
F 3 "~" H 9100 2650 50  0001 C CNN
F 4 "25V" H 8985 2695 50  0000 R CNN "Champ4"
F 5 "X7R" H 8985 2786 50  0000 R CNN "Champ5"
	1    9100 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5E7E7CDB
P 8600 2650
AR Path="/5E7E7CDB" Ref="C?"  Part="1" 
AR Path="/5E7CE147/5E7E7CDB" Ref="C13"  Part="1" 
F 0 "C13" H 8485 2513 50  0000 R CNN
F 1 "100n" H 8485 2604 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8638 2500 50  0001 C CNN
F 3 "~" H 8600 2650 50  0001 C CNN
F 4 "25V" H 8485 2695 50  0000 R CNN "Champ4"
F 5 "X7R" H 8485 2786 50  0000 R CNN "Champ5"
	1    8600 2650
	-1   0    0    1   
$EndComp
Wire Wire Line
	8600 2100 8600 2200
Connection ~ 8600 2200
Wire Wire Line
	8600 2200 9550 2200
Wire Wire Line
	8600 2200 8600 2500
Wire Wire Line
	9100 2100 9100 2400
Connection ~ 9100 2400
Wire Wire Line
	9100 2400 9550 2400
Wire Wire Line
	9100 2500 9100 2400
Wire Wire Line
	8600 2800 8600 2900
Wire Wire Line
	8600 2900 9100 2900
Wire Wire Line
	9100 2900 9100 2800
Wire Wire Line
	9500 2900 9500 2500
Connection ~ 9500 2500
Wire Wire Line
	9100 2900 9500 2900
Connection ~ 9100 2900
Wire Wire Line
	9100 2950 9100 2900
Wire Wire Line
	8600 1800 8600 1750
Wire Wire Line
	8600 1750 8850 1750
Wire Wire Line
	8850 1750 8850 1700
Wire Wire Line
	8850 1750 9100 1750
Wire Wire Line
	9100 1750 9100 1800
Connection ~ 8850 1750
Text HLabel 7700 2200 0    50   Output ~ 0
BUTTON_ALARM
Text HLabel 7700 2400 0    50   Output ~ 0
BUTTON_BACKLIGHT
Connection ~ 3200 2450
Wire Wire Line
	3200 2450 1700 2450
Connection ~ 3600 2350
Wire Wire Line
	3200 2450 4400 2450
Wire Wire Line
	3600 2350 4400 2350
Text HLabel 4400 2350 2    50   Output ~ 0
BUTTON_MINUS
Text HLabel 4400 2450 2    50   Output ~ 0
BUTTON_PLUS
$Comp
L Switch:SW_Push SW?
U 1 1 5E7D585D
P 6000 4600
AR Path="/5E7D585D" Ref="SW?"  Part="1" 
AR Path="/5E7CE147/5E7D585D" Ref="SW3"  Part="1" 
F 0 "SW3" V 6046 4748 50  0000 L CNN
F 1 "Button_Settings" V 5955 4748 50  0000 L CNN
F 2 "Button_Switch_THT:SW_Tactile_SKHH_Angled" H 6000 4800 50  0001 C CNN
F 3 "~" H 6000 4800 50  0001 C CNN
	1    6000 4600
	0    1    -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E7D5863
P 5450 4100
AR Path="/5E7ACE5B/5E7D5863" Ref="R?"  Part="1" 
AR Path="/5E7D5863" Ref="R?"  Part="1" 
AR Path="/5E7CE147/5E7D5863" Ref="R15"  Part="1" 
F 0 "R15" H 5380 4054 50  0000 R CNN
F 1 "10K" H 5380 4145 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5380 4100 50  0001 C CNN
F 3 "~" H 5450 4100 50  0001 C CNN
	1    5450 4100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E7D5869
P 5750 4900
AR Path="/5E7D5869" Ref="#PWR?"  Part="1" 
AR Path="/5E7CE147/5E7D5869" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 5750 4650 50  0001 C CNN
F 1 "GND" H 5755 4727 50  0000 C CNN
F 2 "" H 5750 4900 50  0001 C CNN
F 3 "" H 5750 4900 50  0001 C CNN
	1    5750 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E7D586F
P 5450 3900
AR Path="/5E7D586F" Ref="#PWR?"  Part="1" 
AR Path="/5E7CE147/5E7D586F" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 5450 3750 50  0001 C CNN
F 1 "+5V" H 5465 4073 50  0000 C CNN
F 2 "" H 5450 3900 50  0001 C CNN
F 3 "" H 5450 3900 50  0001 C CNN
	1    5450 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E7D5878
P 5450 4600
AR Path="/5E7D5878" Ref="C?"  Part="1" 
AR Path="/5E7CE147/5E7D5878" Ref="C12"  Part="1" 
F 0 "C12" H 5335 4463 50  0000 R CNN
F 1 "100n" H 5335 4554 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5488 4450 50  0001 C CNN
F 3 "~" H 5450 4600 50  0001 C CNN
F 4 "25V" H 5335 4645 50  0000 R CNN "Champ4"
F 5 "X7R" H 5335 4736 50  0000 R CNN "Champ5"
	1    5450 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	5450 4750 5450 4850
Wire Wire Line
	5450 4850 5750 4850
Wire Wire Line
	5750 4850 5750 4900
Wire Wire Line
	5750 4850 6000 4850
Wire Wire Line
	6000 4850 6000 4800
Connection ~ 5750 4850
Wire Wire Line
	6000 4350 6000 4400
Wire Wire Line
	4900 4350 5450 4350
Wire Wire Line
	5450 4250 5450 4350
Connection ~ 5450 4350
Wire Wire Line
	5450 4350 6000 4350
Wire Wire Line
	5450 4350 5450 4450
Wire Wire Line
	5450 3900 5450 3950
Text HLabel 4900 4350 0    50   Output ~ 0
BUTTON_SETTINGS
$Comp
L Switches:Inverter_8013 SW4
U 1 1 5E7FA0CA
P 1850 5100
F 0 "SW4" H 2328 5146 50  0000 L CNN
F 1 "Inverter_8013" H 2328 5055 50  0000 L CNN
F 2 "Empty_Footprint:Empty_Footprint" H 1850 5100 50  0001 C CNN
F 3 "https://www.gotronic.fr/art-inverseur-unipolaire-8013-4172.htm" H 1850 5100 50  0001 C CNN
	1    1850 5100
	1    0    0    -1  
$EndComp
$Comp
L Switches:Push_Button_R1500 SW5
U 1 1 5E7FA7B1
P 1900 5850
F 0 "SW5" H 2328 5896 50  0000 L CNN
F 1 "Push_Button_R1500" H 2328 5805 50  0000 L CNN
F 2 "Empty_Footprint:Empty_Footprint" H 1900 5850 50  0001 C CNN
F 3 "https://www.gotronic.fr/art-bp-de-securite-r1500-4191.htm" H 1900 5850 50  0001 C CNN
	1    1900 5850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
