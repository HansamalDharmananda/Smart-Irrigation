/*
 * core.c
 *
 * Created: 1/9/2020 3:13:29 AM
 * Author : Hansamal
 */

#define  F_CPU 16000000
#define BAUD 9600
#define MYUBRR ((F_CPU/16/BAUD)-1)

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

//LCD Functions Developed by electroSome
#define eS_PORTA0 0
#define eS_PORTA1 1
#define eS_PORTA2 2
#define eS_PORTA3 3
#define eS_PORTA4 4
#define eS_PORTA5 5
#define eS_PORTA6 6
#define eS_PORTA7 7
#define eS_PORTB0 10
#define eS_PORTB1 11
#define eS_PORTB2 12
#define eS_PORTB3 13
#define eS_PORTB4 14
#define eS_PORTB5 15
#define eS_PORTB6 16
#define eS_PORTB7 17
#define eS_PORTC0 20
#define eS_PORTC1 21
#define eS_PORTC2 22
#define eS_PORTC3 23
#define eS_PORTC4 24
#define eS_PORTC5 25
#define eS_PORTC6 26
#define eS_PORTC7 27
#define eS_PORTD0 30
#define eS_PORTD1 31
#define eS_PORTD2 32
#define eS_PORTD3 33
#define eS_PORTD4 34
#define eS_PORTD5 35
#define eS_PORTD6 36
#define eS_PORTD7 37

#ifndef D0
#define B0 eS_PORTB0
#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTB3
#define EN eS_PORTB2
#endif

#define E_PIN			2
#define RS_PIN			3
#define LCD_CTRL_PORT_DIR	DDRB
#define LCD_DATA_PORT_DIR	DDRD


void pinChange(int a, int b)
{
	if(b == 0)
	{
		if(a == eS_PORTB0)
		PORTB &= ~(1<<PB0);
		else if(a == eS_PORTB1)
		PORTB &= ~(1<<PB1);
		else if(a == eS_PORTB2)
		PORTB &= ~(1<<PB2);
		else if(a == eS_PORTB3)
		PORTB &= ~(1<<PB3);
		else if(a == eS_PORTB4)
		PORTB &= ~(1<<PB4);
		else if(a == eS_PORTB5)
		PORTB &= ~(1<<PB5);
		else if(a == eS_PORTB6)
		PORTB &= ~(1<<PB6);
		else if(a == eS_PORTB7)
		PORTB &= ~(1<<PB7);
		else if(a == eS_PORTC0)
		PORTC &= ~(1<<PC0);
		else if(a == eS_PORTC1)
		PORTC &= ~(1<<PC1);
		else if(a == eS_PORTC2)
		PORTC &= ~(1<<PC2);
		else if(a == eS_PORTC3)
		PORTC &= ~(1<<PC3);
		else if(a == eS_PORTC4)
		PORTC &= ~(1<<PC4);
		else if(a == eS_PORTC5)
		PORTC &= ~(1<<PC5);
		else if(a == eS_PORTC6)
		PORTC &= ~(1<<PC6);
		else if(a == eS_PORTD0)
		PORTD &= ~(1<<PD0);
		else if(a == eS_PORTD1)
		PORTD &= ~(1<<PD1);
		else if(a == eS_PORTD2)
		PORTD &= ~(1<<PD2);
		else if(a == eS_PORTD3)
		PORTD &= ~(1<<PD3);
		else if(a == eS_PORTD4)
		PORTD &= ~(1<<PD4);
		else if(a == eS_PORTD5)
		PORTD &= ~(1<<PD5);
		else if(a == eS_PORTD6)
		PORTD &= ~(1<<PD6);
		else if(a == eS_PORTD7)
		PORTD &= ~(1<<PD7);
	}
	else
	{
		if(a == eS_PORTB0)
		PORTB |= (1<<PB0);
		else if(a == eS_PORTB1)
		PORTB |= (1<<PB1);
		else if(a == eS_PORTB2)
		PORTB |= (1<<PB2);
		else if(a == eS_PORTB3)
		PORTB |= (1<<PB3);
		else if(a == eS_PORTB4)
		PORTB |= (1<<PB4);
		else if(a == eS_PORTB5)
		PORTB |= (1<<PB5);
		else if(a == eS_PORTB6)
		PORTB |= (1<<PB6);
		else if(a == eS_PORTB7)
		PORTB |= (1<<PB7);
		else if(a == eS_PORTC0)
		PORTC |= (1<<PC0);
		else if(a == eS_PORTC1)
		PORTC |= (1<<PC1);
		else if(a == eS_PORTC2)
		PORTC |= (1<<PC2);
		else if(a == eS_PORTC3)
		PORTC |= (1<<PC3);
		else if(a == eS_PORTC4)
		PORTC |= (1<<PC4);
		else if(a == eS_PORTC5)
		PORTC |= (1<<PC5);
		else if(a == eS_PORTC6)
		PORTC |= (1<<PC6);
		else if(a == eS_PORTD0)
		PORTD |= (1<<PD0);
		else if(a == eS_PORTD1)
		PORTD |= (1<<PD1);
		else if(a == eS_PORTD2)
		PORTD |= (1<<PD2);
		else if(a == eS_PORTD3)
		PORTD |= (1<<PD3);
		else if(a == eS_PORTD4)
		PORTD |= (1<<PD4);
		else if(a == eS_PORTD5)
		PORTD |= (1<<PD5);
		else if(a == eS_PORTD6)
		PORTD |= (1<<PD6);
		else if(a == eS_PORTD7)
		PORTD |= (1<<PD7);
	}
}



