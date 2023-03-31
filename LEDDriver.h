/** TempSensor operation library for Arduino
 *
 *  @class  TempSensor
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#ifndef ARDUINO_LED_DRIVER_NXP_ARD_H
#define ARDUINO_LED_DRIVER_NXP_ARD_H

#include <Arduino.h>
#include <stdint.h>

#include <I2C_device.h>

/** LEDDriver class
 *	
 *  @class LEDDriver
 *
 *	LEDDriver class is a base class for all LED drivers
 *	All actual device class will be derived from this class
 */

class LEDDriver
{
public:
	enum board {
		NONE,
		ARDUINO_SHIELD,
	};
	
	LEDDriver( uint8_t n_ch, uint8_t PWM_r );
	virtual ~LEDDriver();
	virtual void reg_access( uint8_t reg, uint8_t val  )	= 0;
	virtual void reg_access( uint8_t reg, uint8_t *vp, uint8_t len )	= 0;

	/** Set PWM value for a channel
	 *
	 * @param reg register number
	 * @param value	PWM value in float (0.0 ~ 1.0)
	 */
	void pwm( uint8_t ch, float value );

	/** Set PWM value for all channels
	 *
	 * @param reg register number
	 * @param *value pointer to PWM value in float (0.0 ~ 1.0)
	 */
	void pwm( float* values );

protected:
	const uint8_t n_channel;
	const uint8_t reg_PWM;
};



/** PCA995x class
 *	
 *  @class PCA995x
 *
 *	Base class to abstract behavior of PCA995x series
 */

class PCA995x : public LEDDriver
{
public:
	PCA995x( uint8_t n_ch, uint8_t PWM_r, uint8_t IREF_r, uint8_t IREFALL_r );
	virtual ~PCA995x();
	
	virtual void begin( float current =  0.1, board env = NONE );
	virtual void init( float current )	= 0;

	/** Set IREFALL value (current setting for all channels)
	 *
	 * @param value current value in float (0.0 ~ 1.0)
	 */
	void irefall( uint8_t iref );

protected:
	const uint8_t reg_IREF;
	const uint8_t reg_IREFALL;
};



class PCA995x_I2C : public PCA995x, public I2C_device
{
public:
	PCA995x_I2C( uint8_t i2c_address, uint8_t n_ch, uint8_t PWM_r, uint8_t IREF_r, uint8_t IREFALL_r );
	virtual ~PCA995x_I2C();

	void reg_access( uint8_t reg, uint8_t val  );
	void reg_access( uint8_t reg, uint8_t *vp, uint8_t len );
};



/** PCA9955B class
 *	
 *  @class PCA9955B

 *  About PCA9955B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW
 */

class PCA9955B : public PCA995x_I2C
{
public:
	/** Number of channels */
	const static uint8_t n_channel	= 16;
	
	/** Name of the PCA9955B registers */
	enum reg_num {
		MODE1, MODE2, 
		LEDOUT0, LEDOUT1, LEDOUT2, LEDOUT3, 
		GRPPWM, GRPFREQ, 
		PWM0,  PWM1,  PWM2,   PWM3,   PWM4,   PWM5,   PWM6,   PWM7, 
		PWM8,  PWM9,  PWM10,  PWM11,  PWM12,  PWM13,  PWM14,  PWM15, 
		IREF0, IREF1, IREF2,  IREF3,  IREF4,  IREF5,  IREF6,  IREF7, 
		IREF8, IREF9, IREF10, IREF11, IREF12, IREF13, IREF14, IREF15, 
		RAMP_RATE_GRP0, STEP_TIME_GRP0, HOLD_CNTL_GRP0, IREF_GRP0, 
		RAMP_RATE_GRP1, STEP_TIME_GRP1, HOLD_CNTL_GRP1, IREF_GRP1, 
		RAMP_RATE_GRP2, STEP_TIME_GRP2, HOLD_CNTL_GRP2, IREF_GRP2, 
		RAMP_RATE_GRP3, STEP_TIME_GRP3, HOLD_CNTL_GRP3, IREF_GRP3, 
		GRAD_MODE_SEL0, GRAD_MODE_SEL1, 
		GRAD_GRP_SEL0, GRAD_GRP_SEL1, GRAD_GRP_SEL2, GRAD_GRP_SEL3, 
		GRAD_CNTL, 
		OFFSET, 
		SUBADR1, SUBADR2, SUBADR3, ALLCALLADR, 
		PWMALL, IREFALL, 
		EFLAG0, EFLAG1, EFLAG2, EFLAG3, 
	};
	
    /** Create a PCA9955B instance connected to specified I2C pins with specified address
     *
     * @param i2c_address I2C-bus address (default: (0xBC>>1))
     */
	PCA9955B( uint8_t i2c_address = (0xBC >> 1) );
	virtual ~PCA9955B();

	/** Initializing device
	 *
	 * @param value current value in float (0.0 ~ 1.0)
	 */
	void init( float current );
};

class PCA9956B : public PCA995x_I2C
{
public:
	/** Number of channels */
	const static uint8_t n_channel	= 24;
	
	/** Name of the PCA9955B registers */
	enum reg_num {
		MODE1, MODE2,
		LEDOUT0, LEDOUT1, LEDOUT2, LEDOUT3, LEDOUT4, LEDOUT5,
		GRPPWM, GRPFREQ,
		PWM0,  PWM1,  PWM2,  PWM3,  PWM4,  PWM5,
		PWM6,  PWM7,  PWM8,  PWM9,  PWM10, PWM11,
		PWM12, PWM13, PWM14, PWM15, PWM16, PWM17,
		PWM18, PWM19, PWM20, PWM21, PWM22, PWM23,
		IREF0,  IREF1,  IREF2,  IREF3,  IREF4,  IREF5,
		IREF6,  IREF7,  IREF8,  IREF9,  IREF10, IREF11,
		IREF12, IREF13, IREF14, IREF15, IREF16, IREF17,
		IREF18, IREF19, IREF20, IREF21, IREF22, IREF23,
		OFFSET,
		SUBADR1, SUBADR2, SUBADR3, ALLCALLADR,
		PWMALL, IREFALL,
		EFLAG0, EFLAG1, EFLAG2, EFLAG3, EFLAG4, EFLAG5
	};
	/** Create a PCA9955B instance connected to specified I2C pins with specified address
	 *
	 * @param i2c_address I2C-bus address (default: (0x02>>1))
	 */
	PCA9956B( uint8_t i2c_address = (0x02 >> 1) );
	virtual ~PCA9956B();

	/** Initializing device
	 *
	 * @param value current value in float (0.0 ~ 1.0)
	 */
	void init( float current );
};

#endif //	ARDUINO_LED_DRIVER_NXP_ARD_H
