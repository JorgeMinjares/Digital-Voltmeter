# **Digital-Voltmeter**
## **Description**
This program will emulate a voltmeter using the MSP432. In this program ADC will utilize in order to display the voltage onto an LCD; Timers will be used to run the ADC every 20ms, gathering a sample every 100ms to create a more precise reading. This voltmeter creates a reading with 98% accuracy.

## **Pinout**
![image](https://user-images.githubusercontent.com/60948298/146273491-d2079ae0-385a-4f9a-ac03-24f95911efea.png)
- Texas Instrument

## **MSP432 LCD 16x02 Pinout**
| **MSP432 Pins** |    **LCD Pin** |  **Description** |   
| :---:       |  :--:      |   :---:      |
| `GND`, 10k Potentiometer Output (V&#177;) | 1| GND|  
| `VCC`, 10k Potentiometer Output (V&#177;) | 2| VCC|    
| 10k Potentiometer Output (V<sub>o</sub>) | 3| Contrast|    
| `P4.5` | 4| RS (Register Select): 0 – Command, 1 - Data|    
| `GND`| 5| R/W (Read/Write): 0 – Write, 1 - Read|    
| `4.4` | 6| Clock Enable|    
| `NC`| 7| Data 0|
| `NC`| 8| Data 1|    
| `NC` | 9| Data 2|    
| `NC`| 10| Data 3|    
| `P4.0` | 11|  Data 4|    
| `P4.1` | 12|  Data 5|    
| `P4.2` | 13|  Data 6|    
| `P4.3` | 14|  Data 7|    
| 100&#8486; to `VCC`| 15| Backlight Anode (+)|    
| `GND`| 16| Backlight Cathode (-)|    
  * LCD Pinout Configuration

## **LCD Main Functions**
|**Function** | **Description** |
| :---    | :---        |
| lcdInit();    |   Initialize LCD Display            |
| lcdClear();   | Clear the LCD Display of characters | 
| lcdSetText(string, c, r); | Print a string/character starting at c, column and r, row |
|lcdSetInt(integer, c, r); | Print a integer starting at c, column and r, row. |
|delay_ms(x); | Delay for x milliseconds. |

## Circuit 
![IMG-7803](https://user-images.githubusercontent.com/96082677/147328936-63011623-c858-46fc-a448-bdfa4a5c8497.jpg)


## **Author** 
- Jorge Minjares :zap:
    - Bachelor of Science in Electrical Engineering
