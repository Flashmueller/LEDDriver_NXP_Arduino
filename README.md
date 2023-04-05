# LEDDriver_NXP_Arduino
LED driver device operation sample code for [Arduino](https://www.arduino.cc) 

> **Note**
This library works with [`I2C_device`](https://github.com/teddokano/I2C_device_Arduino) library together. Please be sure the `I2C_device` library is imported in your environment before trying to build. 

> **Warning**  
**Default setting of LED brightness may be too strong!**  
Basic sample code have setting of mamximum current output. It may be too bright for normal use.  
If you want to turn down the output, adjust first parameter of `ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);` method call.  
The first `1.0` means the ratio of all output current. The 1.0 is for 100% (maximum output). So it could be **0.1** or so for softer brightness.  

```cpp
// Changing output current setting
void setup() {
  ...
  ..
  Wire.begin();
  //ledd.begin( 1.0, PCA9955B::ARDUINO_SHIELD ); // <-- This was original 
  ledd.begin( 0.1, PCA9955B::ARDUINO_SHIELD );   // <-- Current setting is changed to 0.1 (means 10% of max)
}

```

![Boards](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/LED-ARD.jpeg)  
_PCA9955BTW-ARD (left), PCA9957HN-ARD (right) and OM13321 LED driver evaluation boards_

# What is this?
An Arduino library for I²C LED drivers with sample code.  
The I²C temperature sensors can measure temoperature and output comparator or interrupt signals by threshold settings. 

# Supported devices
Type#|Features|# of channels|additional feature|Interface|Evaluation board
---|---|---|---|---|---
[PCA9955B](https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW)	|Constant current LED driver	|16ch		|with gradation control	|I²C Fast-mode plus (1MHz)			|[PCA9955BTW-ARD LED Driver Arduino® Shield Evaluation Board](https://www.nxp.com/design/development-boards/analog-toolbox/arduino-shields-solutions/pca9955btw-ard-led-driver-arduino-shield-evaluation-board:PCA9955BTW-ARD?tid=vanPCA9955BTW-ARD)
[PCA9956B](https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9956BTW)		|Constant current LED driver	|24ch		|---					|I²C Fast-mode plus (1MHz)			|[OM13321](https://www.nxp.com/docs/en/user-guide/UM10709.pdf)
[PCA9957](https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9957)		|Constant current LED driver	|24ch		|with gradation control	|SPI								|[PCA9957HN-ARD LED Driver Arduino® Shield Evaluation Board](https://www.nxp.jp/design/development-boards/analog-toolbox/arduino-shields-solutions/pca9957hn-ard-led-driver-arduino-shield-evaluation-board:PCA9957HN-ARD)

To put PCA9957HN-ARD Arduino-shield evaluation board, use socket-pin extenders to avoid down side connector interfare.  
![Boards](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/PCA9957_pins.jpeg)

# Code sample
With `LEDDriver_NXP_Arduino` library, the LEDs can be managed simple API.  
For PCA9955B and PCA9956B, those operations are quite similar. When the device is changed, just overwrite class name from `PCA9955B` to `PCA9956B`.  

```cpp
// Very simple sample to use the 'PCA9955BTW-ARD LED Driver Arduino® Shield Evaluation Board'

#include <LEDDriver.h>

PCA9955B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);
}

void loop() {
  ledd.pwm(0, 1.0);
  Serial.println("ON ");
  delay(100);

  ledd.pwm(0, 0.0);
  Serial.println("OFF");
  delay(100);
}
```

For PCA9957, it uses an SPI as serial interface. To use the SPI, need to have `SPI.begin()` in `setup()` function. 

```cpp
// Very simple sample to use the 'PCA9957HN-ARD LED Driver Arduino® Shield Evaluation Board'

#include <LEDDriver.h>

PCA9957 ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9957! *****");

  SPI.begin();
  ledd.begin(1.0, PCA9957::ARDUINO_SHIELD);
}

void loop() {
  ledd.pwm(0, 1.0);
  Serial.println("ON ");
  delay(100);

  ledd.pwm(0, 0.0);
  Serial.println("OFF");
  delay(100);
}
```  

# Getting started
Use **Library manager** in Arduino IDE for easy install
- **Find** this library: **Open** the _**Library Manager**_ pane, **Search** this library (type "**PCA99**" in the search field then this library will be shown) and click **INSTALL** button.  
![Find the lib](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/install.png)

- Click **"INSTALL ALL"**  
![Install all](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/install_all.png)

- Install will be completed quickly  
![Install completed](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/install_completed.png)

- Choose a sample code and try!  
![Choosing a sample code](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/using_examples.png)

# What's inside?
## Examples
Examples are provided as scketch files.  
### How to use?
For a quick access to those sketch, **refer to last step** of **"Getting started" section** of this page. 

### List of sample code

#### Basic examples
Folder|Sketch|Target|Feature
---|---|---|---
PCA9955B/	|0_simple_ch0_PCA9955B						|PCA9955B	|**Simple** sample for just blinking channel 0
PCA9955B/	|1_all_channels_PCA9955B					|PCA9955B	|Simple operation to blink **all channels in order**
PCA9955B/	|2_color_phases_PCA9955B					|PCA9955B	|Phase independent dimming on color LEDs: **color mixing**
PCA9955B/	|3_direct_register_access_PCA9955B			|PCA9955B	|**Direct register access** sample. Write/read a register in every 100 mili-second
PCA9956B/	|0_simple_ch0_PCA9956B						|PCA9956B	|**Simple** sample for just blinking channel 0
PCA9956B/	|1_all_channels_PCA9956B					|PCA9956B	|Simple operation to blink **all channels in order**
PCA9956B/	|2_color_phases_PCA9956B					|PCA9956B	|Phase independent dimming on color LEDs: **color mixing**
PCA9956B/	|3_direct_register_access_PCA9956B			|PCA9956B	|**Direct register access** sample. Write/read a register in every 100 mili-second
PCA9957/	|0_simple_ch0_PCA9957						|PCA9957	|**Simple** sample for just blinking channel 0
PCA9957/	|1_all_channels_PCA9957						|PCA9957	|Simple operation to blink **all channels in order**
PCA9957/	|2_color_phases_PCA9957						|PCA9957	|Phase independent dimming on color LEDs: **color mixing**
PCA9957/	|3_direct_register_access_PCA9957			|PCA9957	|**Direct register access** sample. Write/read a register in every 100 mili-second

#### Advanced examples (showing additional features)
Folder|Sketch|Target|Feature
---|---|---|---
concept_examples/	|abstracting_LEDs					|PCA9955B	|For further easy operations for multiple LEDs
concept_examples/	|buffered_mode						|PCA9955B	|Demo: how to use "buffered" mode
concept_examples/	|buffered_mode_with_timer			|PCA9955B	|Demo: LED refresh rate managed by **timer interrupt**. This code is using [MsTimer2](https://playground.arduino.cc/Main/MsTimer2/) library
concept_examples/	|Demo_dual_OM13321					|PCA9956B	|Demo: **Two PCA9956B** operation demo. Using [MsTimer2](https://playground.arduino.cc/Main/MsTimer2/) library
concept_examples/	|no_library_operation_sample		|PCA9955B	|Showing a sample of **no-library using** operation


## LED driver library
`PCA9955B`, `PCA9956B` and `PCA9957` class libraries are included. Those libraries can be used by just making an instance from those class.  
Those libraries have common methods to get/set device information.

### Constructors
`PCA9955B`, `PCA9956B` and `PCA9957` are classes to make instances. To make those instance, one option can be specified.   

```cpp
// defining 3 LED driver instances ('ledd_1' is having option to set non-default I²C target address)
PCA9955B ledd_0;         // making instance of  PCA9955B as 'ledd_0' with default I2C addess (0xBE)
PCA9956B ledd_1( 0xB0 ); // making instance of  PCA9956B as 'ledd_1' with I2C addess (0xB0)
PCA9957  ledd_2;         // making instance of  PCA9957  as 'ledd_2'. No I2C address given because its a SPI device
```

### Basic methods

`begin()` and `pwm()` are basic methods of LEDDriver.  
Method|Role
---|---
`begin( float current = 0.1, board env = NONE )`	|Initializing device. 1st argument `current` is ratio of output current. 0.0~1.0. 2nd argument `env` is an option: use `LEDDriver::ARDUINO_SHIELD` if the target board is Arduino-shield board
`pwm( uint8_t ch, float value )`					|Set single channel LED brightness. `value` must be in float: 0.0~1.0
`pwm( float* values )`								|Set LED brightness for all channels. `values` must be an array of float with length of number of device output channels. Each float values in the array should be 0.0~1.0.

#### `begin()`
`begin()` mathod can take two parameters: `current` and `env`. These parameters are option. If those are not give, default values are applied (0.1 and NONE). 
As described in **warning** of beggining of this document, the first parameter sets current output. 
It can be as range of 0.0 ~ 1.0 which means 0% ~ 100%. 

The second parameter is to set board setting for _**LED Driver Arduino® Shield Evaluation Boards**_. 
Those boards need to have specific pin setting on D8 and D9 pins. When the Shield board using constant of `ARDUINO_SHIELD`. 

```cpp
// Calling 'begin()' method with/without options
ledd_0.begin( 1.0 ); //	'ledd_0' is set to 100% current output. Target is non-Arduino-Shield board
ledd_1.begin();      //	Use default setting. Output current is 10% and target is non-Arduino-Shield board
ledd_2.begin( 0.5, PCA9955B::ARDUINO_SHIELD ); // Output is 50% and target is non-Arduino-Shield board
```
#### `pwm()`
`pwm()` is a method for setting PWM output ratio.  

If the `pwm()` is called with two parameters of `ch` and `value`, it will set the PWM ratio given as `value`. 
The `value` is a float, which needs to be in range of 0.0 ~ 1.0. 

If the `pwm()` is called with a pointer to float array, it will set all PWM channels with values in the array.  
The array size need to be same as the number of LED driver output channels. 

```cpp
// Callong 'pwm()' method with channel number and PWM ratio
ledd_0.pwm( 5, 0.5 );	//	The ledd_0's channel 5 PWM ratio is set to 50%. 
```

```cpp
// Callong 'pwm()' method with an array of float
float v[ ledd_0.n_chanel ] = { 0.2 }; // Prepare an array of float, initialized to all 0.2. 'n_chanel' is available to get the LED driver output chanels
v[ 7 ] = 0.5;    // Set 0.5 into 7 item in the array
ledd_0.pwm( v );  // All channels are set to 20% ouptput except channel 7 (50%)
```
### Methods for buffer mode

Method|Role
---|---
`buffer_enable( bool flag )`	|Buffer mode enabling by giving parameter of `true`. Give `false` to disable
`flush( void )`					|Flushing data. The buffer contents will be sent to the LED driver

The **buffer mode** can be used for all LEDDriver instances. 
The buffer mode is to save I²C/SPI bus bandwidth. Without the buffering, the MCU and LED driver interaction happens each time of `pwm()` method call.  
To avoid waste of bandwidth, the buffer mode can be used.  

After the buffer mode enabled, the `pwm()` method call updates PWM value in buffer memory. The brightness of LED is not changed at this moment.  
After all necessary channel values update is done, `flush()` method can be called to update LED driver output. 

```cpp
// Buffer mode usage
ledd_0.buffer_enable( true );              // Buffer mode enabled for ledd_0
for ( int i; i < ledd_0.n_channel; i++) {
	ledd_0.pwm( i, 0.5 );                  // 50% setting for each channels. Settings are stored in buffer memory
}

ledd_0.flush();  // Update LED driver with new values
```

Example code is available for how the buffer mode can be used. Please refer to code in `examples/concept_examples/buffered_mode`

### LED class
An `LED` class is defined and used at examples in `examples/concept_examples/` folder.  
This class enables indexing LEDs independent from LED drivers.  
To see basic idea for the `LED` class, see `examples/concept_examples/abstracting_LEDs`. 


# Document
For details of the library, please find descriptions in [this document](https://teddokano.github.io/LEDDriver_NXP_Arduino/annotated.html).

# References

## Related libraries
Library|Feature|Target devices|Required library
---|---|---|---
[LEDDriver_NXP_Arduino](https://github.com/teddokano/LEDDriver_NXP_Arduino)		|LED driver libraries				|PCA9955B, PCA9956B, PCA9957	|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino)	|Temperature sensor libraries		|LM75B, PCT2075, P3T1085		|[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)
[I2C_device_Arduino](https://github.com/teddokano/I2C_device_Arduino)			|Base library for I²C operations	|none (can be applied as base class for all I²C targets)|---
