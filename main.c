#include <at89c5131.h>
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions
#include <stdio.h>






sbit LED=P1^7;

code const char my_list[][7] = {"ant", "rabbit", "black","the","and","you","that","was","for","are","with","his","they","this","have","from","one","had","word","but","not","what","all","were","when","your","can","said","there","use","each","which","she","how","their","will","other","about","out","many","then","them","these","some","her","would","make","like","him","into","time","has","look","two","more","write","see","number","way","could","people","than","first","water","been","call","who","oil","now","find","long","down","day","did","get","come","made","may","part"};


//const char my_list[2][];
int random_number ;
int length_counter = 0;
unsigned int len_word=sizeof(my_list[0])/sizeof(char);
unsigned int i =0;
char ch=0;
unsigned int misguess_counter = 0;
int matched = 0;
char s[]={0,'\0'};
int win = 0;
int guessed_chars = 0;
int lcd_tracker = 128;

//Main function
void main(void)
{
	while(1){
	random_number = (rand()%77);
	length_counter = 0;
	for(i=0;i<7;i++){
		if(my_list[random_number][i] < 123 && my_list[random_number][i] > 96 ){
		length_counter++;
		}
	}
	len_word = length_counter + 1;
	//Initialize port P1 for output from P1.7-P1.4
	P1 = 0x0F;
	
	//Call initialization functions
	lcd_init();
	uart_init();
	
	//These strings will be printed in terminal software
	transmit_string("Type and guess the word\r\n");
  transmit_string(my_list[random_number]);

	

	 
	lcd_cmd(0x80);	
	for( i=1;i<len_word;i++){
		lcd_write_char('_');	
	}
	
	misguess_counter = 0;
	win = 0;
	lcd_cmd(0xC0);																				//print line 2 as number of wrong attempt
	lcd_write_string("Wrong Guesses: ");
	s[0]=48 + misguess_counter;
	lcd_write_string(s);
	
	
	
	while(misguess_counter <= 5 && win == 0)
	{
			
		ch = receive_char();
		matched = '0'	;
		
					 
					for(i=0;i<len_word;i++){
						lcd_tracker = 128;
						
							if (ch== my_list[random_number][i]){
								matched = '1'	;
								lcd_tracker = lcd_tracker + i;
								guessed_chars = guessed_chars + 1;
								lcd_cmd(lcd_tracker);
								lcd_write_char(ch);
											
							}
							
					}
					if (matched == '0'){
							misguess_counter = misguess_counter + 1;
					}
					if(guessed_chars>=len_word-1){	
					win=1;
					}
					
					if(misguess_counter > 5){
		transmit_string("You lost. The word was:");
	  transmit_string(my_list[random_number]);
		transmit_string("\r\n Press Reset to play again\r\n");
						
		
	}
	
	if(win == 1){
	transmit_string("You won. The word was:");
	  transmit_string(my_list[random_number]);
		transmit_string("\r\n Press Reset to play again\r\n");
	
		
	}
	
					s[0]=48+ misguess_counter;
					lcd_cmd(0xC0);
					lcd_write_string("Wrong guesses: ");
					s[0]=48+ misguess_counter;
					lcd_write_string(s);
				
		
	}
}
	}
