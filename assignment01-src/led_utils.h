#define L1 6
#define L2 7
#define L3 8
#define L4 9
#define LS 10

/*
* Initialises LED pins.
*/
void led_init();

/*
* Turns the LED attached to the pin given as an argument.
*/
void turn_led(int pin);

/*
* Turns off all the LEDs.
*/
void sweep_leds();

/*
* Returns the state of the LED attached to the pin given as an argument.
*/
int get_led_state(int pin);

/*
* Fades the red LED.
*/
void fade_led();