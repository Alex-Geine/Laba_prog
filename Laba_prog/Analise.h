
#pragma once
#include <iostream>
#define Pi 3.1415926535
#include <math.h>
using namespace std;
//		В этом классет будет описываться фильтр, т.е. его характеристики,
//		количество отсчетов, АЧХ и ФЧХ
//		Так же будут описаны методы для анализа сигнала, а точнее Фурье преобразование, 
//		вычисление АЧХ и ФЧХ 



class Signal_Analise
{
private:
	double
		* ACH,			//АЧХ фильтра
		* FCH,			//ФЧХ фильтра
		* averageACH,	//погрешность ачх
		* averageFCH;	//погрешность фчх
	int
		n, //количество отсчетов
		backACH = 0,	//номера последних элементов в массиве 
		backFCH = 0,
		backACH_av = 0,
		backFCH_av = 0;
	
public:
	Signal_Analise(int N);	// стандартный конструктор	

	void GetACH(double* out);			//возвращает массив ачх
	void GetFCH(double* out);			//возвращает массив фчх
	void GetACH_averege(double* out);	//возвращает массив погрешностей ачх
	void GetFCH_average(double* out);	//возвращает массив погрешностей фчх

	double GetLastACH();			//возвращает последнее ачх
	double GetLastFCH();			//возвращает последнее фчх
	double GetLastACH_averege();	//возвращает последнюю погрешность ачх
	double GetLastFCH_average();	//возвращает последнюю погрешность фчх

	void PushACH(double out);			//засовывает значение в массив
	void PushFCH(double out);			//засовывает значение в массив
	void PushACH_averege(double out);	//засовывает значение в массив
	void PushFCH_average(double out);	//засовывает значение в массив
	

	// *** Быстрое Фурье преобразование сигнала
	// запихиваем сигнал, получаем в те же массивы результат преобразования
	//Rdat - действительная часть сигнала
	//Idat - мнимая 
	//N - чисто отсчетов
	//logN - log2(N)
	//Ft_Flag - (= -1) если прямое преобразование (=1) если обратное
	bool FFT(double* Rdat, double* Idat, int N, int LogN, int Ft_Flag );

	// *** Вычисление АЧХ
	void ACH_Find();

	// *** Вычисление ФЧХ
	// запихиваем массивы с Фурье преобразованием сигналов, получаем ФЧХ на данной частоте(результат кладется в массив FCH класса)
	// Re - для первого сигнала
	// Im - 
	// Re1 - для второго
	// Im1 - 
	// N - количество отсчетов
	void FCH_Find(double* Re, double* Im, double* Re1, double* Im1, int N);
};