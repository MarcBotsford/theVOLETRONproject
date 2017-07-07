//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "doors.h"
#include "VI.h
#include "servo_controller.h"
#include "pwm.h"
#include "timer.h"
#include "rtc.h
#include "uart.h"
#include "beambreak.h"

void main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	
}
