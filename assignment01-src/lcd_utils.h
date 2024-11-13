#define LCD 0x27

/*
* Initialises the LCD screen for communication.
*/
void lcd_init();

/*
* Shows the welcome screen.
*/
void welcome_screen();

/*
* Shows the game starting screen.
*/
void go_screen();

/*
* Shows the number to be converted during the round.
*/
void show_number(int num);

/*
* Shows the current score between rounds.
*/
void score_screen(int score);

/*
* Shows the game over screen.
*/
void game_over_screen(int score);

/*
* Turns off the screen
*/
void lcd_turn_off();