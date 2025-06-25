#include <lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALARM_DELAY 50000
#define WAIT_DELAY 100000
#define RS_CTRL 1 << 19
#define EN_CTRL 1 << 20
#define DATA_CTRL 0xF << 15
#define LED_CTRL 0xFF << 4
/*
CNA - P0.11 - P0.4 -> LED
CNB - P2.10 - 5th pin -> relay
CNB - P2.13 - 8th pin -> buzzer
CNB - P2.11 - 6th pin -> External Interrupt 1
- LEAK - sensor -ve edge triggered
CNB - P2.12 - 7th pin -> External Interrupt 2
- SAFE - sensor +ve edge triggered
CNC - P0.20 - P0.15 -> LCD
CND - P0.23 - 1rst pin -> sensor analog input
(function 1) (top right-most pin)
*/
void lcd_init(void);
void lcd_write(void);
void port_write(void);
void lcd_puts(unsigned char *);
void delay(unsigned int);
unsigned int temp, i, temp1, temp2,
    adc_reading, state;
unsigned char lcd_line_1[20] = "GASLEAK
    DETECTOR ";
    unsigned char lcd_line_2[20] = "";
void ADC_IRQHandler(void)
{
    // clear all interrupt flags
    LPC_ADC->ADINTEN = 0x1FF;
    // check bit 31 done flag
    if (!((temp = LPC_ADC->ADGDR) & (1 << 31)))
    {
        return;
    }
    // check if channel 0 has been polled
    else if (temp >> 24 & 0x7)
    {
        return;
    }
    adc_reading = (temp >> 4) & 0xFFF;
    sprintf(lcd_line_2, "%s | %u ", state ? "LEAK" : "SAFE", adc_reading);
    // move cursor to second line and write
    string
        LPC_GPIO0->FIOMASK = LED_CTRL;
    temp1 = 0xC0;
    lcd_write(0);
    delay(800);
    lcd_puts(&lcd_line_2[0]);
}
void EINT1_IRQHandler(void)
{
    // clear interrupt EINT1 - negative edge
    on CNB pin 6 - P2.11 LPC_SC->EXTINT = 1 << 1;
    // leak detected - perform alarm actions
    in main() while loop
        state = 1;
}
void EINT2_IRQHandler(void)
{
    // clear interrupt EINT2 - positive edge
    on CNB pin 7 - P2.12 LPC_SC->EXTINT = 1 << 2;
    // no leak present - disable alarms
    state = 0;
    // relay ON buzzer OFF LED OFF
    LPC_GPIO0->FIOMASK = RS_CTRL | EN_CTRL |
                         DATA_CTRL;
    LPC_GPIO0->FIOPIN = 0; // LED OFF
    LPC_GPIO2->FIOPIN = (1 << 10) | (0 << 13);
    // relay ON | buzzer OFF
}
int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();
    // Set P2.10 (relay) & P2.13 (buzzer) as
    output
        LPC_GPIO2->FIODIR = (1 << 10) | (1 << 13);
    // Set P0.21-P0.15 as LCD output and
    P0.11 - P0.4 as LED output
                LPC_GPIO0->FIODIR = RS_CTRL | EN_CTRL |
                                    DATA_CTRL | LED_CTRL;
    // Set CNB pin 6 - P2.11 & CNB pin 7 -
    P2.12 as external interrupt
        LPC_PINCON->PINSEL4 = (1 << 22) | (1 << 24);
    // edge triggered interrupt on both EINT1
    &EINT2
         LPC_SC->EXTMODE = (1 << 1) | (1 << 2);
    // EINT1: negative edge | EINT2: positive
    edge
        LPC_SC->EXTPOLAR = (0 << 1) | (1 << 2);
    // enable external interrupt globally in
    NVIC block
        NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
    lcd_init();
    delay(WAIT_DELAY);
    // display project title on first line
    temp1 = 0x80;
    lcd_write(0);
    delay(800);
    lcd_puts(&lcd_line_1[0]);
    // enable ADC CH0 at P0.23 (connected to
sensor analog output - CND first pin)
LPC_PINCON->PINSEL1 = 1 << 14;
LPC_SC->PCONP |= (1 << 12);
LPC_ADC->ADCR = (1 << 0) | (1 << 21) | (1 << 16);
LPC_ADC->ADINTEN = (1 << 0); // enable
interrupt on ADC CH0 scan
    NVIC_EnableIRQ(ADC_IRQn); // enable ADC
interrupts globally while (1)
{
    // trigger alarm actions only if state
    is 1 i.e.gas leak detected if (!state)
    {
        delay(WAIT_DELAY);
        continue;
    }
    // toggle buzzer and LED while keeping
    relay OFF
        LPC_GPIO0->FIOMASK = RS_CTRL | EN_CTRL | DATA_CTRL;
    LPC_GPIO0->FIOPIN = 0xFF << 4; // LED
    ON
        LPC_GPIO2->FIOPIN = (0 << 10) | (1 << 13); // relay OFF | buzzer ON
    delay(ALARM_DELAY);
    LPC_GPIO0->FIOPIN = 0; // LED
    OFF
        LPC_GPIO2->FIOPIN = (0 << 10) | (0 << 13); // relay OFF | buzzer OFF
    delay(ALARM_DELAY);
}
}
void lcd_init()
{
    clear_ports();
    delay(3200);
    temp2 = (0x30 << 15);
    port_write(0);
    delay(30000);
    temp2 = (0x30 << 15);
    port_write(0);
    delay(30000);
    temp2 = (0x30 << 15);
    port_write(0);
    delay(30000);
    temp2 = (0x20 << 15);
    port_write(0);
    delay(30000);
    temp1 = 0x28;
    lcd_write(0);
    delay(30000);
    temp1 = 0x0C;
    lcd_write(0);
    delay(800);
    temp1 = 0x06;
    lcd_write(0);
    delay(800);
    temp1 = 0x01;
    lcd_write(0);
    delay(10000);
    temp1 = 0x80;
    lcd_write(0);
    delay(800);
    return;
}
void lcd_write(unsigned int is_data)
{
    temp2 = temp1 & 0xF0;
    temp2 = temp2 << 11;
    port_write(is_data);
    temp2 = temp1 & 0x0F;
    temp2 = temp2 << 15;
    port_write(is_data);
    delay(1000);
    return;
}
void port_write(unsigned int is_data)
{
    LPC_GPIO0->FIOCLR = RS_CTRL | EN_CTRL |
                        DATA_CTRL;
    LPC_GPIO0->FIOPIN = temp2;
    (is_data) ? (LPC_GPIO0->FIOSET = RS_CTRL)
              : (LPC_GPIO0->FIOCLR = RS_CTRL);
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    return;
}
void lcd_puts(unsigned char *buffer)
{
    i = 0;
    while (buffer[i] != ’\0’ && i < 16)
    {
        temp1 = buffer[i++];
        lcd_write(1);
    }
    return;
}
void delay(unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; i++);
}