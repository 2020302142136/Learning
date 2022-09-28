#pragma once
#ifndef COORDINATE
#define COORDINATE
#include <iostream>
#include<iomanip>
#include <cmath>
/******************
*宏定义
*******************/
#define R_WGS84  6378137.0          /* Radius Earth [m]; WGS-84  */
#define F_WGS84  1.0/298.257223563  /* Flattening; WGS-84   */
#define R_CGS2K  6378137.0          /* Radius Earth [m]; CGCS2000  */
#define F_CGS2K  1.0/298.257222101  /* Flattening; CGCS2000   */

#define D2R  3.14159265359/180.0
#define R2D  180.0/3.14159265359


using namespace std;
/******************
*存放不同时间结构体的定义
*******************/
struct XYZ
{
	double x;
	double y;
	double z;

	XYZ(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		
	}

	void PrintXYZ()
	{
		cout << fixed << setprecision(3) << "X:" << x << endl;
		cout << fixed << setprecision(3) << "Y:" << y << endl;
		cout << fixed << setprecision(3) << "Z:" << z << endl;
	}

};

struct BLH
{
	double b;
	double l;
	double h;

	BLH(double b, double l, double h)
	{
		this->b = b;
		this->l = l;
		this->h = h;
	}

	void PrintBLH()
	{
		/// <summary>
		/// 此处直接输出的是带小数位的角度，后续加上小数位角度转度分秒显示的函数/功能
		/// </summary>
		cout << fixed << setprecision(3) << "B:" << b *R2D<<"°"<< endl;
		cout << fixed << setprecision(3) << "L:" << l *R2D<<"°"<< endl;
		cout << fixed << setprecision(3) << "H:" << h <<"m" << endl;
	}

};


/******************
*函数声明
*******************/
BLH XYZ2BLH(const XYZ& cartPoint, double a, double f);
XYZ BLH2XYZ(const BLH& geoPoint, double a, double f);


#endif // !COORDINATE

