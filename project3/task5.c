#include "pic24_all.h"
#if __dsPIC33EP128GP502__
#define LED1 _LATB15
#define CONFIG_LED1() ENABLE_RB15_OPENDRAIN();

#define RLED _LATA0
#define BLED _LATB2
#define GLED _LATA4

inline void CONFIG_RGB()
{
    CONFIG_RA0_AS_DIG_OUTPUT();
    CONFIG_RB2_AS_DIG_OUTPUT();
    CONFIG_RA4_AS_DIG_OUTPUT();
}

#define SW1 _RB0
#define SW2 _RB1
#define PRESS (!SW1)
#define RELEASE (SW1)

inline void CONFIG_SW1()
{
    CONFIG_RB0_AS_DIG_INPUT();
    ENABLE_RB0_PULLUP();
}

inline void CONFIG_SW2()
{
    CONFIG_RB1_AS_DIG_INPUT();
    ENABLE_RB1_PULLUP();
}

#endif

typedef enum
{
    RESET = 0,
    WAIT_R,
    WAIT_P,
} State;

int main(void)
{
    // the code below configures the dsPIC33 using functions provided by
    // the textbook authors.
    configClock();
    configPinsForLowPower();
    configHeartbeat();
    State state;

    // the code below is to setup LED1, SW1, and the RGB LED
    CONFIG_LED1();
    CONFIG_RGB();
    CONFIG_SW1();
    CONFIG_SW2();

    DELAY_US(1);
    RLED = 0;
    while (1)
    { // Infinite while loop
        LED1 = 1;
        switch (state)
        {
        case WAIT_P {
            if (PRESS()) {
                state = WAIT_R;
                break;
            }
        } case WAIT_R {
            if (RELEASE()) {
                RLED = !RLED;
                state = WAIT_P;
                break;
            }
        } case RESET {
            break;
        } default:
            state = WAIT_P;
        }

        DELAY_MS(1000); // Delay 15 ms
    }
    return 0;
}
