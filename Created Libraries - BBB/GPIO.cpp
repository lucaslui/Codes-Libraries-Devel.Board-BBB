/*
 * Arquivo: GPIO.cpp
 * Descrição do arquivo: Arquivo do código da classe GPIO, na qual faz a criação, acesso e
 * 						 configuração dos pinos de próposito geral da beaglebone.
 * Criado em: 02/05/2015
 * Autor: Lucas Lui Motta.
 */


#include "GPIO.h"
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


void GPIO::export_pin(int num_pin){
	ofstream fout("/sys/class/gpio/export", ios::out);
	fout << num_pin;
	fout.close();
}

void GPIO::unexport_pin(int num_pin){
	ofstream fout("/sys/class/gpio/unexport", ios::out);
	fout << num_pin;
	fout.close();
}

void GPIO::set_direction(int num_pin, const char direction[]){
	int i = 0;
	char buffer[100];
	sprintf(buffer, "/sys/class/gpio/gpio%d/direction", num_pin);
	ofstream fout;
	fout.open(buffer, ios::out);
	do{
		fout.put(direction[i]);
		i++;
	}while(direction[i]);
	fout.close();
}

void GPIO::set_value(int num_pin, state_pin value){
	char buffer[100];
	sprintf(buffer, "/sys/class/gpio/gpio%d/value", num_pin);
	ofstream fout(buffer, ios::out);
	fout << value;
	fout.close();
}

int GPIO::get_value(int num_pin){
	char buffer[100], temp[5];
	int temp_int;
	sprintf(buffer, "/sys/class/gpio/gpio%d/value", num_pin);
	ifstream fin(buffer, ios::in);
	fin >> temp;
	fin.close();
	temp_int = atoi(temp);
	return temp_int;
}


