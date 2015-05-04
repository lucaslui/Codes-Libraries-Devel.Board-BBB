/*
 * Arquivo: LCD.h
 * Descrição do arquivo: Arquivo das definições (headers) da classe LCD, na qual faz a criação, acesso e
 * 			 configuração de um display LCD 16x2 com controlador HD44780.
 * Criado em: 25/02/2015
 * Autor: Lucas Lui Motta.
 */
 
#ifndef HEADER_LCD_H_
#define HEADER_LCD_H_

using namespace std;

#define EN_DELAY 500

class LCD {

private:
	int EN, RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7;
	void lcd_toggle_enable();
public:
	LCD() :
			EN(45), RS(44), LCD_D4(66), LCD_D5(67), LCD_D6(68), LCD_D7(69) // Construtor Default.
	{}
	LCD(int EN, int RS, int LCD_D4, int LCD_D5, int LCD_D6, int LCD_D7);
	virtual ~LCD(); // Destrutor Default.

	void init_lcd();
	void lcd_byte(char byte);
	void write_lcd(char caracter);
	void cmd_lcd(char cmd);
	void write_string_lcd(const char arrayFrase[]);
};

#endif /* HEADER_LCD_H_ */
