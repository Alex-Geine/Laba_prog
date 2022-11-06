#include"pch.h"
#include "Analise.h"

Signal_Analise::Signal_Analise(int N, double fd, double df) :N(N), fd(fd), df(df) {}

vector<cmplx> Signal_Analise::CreateSign(double A, double f, double y)
{
	vector<cmplx>res;
	for (int i = 0; i < N; i++)res.push_back(cmplx(A * sin(2 * pi * f * i / fd + y), 0));
	return res;
}


void Signal_Analise::CalcFC(double left, double right, double A)
{

	for (double f = left; f <= right; f += df)
	{
		//создали сигнал
		vector<cmplx>input = CreateSign(A, f, 0);
		vector<cmplx>output = CreateSign(2 * A, f, pi);


		//получили фурье
		vector<cmplx>input_f = input;
		vector<cmplx>output_f = output;
		fourea(N, input_f, -1);
		fourea(N, output_f, -1);


		//нашли пик
		//номер €чейки с пиком
		int id = 0;
		double absmax = 0;
		for (int i = 0; i < N; i++)
		{
			double curabs = abs(output_f[i]);
			if (curabs > absmax)
			{
				absmax = curabs;
				id = i;
			}
		}


		double K = absmax / abs(input_f[id]);
		double phase = arg(output_f[id]) - arg(input_f[id]);


		AFC.push_back(K);
		PFC.push_back(phase);
	}


	Draw(left, right);
}


double Signal_Analise::abs(const cmplx& item)
{
	return sqrt(item.re * item.re + item.im * item.im);
}


double Signal_Analise::arg(const cmplx& item)
{
	double phase = asin(item.im / abs(item));
	if (item.re < 0)phase = pi - phase;
	return phase;
}


void Signal_Analise::setAFCHWND(HWND hWnd)
{
	AFCdrv.Create(hWnd);
}
void Signal_Analise::setPFCHWND(HWND hWnd)
{
	PFCdrv.Create(hWnd);
}
void Signal_Analise::Draw(double left, double right)
{
	AFCdrv.DrawGraph(AFC, left, right);
	PFCdrv.DrawGraph(PFC, left, right);

}