# si5351-tiny-vfo
VFO build around Si5351, Attiny85, ssd1306

# VFO Schematics:

Schematics exactly the same with ZL2PD single band VFO: https://www.zl2pd.com/tiny85_si5351_VFO.html , but without S-meter. 
Brief wiring:
                        Attiny85
                      +----------+   
  ---[RESET]----------+ PB5  Vcc +---(+)--VCC + 3.3 VOLTS --------
  ---[ENCODER LEFT]---+ PB3  PB2 +---[I2C/SCL SI5351 / SSD1306]---
  ---[ENCODER RIGHT]--+ PB4  PB1 +---[I2C/SDA SI5351 / SSD1306]---
  ---[GROUND]---------+ GND  PB0 +---[ENCODER BUTTON]-------------
                      +----------+
  
  I2C SCL and I2C SDA pull-up to VCC by 4.7 kOhm resistors. 
  ATTINY 85 FUSES set to E:FF, H:DF, L:62
  SI5351 CLK0 output is VFO, CLK1 output is BFO

# Making project:

make

# VFO Operate:

Setup.
Enter setup (calibration) mode by pressing ENCODER button at power-on. "#VFO" will be shown at the bottom screen line. 
Set starting VFO frequency using ENCODER rotation. ENCODER short button press change menu items. First click select 
sideband change (LSB/USB), second click select step change (100Hz, 1kHz, 5kHz, 1MHz). Next click back to frequency select. 
Long press of ENCODER button store starting VFO frequency to EEPROM and go to BFO frequency. 
At BFO frequency setup #BFO will shown at the bottom screen line. Set BFO frequency exactly the VFO frequency. Long ENCODER
button press store BFO frequency to EEPROM and return to normal operation mode. 

Operation mode.
ENCODER rotation change frequency by selected step. ENCODER short button press change menu items. First click select 
sideband change (LSB/USB), second click select step change (100Hz, 1kHz, 5kHz, 1MHz). Next click back to frequency select.
Long press of ENCODER button store starting VFO frequency to EEPROM.

# Credits

Uses SSD1306xLED - Library for the SSD1306 based OLED/PLED 128x64 displays by Neven Boyanov (https://bitbucket.org/tinusaur/ssd1306xled)