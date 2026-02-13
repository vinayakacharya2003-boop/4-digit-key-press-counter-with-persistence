/*
 * File:   main.c
 * Author: VINAYAK ACHARYA
 *
 * Created on 2 February, 2026, 6:30 PM
 */


#include <xc.h>

#include"header.h"

static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

void init_config() {
    init_digital_keypad();
    init_ssd_control();
}

void main(void) {
    unsigned char key;
    unsigned int delay = 0;
    unsigned int count = (read_internal_eeprom(0x03)*1000)+(read_internal_eeprom(0x02)*100)+(read_internal_eeprom(0x01)*10)+(read_internal_eeprom(0x00));
    init_config();

    while (1) {
        ssd[3] = digit[count % 10];
        ssd[2] = digit[(count / 10) % 10];
        ssd[1] = digit[(count / 100) % 10];
        ssd[0] = digit[count / 1000];

        display(ssd);

        key = read_digital_keypad(0);
        if (SWITCH1 == key) {
            if (delay++ > 200) {
                count = 0;
            }
        } else if (delay > 0 && delay < 200) {
            count++;
            delay = 0;
        } else {
            delay = 0;
        }

        if (SWITCH2 == key) {
            write_internal_eeprom(0x00, count % 10);
            write_internal_eeprom(0x01, (count / 10) % 10);
            write_internal_eeprom(0x02, (count / 100) % 10);
            write_internal_eeprom(0x03, count / 1000);
        }
    }

}
