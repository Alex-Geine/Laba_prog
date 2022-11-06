#pragma once
#include <iostream>
#include"cmplx.h"
#include"Drawer.h"
using namespace std;


//����� ��
const double pi = 4 * atan(1);


//		� ���� ������� ����� ����������� ������, �.�. ������������������ �������� �������,
//		��� �������������� (���������� ��������, ������� �������������),
//		����� ��������� ����� �������������� �� �������, ��� � ���
//		��� �� ����� ������� ������ ��� ������� �������, � ������ ����� ��������������, 
//		���������� ��� � ��� 


class Signal_Analise
{
private:
	//���������� �������� 
	int N;
	
	//������� �������������
	double fd;
	//��� �� ��������
	double df;

	//������ �������� ���
	vector<double>AFC;
	//������ �������� ���
	vector<double>PFC;


	Drawer AFCdrv;
	Drawer PFCdrv;
	
public:
	Signal_Analise(int N, double fd, double df);	// ����������� �����������	


protected:
	//������� ������ �� ���������, ������� � ����
	vector<cmplx> CreateSign(double A, double f, double y);
	//������ ������������ �����
	double abs(const cmplx& item);
	//���� ������������ �����
	double arg(const cmplx& item);
	// ������ ���� � [0, 2pi]
	double resize(double phase);


public:
	//���������� �� � ��������� ������ [left, right]
	void CalcFC(double left, double right, double A);

	void setAFCHWND(HWND hWnd);
	void setPFCHWND(HWND hWnd);
	void Draw(double left, double right);
};