//LCD 8 Bit Interfacing Functions
void Lcd8_Port(char a)
{
	if(a & 1)
	pinChange(D0,1);
	else
	pinChange(D0,0);

	if(a & 2)
	pinChange(D1,1);
	else
	pinChange(D1,0);

	if(a & 4)
	pinChange(D2,1);
	else
	pinChange(D2,0);

	if(a & 8)
	pinChange(D3,1);
	else
	pinChange(D3,0);

	if(a & 16)
	pinChange(D4,1);
	else
	pinChange(D4,0);

	if(a & 32)
	pinChange(D5,1);
	else
	pinChange(D5,0);

	if(a & 64)
	pinChange(D6,1);
	else
	pinChange(D6,0);

	if(a & 128)
	pinChange(D7,1);
	else
	pinChange(D7,0);
}
void Lcd8_Cmd(char a)
{
	pinChange(RS,0);             // => RS = 0
	Lcd8_Port(a);             //Data transfer
	pinChange(EN,1);             // => E = 1
	_delay_ms(1);
	pinChange(EN,0);             // => E = 0
	_delay_ms(1);
}
void Lcd8_Clear()
{
	Lcd8_Cmd(1);
}
void Lcd8_Set_Cursor(char a, char b)
{
	if(a == 1)
	Lcd8_Cmd(0x80 + b);
	else if(a == 2)
	Lcd8_Cmd(0xC0 + b);
}
void Lcd8_Init()
{
	pinChange(RS,0);
	pinChange(EN,0);
	_delay_ms(20);
	///////////// Reset process from datasheet /////////
	Lcd8_Cmd(0x30);
	_delay_ms(5);
	Lcd8_Cmd(0x30);
	_delay_ms(1);
	Lcd8_Cmd(0x30);
	_delay_ms(10);
	/////////////////////////////////////////////////////
	Lcd8_Cmd(0x38);    //function set
	Lcd8_Cmd(0x0C);    //display on,cursor off,blink off
	Lcd8_Cmd(0x01);    //clear display
	Lcd8_Cmd(0x06);    //entry mode, set increment
}
void Lcd8_Write_Char(char a)
{
	pinChange(RS,1);             // => RS = 1
	Lcd8_Port(a);             //Data transfer
	pinChange(EN,1);             // => E = 1
	_delay_ms(1);
	pinChange(EN,0);             // => E = 04
	_delay_ms(1);
}
void Lcd8_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	Lcd8_Write_Char(a[i]);
}
void Lcd8_Shift_Right()
{
	Lcd8_Cmd(0x1C);
}
void Lcd8_Shift_Left()
{
	Lcd8_Cmd(0x18);
}
//End LCD 8 Bit Interfacing Functions

