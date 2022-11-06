#pragma once
#include <iostream>
#include"cmplx.h"
#include"Drawer.h"
using namespace std;


//Число пи
const double pi = 4 * atan(1);


//		В этом классет будет описываться сигнал, т.е. последовательность отсчетов сигнала,
//		его характеристики (количество отсчетов, частота дискретизации),
//		будет храниться фурье преобразование от сигнала, АЧХ и ФЧХ
//		Так же будут описаны методы для анализа сигнала, а точнее Фурье преобразование, 
//		вычисление АЧХ и ФЧХ 


class Signal_Analise
{
private:
	//количество отсчетов 
	int N;
	
	//частота дискретизации
	double fd;
	//шаг по частотам
	double df;

	//Вектор значений АЧХ
	vector<double>AFC;
	//Вектор значений ФЧХ
	vector<double>PFC;


	Drawer AFCdrv;
	Drawer PFCdrv;
	
public:
	Signal_Analise(int N, double fd, double df);	// стандартный конструктор	


protected:
	//Создает сигнал по Амплитуде, частоте и фазе
	vector<cmplx> CreateSign(double A, double f, double y);
	//Модуль комлпексного числа
	double abs(const cmplx& item);
	//Фаза комплексного числа
	double arg(const cmplx& item);
	// сводит фазу к [0, 2pi]
	double resize(double phase);


public:
	//Вычисление ЧХ в диапазоне частот [left, right]
	void CalcFC(double left, double right, double A);

	void setAFCHWND(HWND hWnd);
	void setPFCHWND(HWND hWnd);
	void Draw(double left, double right);
};



