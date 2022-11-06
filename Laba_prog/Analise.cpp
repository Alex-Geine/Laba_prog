#include"pch.h"
#include "Analise.h"

Signal_Analise::Signal_Analise(int N, double fd, double df) :N(N), fd(fd), df(df) { }

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
		if (f == 0)
		{
			AFC.push_back(0);
			PFC.push_back(0);
			continue;
		}


		fd = 50 * f;
		//создали сигнал
		vector<cmplx>input = CreateSign(A, f, pi);
		vector<cmplx>output = CreateSign(A/f, f, pi/f);

		
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
		phase = resize(phase);

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
	double phase = acos(item.re / abs(item));
	if (item.im < 0)phase += 2 * pi;
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


double Signal_Analise::resize(double phase)
{
	double k = phase / (2 * pi);
	k = int(k) * 2 * pi;
	phase -= k;
	if (phase < 0)phase += 2 * pi;
	return phase;
}