//LCD 4 Bit Interfacing Functions

void Lcd4_Port(char a)
{
	if(a & 1)
	pinChange(D5,1);
	else
	pinChange(D5,0);

	if(a & 2)
	pinChange(D6,1);
	else
	pinChange(D6,0);

	if(a & 4)
	pinChange(D7,1);
	else
	pinChange(D7,0);

	if(a & 8)
	pinChange(B0,1);
	else
	pinChange(B0,0);
}
void Lcd4_Cmd(char a)
{
	pinChange(RS,0);             // => RS = 0
	Lcd4_Port(a);
	pinChange(EN,1);            // => E = 1
	_delay_ms(1);
	pinChange(EN,0);             // => E = 0
	_delay_ms(1);
}
void Lcd4_Clear()
{
	Lcd4_Cmd(0);
	Lcd4_Cmd(1);
}
void Lcd4_Set_Cursor(char a, char b)
{
	char temp,z,y;
	if(a == 1)
	{
		temp = 0x80 + b;
		z = temp>>4;
		y = (0x80+b) & 0x0F;
		Lcd4_Cmd(z);
		Lcd4_Cmd(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b;
		z = temp>>4;
		y = (0xC0+b) & 0x0F;
		Lcd4_Cmd(z);
		Lcd4_Cmd(y);
	}
}
void Lcd4_Init()
{
	Lcd4_Port(0x00);
	_delay_ms(20);
	///////////// Reset process from datasheet /////////
	Lcd4_Cmd(0x03);
	_delay_ms(5);
	Lcd4_Cmd(0x03);
	_delay_ms(11);
	Lcd4_Cmd(0x03);
	/////////////////////////////////////////////////////
	Lcd4_Cmd(0x02);
	Lcd4_Cmd(0x02);
	Lcd4_Cmd(0x08);
	Lcd4_Cmd(0x00);
	Lcd4_Cmd(0x0C);
	Lcd4_Cmd(0x00);
	Lcd4_Cmd(0x06);
}
void Lcd4_Write_Char(char a)
{
	char temp,y;
	temp = a&0x0F;
	y = a&0xF0;
	pinChange(RS,1);             // => RS = 1
	Lcd4_Port(y>>4);             //Data transfer
	pinChange(EN,1);
	_delay_ms(1);
	pinChange(EN,0);
	_delay_ms(1);
	Lcd4_Port(temp);
	pinChange(EN,1);
	_delay_ms(1);
	pinChange(EN,0);
	_delay_ms(1);
}
void Lcd4_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	Lcd4_Write_Char(a[i]);
}
void Lcd4_Shift_Right()
{
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x0C);
}
void Lcd4_Shift_Left()
{
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x08);
}
//End LCD 4 Bit Interfacing Functions
/****************************************************/
/*		Initialize hardware required for LCD		*/
/****************************************************/
void hardwareInitLCD(void)
{
	LCD_CTRL_PORT_DIR |= ((1<<E_PIN) | (1<<RS_PIN));	//LED control pins to output
	LCD_DATA_PORT_DIR = 0xF0;							//LED Data to output
}
/****************************************************/
/*			Initialize all the hardware				*/
/****************************************************/
void hardwareInit(void)
{
	hardwareInitLCD();
	/* Any other initializations should go here */
}

void USART_Init(unsigned int);
void USART_Transmit(unsigned char);
unsigned char USART_Receive(void);
void EnableADC(void);
unsigned int read_adc(unsigned char);

void MOTOR_ON(void)
{
	PORTB |= 0B00100000;
}

void MOTOR_OFF(void)
{
	PORTB &= 0B11011111;
}

void MOTOR_PORT_CONFIG(void)
{
	DDRB |= 0B00100000;
}

