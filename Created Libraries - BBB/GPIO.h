/*
 * Arquivo: GPIO.h
 * Descrição do arquivo: Arquivo de cabeçalho com as definições da classe GPIO, na qual faz a criação,
 * 			 acesso e configuração dos pinos de próposito geral da beaglebone.
 * Criado em: 02/05/2015
 * Autor: Lucas Lui Motta.
 */

#ifndef HEADER_GPIO_H_
#define HEADER_GPIO_H_

enum state_pin{
	LOW = 0,
	HIGH = 1
};
class GPIO {

public:
	void export_pin(int num_pin);
	void unexport_pin(int num_pin);
	void set_direction(int num_pin, const char direction[]);
	void set_value(int num_pin, state_pin value);
	int get_value(int num_pin);
};

#endif /* HEADER_GPIO_H_ */
