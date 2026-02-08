#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void process_state_machine(void);

typedef enum{
    INACTIVE,
    INITIALISING,
    FLASHING,
    DEACTIVATING
} type_state;

type_state current_state = INACTIVE;
char flash_count = 0;

int main(void)
{
    while (1){
        process_state_machine();
    }
    return (0);
}

void process_state_machine(void)
{
    switch (current_state){
        case INACTIVE:
            _delay_ms(1000);
            current_state = INITIALISING;
            break;
        case INITIALISING:
            DDRD = 0xf0;
            PORTD = 0x0f;
            current_state = FLASHING;
            break;
        case FLASHING:
            flash_count++;
            if (flash_count <= 8){
                PORTD ^= 0xf0;
                _delay_ms(250);
            } else{
                flash_count = 0;
                current_state = DEACTIVATING;
            }
            break;
        case DEACTIVATING:
            DDRD = 0x00; // back to inputs
            current_state = INACTIVE;
            break;
        default:
            current_state = INACTIVE;
    }
}