void motor_power_status_input(){
	DDRB &= 0B11101111;
}

void init_timer0(void)
{
	TCNT0 = 0x00;
	TCCR0A &= 0xFC;
	TCCR0B &= 0xF7;
	TCCR0B |= 0x07;
}

void init_timer1(void)
{
	TCNT1 = 0x0000;
	TCCR1A &= 0xFC;
	TCCR1B &= 0xF7;
	TCCR1B |= 0x04;
}

int read_water_flow_rate(void) {
	TCNT0 = 0x00;
	TCNT1 = 3036; // for 1s delay
	
	// wait until the timer1 overflows (after 1s) get timer0 count value
	while((TIFR1 & 0b00000001) == 0){}
	int pulse_count = TCNT0;
	
	TIFR1 = 0x01; // reset timer1 overflow flag
	
	return pulse_count;
}

void send_string_to_lcd(char string[], int length) {
	for(int i = 0; i < length; i++) {
		Lcd4_Write_Char(string[i]);
	}
}

void USART_send_int(int number) {
	int V0 = number % 10;
	int V1 = (number/10) % 10;
	int V2 = (number/100) % 10;
	int V3 = (number/1000) % 10;
	
	USART_Transmit(0x30 + V3);
	USART_Transmit(0x30 + V2);
	USART_Transmit(0x30 + V1);
	USART_Transmit(0x30 + V0);
	USART_Transmit(0x0A); USART_Transmit(0x0D);
}

int get_plant_type(int user_input) {
	if (user_input < 20) {
		return 0; // NO VEGITABLE
	} else if (user_input < 320) {
		return 1; // CARROT
	} else if (user_input < 640) {
		return 2; // BRINJAL
	} else {
		return 3; // CABBAGE
	}
}

unsigned int adcValue = 0;
unsigned char V0=0,V1=0,V2=0,V3=0, V4=0;

void pulse_in(){
	
	if((PINB & 0B00010000) != 0){
		
		PORTB |= 0B00100000;
		
		TCNT0 = 0x00;
		TCNT1 = 3036;
		
		while((TIFR1 & 0b00000001) == 0){}
		int pulseCount = TCNT0;
		
		
		V0 = pulseCount %10;
		V1 = (pulseCount/10)%10;
		V2 = (pulseCount/100)%10;
		V3 = (pulseCount/1000)%10;
		
		USART_Transmit('R');
		USART_Transmit('X');
		USART_Transmit(':');
		
		USART_Transmit(0x30 + V3);
		USART_Transmit(0x30 + V2);
		USART_Transmit(0x30 + V1);
		USART_Transmit(0x30 + V0);
		USART_Transmit(0x0A); USART_Transmit(0x0D);
		
		Lcd4_Set_Cursor(2,4);
		char array[8] = {"MOTOR ON"};
		for (int j=0;j<8;j++){
			Lcd4_Write_Char(array[j]);
		}
		
		TIFR1 = 0x01;
	}
	else{
		PORTB &= 0B11011111;
		Lcd4_Set_Cursor(2,3);
		char array[10] = {"PLUG MOTOR"};
		for (int k=0;k<10;k++){
			Lcd4_Write_Char(array[k]);
		}
		_delay_ms(10);
	}
	
}

// volatile unsigned char rxFlag=0;
// volatile unsigned char rxData;

/*
ISR(USART_RX_vect)
{
	rxFlag = 1;
	rxData = UDR0;
}
*/

