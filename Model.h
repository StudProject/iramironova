#ifndef __MODEL__
#define __MODEL__
#include <Windows.h>
#define G 10
#define VY_MAX 100

/*! Structure of threads*/

struct TLine
{
	double xj, yj, Xj, Yj;//��������� ���������
	double r, R;//�����
	double o, p;//��������� ���������� ��� ����������
	double M, Mx, My;//������� ����� ��� ������� ����
	double m, mx, my;// � ��� ������
	double nx, ny, Nx, Ny;//��������� ��������� ����������� �����
	double grad, grad1;//���� ������
	double angle, angle1;//� ������� �����
	double E, Ep, e, ep;//�������


};
/*! Structure of left ball*/

struct TBall//��������� ��� ������ ����
{
	double X, Y;//���������� ���������
	double x, y;//����������� ���������
	double m, a;//�����, ���������
	double cosA, sinA;//�������, ����� ����
	double vx, vy;//��������
	bool isSelected;//������
};
/*! Structure of right ball*/
struct TOrb
{
	double X, Y;//���������� ���������
	double x, y;//����������� ���������
	double m, a;//�����, ���������
	double cosA, sinA;//�������, ����� ����
	double vx, vy;//��������
	bool isSelected;//������
};
/*! Structure of center balls*/
struct TBalls
{
	double X, Y;//���������� ���������
	double x, y;//����������� ���������
};
#endif
