#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P1 RA4

void putch(char c){
    while(TXIF==0);
    TXREG=c;
}

void main(void) {
    //Configura entradas y salidas
    TRISA=0xFF;
    TRISB=0x00;
    TRISC=0x00;
    TRISC7=1;
    
    //Configura UART a 9600 baudios
    TXSTAbits.TXEN=1;
    TXSTAbits.BRGH=1;
    RCSTAbits.SPEN=1;
    RCSTAbits.CREN=1;
    BAUDCTLbits.BRG16=0;
    SPBRG=25;
    SPBRGH=0;
    
    //CONFIG TIMER 0
    T0CS=0;// para 6.6ms del TP1
    PSA=0;
    PS2=0; // 1:8
    PS1=1;
    PS0=0;
    TMR0=131;// a 125 de desbordar
    T0IF=0;
    
    //Variables
    unsigned int time=0, flag=0;
    
    while(1){
        while(T0IF==1){
            TMR0=TMR0+131;
            T0IF=0;
            if(P1==1){
                time++;
                flag=1;
            }
            else if (flag==1){
                printf("%d ms",time);
                time=0;
                flag=0;
            }
        }
    }
}
