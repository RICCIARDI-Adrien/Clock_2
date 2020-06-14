# Clock 2

![Clock 2](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Clock_Front_View.jpg)

Improved digital clock. First generation is [here](https://github.com/RICCIARDI-Adrien/Clock).  

New features :
* Improved temperature sensor.
* Humidity sensor.
* Pressure sensor.
* High accuracy temperature-compensated RTC.
* More compact, more industrial and more robust casing.
* A really simple interface made of 3 buttons to configure all clock settings (no more configuration through USB).

## Firmware

Microchip XC8 version 2.20 or above is required to build the firmware. Previous XC8 versions will work but the Celsius degree unit won't be displayed. This is due to a bug in XC8 escaped string characters parsing.

On a Linux system with XC8 installed and added to `PATH`, enter the following lines :
```
cd <repository directory>/Software
make
```

Resulting firmware file is `Firmware.hex`.

## Photo gallery

### PCB

![Naked PCB front](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Naked_PCB_Front.jpg)
![Naked PCB back](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Naked_PCB_Back.jpg)

![PCB front](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/PCB_Front.jpg)
![PCB back](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/PCB_Back.jpg)

### Display

![Display front](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Display_Front.jpg)
![Display back](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Display_Back.jpg)

### Casing

![Casing steel plates](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Casing_Steel_Plates.jpg)

### Finished clock

![Clock front view](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Clock_Front_View.jpg)

Alarm stopping and display backlight button :
![Clock top view](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Clock_Top_View.jpg)

Power supply USB connector :
![Clock back view](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Clock_Back_View.jpg)

Bottom protection pads :
![Clock bottom view](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Clock_Bottom_View.jpg)

Internal view (backup battery not yet fitted) :
![Clock internal view](https://github.com/RICCIARDI-Adrien/Clock_2/blob/master/Resources/Pictures/Clock_Internal_View.jpg)

## Views

### Main

```
+--------------------+
|      11:16:23      |
|   Jeu 19/03/2020   |
| T:23°C  P:1112mBar |
| H:68%   A:OFF      |
+--------------------+
```

'A' stands for a bell symbol representing the current alarm state (enabled or disabled).

### Statistics

Press `+` button to reach temperature view.  
Press `-` button to reach humidity view (these views can be accessed in reverse order).

```
+--------------------+
|---- TEMPERATURE ---|
|Minimum : 23°C      |
|Maximum : 15°C      |
|                    |
+--------------------+
```

Press `Set` or `-` button to return to main view.  
Press `+` button to go to pressure view.

```
+--------------------+
|----- PRESSION -----|
|Minimum : 980mbar   |
|Maximum : 1002mbar  |
|                    |
+--------------------+
```

Press `Set` to immediately return to main view.  
Press `-` button to return to temperature view.  
Press `+` button to go to humidity view.

```
+--------------------+
|----- HUMIDITE -----|
|Minimum : 57%       |
|Maximum : 59%       |
|                    |
+--------------------+
```

Press `Set` or `+` button to return to main view.  
Press `-` button to return to pression view.

### Settings

Press `Set` button to reach this view.

```
+--------------------+
|-> Régler alarme    |
|   Régler heure     |
|   Régler date      |
|       Retour       |
+--------------------+
```
Select a menu entry using `+` and `-` buttons, then press `Set` button.

### Set alarm

```
+--------------------+
|--- HEURE ALARME ---|
| Heure : 7          |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose an hour, then press `Set` button to continue.

```
+--------------------+
|-- MINUTES ALARME --|
| Minutes : 30       |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose minutes value, then press `Set` button to return to settings menu.

### Set time

```
+--------------------+
|--- REGLER HEURE ---|
| Heure : 11         |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose an hour, then press `Set` button to continue.

```
+--------------------+
|-- REGLER MINUTES --|
| Minutes : 26       |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose minutes value, then press `Set` button to continue.

```
+--------------------+
|- REGLER SECONDES --|
| Secondes : 47      |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose seconds value, then press `Set` button to return to settings menu.

### Set date

```
+--------------------+
|--- REGLER JOUR ----|
| Jour : 14          |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose a day, then press `Set` button to continue.

```
+--------------------+
|--- REGLER MOIS ----|
| Mois : 3           |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose a month, then press `Set` button to continue.

```
+--------------------+
|--- REGLER ANNEE ---|
| Année : 2020       |
| + et - pour régler |
| SET pour continuer |
+--------------------+
```
Press `+` and `-` buttons to choose a year, then press `Set` button to return to settings menu.
