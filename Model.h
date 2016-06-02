#ifndef __MODEL__
#define __MODEL__
#include <Windows.h>
#define G 10
#define VY_MAX 100

/*! Structure of threads*/

struct TLine
{
	double xj, yj, Xj, Yj;//начальное положение
	double r, R;//длина
	double o, p;//временные переменные для считывания
	double M, Mx, My;//векторы длины для правого шара
	double m, mx, my;// и для левого
	double nx, ny, Nx, Ny;//начальное положение центральных шаров
	double grad, grad1;//углы левого
	double angle, angle1;//и правого шаров
	double E, Ep, e, ep;//энергия


};
/*! Structure of left ball*/

struct TBall//структура для левого шара
{
	double X, Y;//изменяемое положение
	double x, y;//изначальное положение
	double m, a;//масса, ускорение
	double cosA, sinA;//косинус, синус угла
	double vx, vy;//скорость
	bool isSelected;//выбран
};
/*! Structure of right ball*/
struct TOrb
{
	double X, Y;//изменяемое положение
	double x, y;//изначальное положение
	double m, a;//масса, ускорение
	double cosA, sinA;//косинус, синус угла
	double vx, vy;//скорость
	bool isSelected;//выбран
};
/*! Structure of center balls*/
struct TBalls
{
	double X, Y;//изменяемое положение
	double x, y;//изначальное положение
};
#endif