int main(void)
{
	init_timer0();
	init_timer1();
	motor_power_status_input();
	hardwareInit();			// Initialize all hardware for LCD and other required peripherals
	Lcd4_Init();			// LCD specific software initializations
	Lcd4_Set_Cursor(1,3);	// Set the cursor to first row first column
	send_string_to_lcd("STARTING..", 10);
	_delay_ms(500);
	
	/*
	char array2[3] = {'3','2','1'};
	for (int j=0;j<3;j++){
		Lcd4_Set_Cursor(2,7);
		Lcd4_Write_Char(array2[j]);
		Lcd4_Write_Char('.');
		_delay_ms(1000);
	}
	*/
	_delay_ms(500);
    USART_Init(MYUBRR);
	EnableADC();
	MOTOR_PORT_CONFIG();

    while (1) {
		
		int moisture_level_threshold = 0;
		int user_input = read_adc(1);
		//USART_send_int(user_input);
		
		int plant_type = get_plant_type(user_input);
		
		
		if (plant_type != 0) {
			switch (plant_type) {
				case 1:
					moisture_level_threshold = 400;
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,5);
					send_string_to_lcd("CARROT", 6);
					_delay_ms(100);
					break;
			
				case 2:
					moisture_level_threshold = 500;
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,4);
					send_string_to_lcd("BRINJAL", 7);
					_delay_ms(100);
					break;
			
				case 3:
					moisture_level_threshold = 600;
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,4);
					send_string_to_lcd("CABBAGE", 7);
					_delay_ms(100);
					break;
			}
		
			int moisture_level = read_adc(0);
			USART_send_int(moisture_level);
			
			if (moisture_level > moisture_level_threshold) { // if the moisture level is below the recommended threshold
				
				if ((PINB & 0b00010000) != 0){ // if the motor is powered
					// turn the motor ON
					PORTB |= 0b00100000;
					Lcd4_Set_Cursor(2,4);
					send_string_to_lcd("MOTOR ON", 8);
					
					int total_water_volume = 0;
					
					/*init_timer0();*/
					while (moisture_level > moisture_level_threshold) {
						// wait for 1s
						//_delay_ms(1000);
						TCNT1 = 3036;
						while((TIFR1 & 0b00000001) == 0){}
						TIFR1 = 0x01;
						
						int flow_rate = read_water_flow_rate();
						//USART_send_int(flow_rate);
						// add new water flow volume to total volume
						total_water_volume = total_water_volume + flow_rate * 1;
						//USART_send_int(flow_rate);
						
						// read new moisture level
						moisture_level = read_adc(0);
						//USART_send_int(moisture_level);
					}
					
					// required moisture level achieved. turn the motor OFF
					PORTB &= 0B11011111;
					Lcd4_Set_Cursor(2,4);
					send_string_to_lcd("MOTOR OFF", 9);
					
					// send total water volume serially
					//USART_send_int(total_water_volume);
					
					// wait for an hour to get the next reading
					int i;
					for (i = 0; i < 2; i++) {
						_delay_ms(1000);
					}
					
					
				} else {
					// turn the motor OFF
					PORTB &= 0B11011111;
					
					// show an error message asking to plug the motor to power
					Lcd4_Clear();
					Lcd4_Set_Cursor(2,4);
					send_string_to_lcd("PLUG MOTOR", 10);
					_delay_ms(100);
				}
			}
			
		} else {
			// a valid plant type is not selected
			MOTOR_OFF();
			Lcd4_Clear();
			Lcd4_Set_Cursor(1,0);
			send_string_to_lcd("SELECT VEGETABLE", 16);
			_delay_ms(100);
		}
		
    }
	
	return 0;
}


void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);

	UCSR0C = (3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char USART_Receive(void)
{
	while  (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void EnableADC(void)
{
	ADCSRA |= (1<<ADEN); //Enable ADC
	ADCSRA |= 0x07;	//Set pre-scalar to 128

	ADMUX  = (ADMUX & 0xC0) | 0x00; //set the channel
	ADCSRA |= (1<<ADSC); // single conversion mode , set 1 to start conversion
}

unsigned int read_adc(unsigned char adc_input_pin)
{
	//clear the channel and set the new channel
	//External V_ref, right adjust result, set channel
	ADMUX = (ADMUX & 0xE0) | adc_input_pin;
	ADMUX &= 0x3F;	// 1 to left align the result

	ADCSRA |= (1<<ADSC);	//start conversion

	while (ADCSRA & (1<<ADSC)); // wait for the AD conversion to complete

	return ADC;	//return result
}
