#include <msp430.h> 
#define ACLK 0x0100
#define UP 0x0010
#define SLOW 0x00C0
int Rx_Data;
//pin for red led : 1.0
//pin for OBC regulation : 1.1
int main(void)
{
    //define all pins
    PM5CTL0 &= 0xFFFE;
    P1DIR = BIT0 + BIT1;
    P1OUT|=BIT1; //enable power supply to obc

    //initiate timer A0 to pet self wdt
    TA0CCR0 = 400;
    TA0CTL = ACLK | UP;
    TA0CCTL0 = CCIE;

    //initiate timer A1 to serve as wdt for obc
    TA1CCR0 = 50000;
    TA1CTL = ACLK | UP | SLOW;
    TA1CCTL0 = CCIE;

    //initiate SPI
    UCA0CTLW0 |= UCSWRST;

    UCA0CTLW0 |= UCSSEL__SMCLK;
    UCA0BRW = 10;

    UCA0CTLW0 |= UCSYNC;
    UCA0CTLW0 |= UCMST;

    P1SEL = BIT5 | BIT7 | BIT6;

    UCA0CTLW0 &= ~UCSWRST;

    UCA0IFG &= ~UCRXIFG;
    UCA0IE |= UCRXIE;

    __enable_interrupt();
    while(1) {}


}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR(void) {
    WDTCTL = WDTPW | WDTCNTCL;
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer1_ISR(void) {
    if(TA1CCR0 == 50000) {
        P1OUT &= (~BIT1) ;
        P1OUT |= BIT0;
        TA1CCR0 = 25000;
    }
    else {
        P1OUT |= BIT1;
        TA1CCR0 = 50000;
    }
}

#pragma vector = USCI_A0_VECTOR
__interrupt void ISR_USCI_A0(void) {
    Rx_Data  = UCA0RXBUF;
    if(Rx_Data == 0x10) {
        TA1CCR0 = 0;
    }
    P1OUT |= BIT0;
}
