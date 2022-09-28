#pragma once
#ifndef COORDINATE
#define COORDINATE
#include <iostream>
#include<iomanip>
#include <cmath>
/******************
*�궨��
*******************/
#define R_WGS84  6378137.0          /* Radius Earth [m]; WGS-84  */
#define F_WGS84  1.0/298.257223563  /* Flattening; WGS-84   */
#define R_CGS2K  6378137.0          /* Radius Earth [m]; CGCS2000  */
#define F_CGS2K  1.0/298.257222101  /* Flattening; CGCS2000   */

#define D2R  3.14159265359/180.0
#define R2D  180.0/3.14159265359


using namespace std;
/******************
*��Ų�ͬʱ��ṹ��Ķ���
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
		/// �˴�ֱ��������Ǵ�С��λ�ĽǶȣ���������С��λ�Ƕ�ת�ȷ�����ʾ�ĺ���/����
		/// </summary>
		cout << fixed << setprecision(3) << "B:" << b *R2D<<"��"<< endl;
		cout << fixed << setprecision(3) << "L:" << l *R2D<<"��"<< endl;
		cout << fixed << setprecision(3) << "H:" << h <<"m" << endl;
	}

};


/******************
*��������
*******************/
BLH XYZ2BLH(const XYZ& cartPoint, double a, double f);
XYZ BLH2XYZ(const BLH& geoPoint, double a, double f);


#endif // !COORDINATE

