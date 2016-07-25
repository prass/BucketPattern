#include <avr/io.h>
#include "../bucket.h"

#define PRESSED 1
#define RELEASED 2

static int button_pressed(struct bucket_t *button, uint8_t pin_state) {
	static uint8_t pressed = 0;

	// update bucket level
	update_bucket(button, pin_state);

	// button pressed long time
	if(bucket_empty(button) && !pressed) {
		pressed = 1;
		return PRESSED;
	}

	// button released
	if(bucket_full(button) && pressed) {
		pressed = 0;
		return RELEASED;
	}
	return 0;
}

int main() {
	int state;
	struct bucket_t button;
	init_bucket(&button, 200);

	// define PB4 as input
	DDRB = (0<<DDB4);
	// enable pullup
	PORTB = (1<<PORTB4);

	while(1) {
		state = button_pressed(&button, !(PINB & (1<<PINB4)));
		if(state == PRESSED) {
		}
		if(state == RELEASED) {
		}
	}
}
