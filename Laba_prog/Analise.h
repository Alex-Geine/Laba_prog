
#pragma once
#include <iostream>
#define Pi 3.1415926535
#include <math.h>
using namespace std;
//		� ���� ������� ����� ����������� ������, �.�. ��� ��������������,
//		���������� ��������, ��� � ���
//		��� �� ����� ������� ������ ��� ������� �������, � ������ ����� ��������������, 
//		���������� ��� � ��� 



class Signal_Analise
{
private:
	double
		* ACH,			//��� �������
		* FCH,			//��� �������
		* averageACH,	//����������� ���
		* averageFCH;	//����������� ���
	int
		n, //���������� ��������
		backACH = 0,	//������ ��������� ��������� � ������� 
		backFCH = 0,
		backACH_av = 0,
		backFCH_av = 0;
	
public:
	Signal_Analise(int N);	// ����������� �����������	

	void GetACH(double* out);			//���������� ������ ���
	void GetFCH(double* out);			//���������� ������ ���
	void GetACH_averege(double* out);	//���������� ������ ������������ ���
	void GetFCH_average(double* out);	//���������� ������ ������������ ���

	double GetLastACH();			//���������� ��������� ���
	double GetLastFCH();			//���������� ��������� ���
	double GetLastACH_averege();	//���������� ��������� ����������� ���
	double GetLastFCH_average();	//���������� ��������� ����������� ���

	void PushACH(double out);			//���������� �������� � ������
	void PushFCH(double out);			//���������� �������� � ������
	void PushACH_averege(double out);	//���������� �������� � ������
	void PushFCH_average(double out);	//���������� �������� � ������
	

	// *** ������� ����� �������������� �������
	// ���������� ������, �������� � �� �� ������� ��������� ��������������
	//Rdat - �������������� ����� �������
	//Idat - ������ 
	//N - ����� ��������
	//logN - log2(N)
	//Ft_Flag - (= -1) ���� ������ �������������� (=1) ���� ��������
	bool FFT(double* Rdat, double* Idat, int N, int LogN, int Ft_Flag );

	// *** ���������� ���
	void ACH_Find();

	// *** ���������� ���
	// ���������� ������� � ����� ��������������� ��������, �������� ��� �� ������ �������(��������� �������� � ������ FCH ������)
	// Re - ��� ������� �������
	// Im - 
	// Re1 - ��� �������
	// Im1 - 
	// N - ���������� ��������
	void FCH_Find(double* Re, double* Im, double* Re1, double* Im1, int N);
};