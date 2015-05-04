#include "LCD.h"		// Arquivo Header da classe LCD.
#include <iostream>     // Standart library C++.
#include <unistd.h>     // Biblioteca padrão UNIX sistemas.
#include "GPIO.h" // Biblioteca de Derek Moloy para a Beaglebone Black.

GPIO* gpio_lcd = new GPIO();

LCD::LCD(int EN, int RS, int LCD_D4, int LCD_D5, int LCD_D6, int LCD_D7) {
	try {
		this->EN = EN; // Inicializando o objeto.
		this->RS = RS;
		this->LCD_D4 = LCD_D4;
		this->LCD_D5 = LCD_D5;
		this->LCD_D6 = LCD_D6;
		this->LCD_D7 = LCD_D7;

		gpio_lcd->export_pin(LCD_D4); // Gerando as saidas GPIO pelo script export da beaglebone no caminho /sys
		gpio_lcd->export_pin(LCD_D5); // /class/gpio/export (ex: echo $num_pin > export)
		gpio_lcd->export_pin(LCD_D6);
		gpio_lcd->export_pin(LCD_D7);
		gpio_lcd->set_direction(LCD_D4, "out"); // Setando as direções dos pinos para saída, pelo arquivo
		gpio_lcd->set_direction(LCD_D5, "out"); // Direction da GPIO.
		gpio_lcd->set_direction(LCD_D6, "out");
		gpio_lcd->set_direction(LCD_D7, "out");

		gpio_lcd->export_pin(EN);
		gpio_lcd->export_pin(RS);
		gpio_lcd->set_direction(EN, "out");
		gpio_lcd->set_direction(RS, "out");
	} catch (...) {
		cout << "WARNING: Error with the export !!"; // Caso ocorra um erro na exportação dos Pinos.
	}
}

LCD::~LCD() {
	gpio_lcd->unexport_pin(LCD_D4); // Destrutor responsável por desativar os pinos GPIO pelo scrip arquivo unexport
	gpio_lcd->unexport_pin(LCD_D5); // do caminho /sys/class/gpio/unexport (echo $num_pin > unexport)
	gpio_lcd->unexport_pin(LCD_D6);
	gpio_lcd->unexport_pin(LCD_D7);
	gpio_lcd->unexport_pin(EN);
	gpio_lcd->unexport_pin(RS);
}

void LCD::lcd_toggle_enable() // Liga/Desliga do pino enable para absorção dos dados no barramento do LCD.
{
	usleep(EN_DELAY);
	gpio_lcd->set_value(EN, HIGH);
	usleep(EN_DELAY);
	gpio_lcd->set_value(EN, LOW);
	usleep(EN_DELAY);
}

void LCD::lcd_byte(char byte) {

	gpio_lcd->set_value(LCD_D4, LOW); // Limpando barramento de dados.
	gpio_lcd->set_value(LCD_D5, LOW);
	gpio_lcd->set_value(LCD_D6, LOW);
	gpio_lcd->set_value(LCD_D7, LOW);
	if ((byte & 0x10) == 0x10)
		gpio_lcd->set_value(LCD_D4, HIGH); // Mascarando bits do byte enviado, para o barramento de dados (Parte Alta).
	if ((byte & 0x20) == 0x20)
		gpio_lcd->set_value(LCD_D5, HIGH);
	if ((byte & 0x40) == 0x40)
		gpio_lcd->set_value(LCD_D6, HIGH);
	if ((byte & 0x80) == 0x80)
		gpio_lcd->set_value(LCD_D7, HIGH);

	lcd_toggle_enable();

	gpio_lcd->set_value(LCD_D4, LOW); // Limpando barramento de dados.
	gpio_lcd->set_value(LCD_D5, LOW);
	gpio_lcd->set_value(LCD_D6, LOW);
	gpio_lcd->set_value(LCD_D7, LOW);
	if ((byte & 0x01) == 0x01)
		gpio_lcd->set_value(LCD_D4, HIGH); // Mascarando bits do byte enviado, para o barramento de dados (Parte Baixa).
	if ((byte & 0x02) == 0x02)
		gpio_lcd->set_value(LCD_D5, HIGH);
	if ((byte & 0x04) == 0x04)
		gpio_lcd->set_value(LCD_D6, HIGH);
	if ((byte & 0x08) == 0x08)
		gpio_lcd->set_value(LCD_D7, HIGH);

	lcd_toggle_enable();
}

void LCD::init_lcd() {
	gpio_lcd->set_value(RS, LOW); // RS com valor nível 0 (low) significando que será dado um comando no LCD.
	usleep(3000);
	lcd_byte(0x03);
	usleep(3000);
	lcd_byte(0x03);
	usleep(3000);
	lcd_byte(0x03);
	usleep(3000);
	lcd_byte(0x02);
	usleep(1000);
	gpio_lcd->set_value(RS, LOW); // RS com valor nível 0 (low) significando que será dado um comando no LCD.
	lcd_byte(0x28);
	usleep(2000);
	lcd_byte(0x0C);
	usleep(2000);
}

void LCD::write_lcd(char caracter) {
	gpio_lcd->set_value(RS, HIGH); // RS com valor nível 1 (HIGH) significando que será enviado um caráter
	lcd_byte(caracter);       // para ser impresso.
	usleep(200);
}

void LCD::cmd_lcd(char cmd) {
	gpio_lcd->set_value(RS, LOW);  // RS com valor nível 0 (low) significando que será dado um comando no LCD.
	lcd_byte(cmd);
	usleep(500);
}

void LCD::write_string_lcd(const char *arrayFrase) { // Gerador de frases para escrita de string no LCD.
	int letras = 0, j = 0;
	while (arrayFrase[j] != '\0') { // Percorrendo string em busca do \0 notação para fim de string.
		j++;
		letras++;
	}
	for (int i = 0; i < letras; i++) write_lcd(arrayFrase[i]);
}


