/*
 * pwm.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Marc
 */

/**
 * @file course1.h
 * @brief This file is to be used to course 1 final assessment.
 *
 * <extended description>
 *
 * @author Alex Fosdick
 * @date April 2, 2017
 *
 */

#ifndef PWM_H_
#define PWM_H_

/*-------------------------------------------------------------------
 *
 *   Preprocessor Constants
 *
 --------------------------------------------------------------------*/
#define PWM_TAxCLK (0x0000)
#define PWM_ACLK   (0x0100)
#define PWM_SMCLK  (0x0200)
#define PWM_INCLK  (0x0300)


#define FREQUENCY 0             //may be changed to a variable if it turns out the frequency needs to change at runtime

/*-------------------------------------------------------------------
 *
 *   Type Definitions
 *
 --------------------------------------------------------------------*/

typedef uint8_t clksel_t;

typedef enum {
  PWMID_SERVO_0 = 0,
  PWMID_SERVO_1,
} PWMID_t;

/*-------------------------------------------------------------------
 *
 *   Function Prototypes
 *
 --------------------------------------------------------------------*/

void PWM_init(uint16_t clock,uint8_t id, uint8_t dcycle);           //unlike most of the items in this lib, the timer will be static, ignoring the pseudo operating system.
void PWM_activate(uint8_t id);
void PWM_load(uint8_t id, uint8_t dcycle);
void PWM_deactivate(uint8_t id);

/**
 * @brief Sets a value of a data array
 *
 * Given a pointer to a char data set, this will set a provided
 * index into that data set to the value provided.
 *
 * @param id Identification to
 * @param dcycle Duty Cycle for given ID
 *
 * @return void.
 */
void PWM_generate(PWMID_t id, uint8_t dcycle);

#endif /* PWM_H_ */
