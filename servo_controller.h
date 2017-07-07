/*
 * servo_controller.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Marc
 */

#ifndef SERVO_CONTROLLER_H_
#define SERVO_CONTROLLER_H_

#define FREQUENCY 1000
#define OPEN_PULSE_WIDTH 0
#define CLOSED_PULSE_WIDTH 0

enum servo_error {success,jam};
typedef enum servo_error servo_error_t;

servo_error_t servo_set_position(uint8_t position, uint8_t port, uint8_t pin);
uint8_t servo_get_position(uint8_t port, uint8_t pin);


#endif /* SERVO_CONTROLLER_H_ */
