/** PCA9955B LED driver operation sample
 *  
 *  This sample code is showing PCA9955B LED driver operation with PWM value setting change.
 *  The ledd.pwm() takes channel number and PWM ratio. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9955B:
 *    https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9955B
 */

#include <LEDDriver.h>

/** Advanced abstraction layer for easy LED management
 *  @class  LED
 */

class LED {
public:
  LED(PCA9955B* leddp, int ch) {
    devp = leddp;
    channel = ch;
  }
  float operator=(float v) {
    devp->pwm(channel, v);
    return v;
  }
private:
  PCA9955B* devp;
  int channel;
};

PCA9955B ledd;
LED led[] = {
  LED(&ledd, 0), LED(&ledd, 1), LED(&ledd, 2), LED(&ledd, 3),
  LED(&ledd, 4), LED(&ledd, 5), LED(&ledd, 6), LED(&ledd, 7),
  LED(&ledd, 8), LED(&ledd, 9), LED(&ledd, 10), LED(&ledd, 11),
  LED(&ledd, 12), LED(&ledd, 13), LED(&ledd, 14), LED(&ledd, 15)
};

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);
}

void loop() {
  led[0] = led[3] = led[6] = 1.0;
  led[1] = led[4] = led[7] = 0.0;
  led[2] = led[5] = led[8] = 0.0;
  delay(100);

  led[0] = led[3] = led[6] = 0.0;
  led[1] = led[4] = led[7] = 1.0;
  led[2] = led[5] = led[8] = 0.0;
  delay(100);

  led[0] = led[3] = led[6] = 0.0;
  led[1] = led[4] = led[7] = 0.0;
  led[2] = led[5] = led[8] = 1.0;
  delay(100);
}
