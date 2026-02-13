/*
 * File:   eeprom.c
 * Author: VINAYAK ACHARYA
 *
 * Created on 2 February, 2026, 6:31 PM
 */


#include <xc.h>
#include"header.h"
void write_internal_eeprom(unsigned char address, unsigned char data) {
    //Write the address
    EEADR = address;

    //Write the data
    EEDATA = data;

    //Point to data memory
    EECON1bits.EEPGD = 0;

    //Access data EEPROM memory
    EECON1bits.CFGS = 0;

    //Data write enable bit
    EECON1bits.WREN = 1;

    //Global interrupt disable 
    INTCONbits.GIE = 0;

    //Write protection sequence
    EECON2 = 0x55;
    EECON2 = 0xAA;

    //Initiate write
    EECON1bits.WR = 1;

    //Global interrupt enable
    GIE = 1;

    //Wait till write is complete
    while (!PIR2bits.EEIF); // wait for write complete
    PIR2bits.EEIF = 0; // clear the flag
    EECON1bits.WREN = 0; // disable writes
}

unsigned char read_internal_eeprom(unsigned char address) {
    //Write the address, from where data has to be read
    EEADR = address;

    //Inhibits write cycles to Flash program/data EEPROM
    EECON1bits.WREN = 0;

    //Point to data memory
    EECON1bits.EEPGD = 0;

    //Access data EEPROM memory
    EECON1bits.CFGS = 0;

    //Initiate read
    EECON1bits.RD = 1;

    //Data available in EEDATA register
    return EEDATA;
}
