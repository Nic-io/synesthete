EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R3
U 1 1 61B9D083
P 1900 3850
F 0 "R3" H 1970 3896 50  0000 L CNN
F 1 "R" H 1970 3805 50  0000 L CNN
F 2 "" V 1830 3850 50  0001 C CNN
F 3 "~" H 1900 3850 50  0001 C CNN
	1    1900 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 61B9D125
P 2500 3900
F 0 "C3" H 2618 3946 50  0000 L CNN
F 1 "CP" H 2618 3855 50  0000 L CNN
F 2 "" H 2538 3750 50  0001 C CNN
F 3 "~" H 2500 3900 50  0001 C CNN
	1    2500 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 61B9D1AC
P 2400 3200
F 0 "RV1" H 2330 3246 50  0000 R CNN
F 1 "R_POT" H 2330 3155 50  0000 R CNN
F 2 "" H 2400 3200 50  0001 C CNN
F 3 "~" H 2400 3200 50  0001 C CNN
	1    2400 3200
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM358 U1
U 1 1 61B9D319
P 3550 3400
F 0 "U1" H 3550 3767 50  0000 C CNN
F 1 "LM358" H 3550 3676 50  0000 C CNN
F 2 "" H 3550 3400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 3550 3400 50  0001 C CNN
	1    3550 3400
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0101
U 1 1 61B9D4CB
P 1450 1200
F 0 "#PWR0101" H 1450 1050 50  0001 C CNN
F 1 "VCC" H 1467 1373 50  0000 C CNN
F 2 "" H 1450 1200 50  0001 C CNN
F 3 "" H 1450 1200 50  0001 C CNN
	1    1450 1200
	1    0    0    -1  
$EndComp
$Comp
L power:VEE #PWR0102
U 1 1 61B9D538
P 1450 2150
F 0 "#PWR0102" H 1450 2000 50  0001 C CNN
F 1 "VEE" H 1468 2323 50  0000 C CNN
F 2 "" H 1450 2150 50  0001 C CNN
F 3 "" H 1450 2150 50  0001 C CNN
	1    1450 2150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 61B9D5DE
P 2500 1650
F 0 "#PWR0103" H 2500 1400 50  0001 C CNN
F 1 "GND" H 2505 1477 50  0000 C CNN
F 2 "" H 2500 1650 50  0001 C CNN
F 3 "" H 2500 1650 50  0001 C CNN
	1    2500 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 61B9D5F8
P 1450 1450
F 0 "R1" H 1520 1496 50  0000 L CNN
F 1 "R" H 1520 1405 50  0000 L CNN
F 2 "" V 1380 1450 50  0001 C CNN
F 3 "~" H 1450 1450 50  0001 C CNN
	1    1450 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 61B9D64C
P 1450 1900
F 0 "R2" H 1520 1946 50  0000 L CNN
F 1 "R" H 1520 1855 50  0000 L CNN
F 2 "" V 1380 1900 50  0001 C CNN
F 3 "~" H 1450 1900 50  0001 C CNN
	1    1450 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 61B9D676
P 1950 1450
F 0 "C1" H 2068 1496 50  0000 L CNN
F 1 "CP" H 2068 1405 50  0000 L CNN
F 2 "" H 1988 1300 50  0001 C CNN
F 3 "~" H 1950 1450 50  0001 C CNN
	1    1950 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 61B9D6DA
P 1950 1900
F 0 "C2" H 2068 1946 50  0000 L CNN
F 1 "CP" H 2068 1855 50  0000 L CNN
F 2 "" H 1988 1750 50  0001 C CNN
F 3 "~" H 1950 1900 50  0001 C CNN
	1    1950 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1200 1450 1300
Wire Wire Line
	1450 1600 1450 1650
Wire Wire Line
	1450 2050 1450 2150
Wire Wire Line
	1950 1300 1450 1300
Connection ~ 1450 1300
Wire Wire Line
	1950 2050 1450 2050
Connection ~ 1450 2050
Wire Wire Line
	1950 1600 1950 1750
Wire Wire Line
	1450 1650 2500 1650
Connection ~ 1450 1650
Wire Wire Line
	1450 1650 1450 1750
$Comp
L Connector:Conn_01x10_Male J?
U 1 1 61B9DF50
P 8900 4000
F 0 "J?" H 9006 4578 50  0000 C CNN
F 1 "Conn_01x10_Male" H 9006 4487 50  0000 C CNN
F 2 "" H 8900 4000 50  0001 C CNN
F 3 "~" H 8900 4000 50  0001 C CNN
	1    8900 4000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J?
U 1 1 61B9E037
P 8900 5000
F 0 "J?" H 9006 5478 50  0000 C CNN
F 1 "Conn_01x08_Male" H 9006 5387 50  0000 C CNN
F 2 "" H 8900 5000 50  0001 C CNN
F 3 "~" H 8900 5000 50  0001 C CNN
	1    8900 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 61B9E1DA
P 7350 5100
F 0 "J?" H 7456 5478 50  0000 C CNN
F 1 "Conn_01x06_Male" H 7456 5387 50  0000 C CNN
F 2 "" H 7350 5100 50  0001 C CNN
F 3 "~" H 7350 5100 50  0001 C CNN
	1    7350 5100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10_Female J?
U 1 1 61B9E2A6
P 7150 1100
F 0 "J?" H 7177 1076 50  0000 L CNN
F 1 "Conn_01x10_Female" H 7177 985 50  0000 L CNN
F 2 "" H 7150 1100 50  0001 C CNN
F 3 "~" H 7150 1100 50  0001 C CNN
	1    7150 1100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Female J?
U 1 1 61B9E436
P 4650 950
F 0 "J?" H 4677 976 50  0000 L CNN
F 1 "Conn_01x05_Female" H 4677 885 50  0000 L CNN
F 2 "" H 4650 950 50  0001 C CNN
F 3 "~" H 4650 950 50  0001 C CNN
	1    4650 950 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J?
U 1 1 61B9E752
P 7350 4300
F 0 "J?" H 7456 4778 50  0000 C CNN
F 1 "Conn_01x08_Male" H 7456 4687 50  0000 C CNN
F 2 "" H 7350 4300 50  0001 C CNN
F 3 "~" H 7350 4300 50  0001 C CNN
	1    7350 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61B9ED87
P 7800 4200
F 0 "#PWR?" H 7800 4050 50  0001 C CNN
F 1 "+3.3V" H 7815 4373 50  0000 C CNN
F 2 "" H 7800 4200 50  0001 C CNN
F 3 "" H 7800 4200 50  0001 C CNN
	1    7800 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4200 7800 4200
Wire Wire Line
	7550 4600 7550 4500
$Comp
L power:GND #PWR?
U 1 1 61B9EE95
P 7800 4500
F 0 "#PWR?" H 7800 4250 50  0001 C CNN
F 1 "GND" H 7805 4327 50  0000 C CNN
F 2 "" H 7800 4500 50  0001 C CNN
F 3 "" H 7800 4500 50  0001 C CNN
	1    7800 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4500 7800 4500
Connection ~ 7550 4500
Text Label 7750 4900 0    50   ~ 0
y+
Text Label 7750 5000 0    50   ~ 0
x+
Text Label 7750 5400 0    50   ~ 0
x-
Text Label 7750 5300 0    50   ~ 0
y-
Wire Wire Line
	7550 4900 7750 4900
Wire Wire Line
	7550 5000 7750 5000
Wire Wire Line
	7550 5300 7750 5300
Wire Wire Line
	7550 5400 7750 5400
$EndSCHEMATC
