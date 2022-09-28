#include"CoordinateStruct.h"
#include<cmath>

//<returns>返回的BLH中角度单位为：弧度rad，距离单位为：米m</returns>
BLH XYZ2BLH(const XYZ& cartPoint,double a,double f)
{
	double b = 0;
	double l = 0;
	double h = 0;
	double x = cartPoint.x;
	double y = cartPoint.y;
	double z = cartPoint.z;

	double e = sqrt(2.0 * f - f * f);

	

	//B的初值
	double B_0 = atan2(z, sqrt(x * x + y * y));
	double N_0 = a / sqrt(1 - e * e * sin(B_0) * sin(B_0));
	double B_k = atan2((z + N_0 * e * e * sin(B_0)), sqrt(x * x + y * y));

	int iterCount = 0;
	while (fabs(B_0-B_k)>1e-6||iterCount<=10)
	{
		B_0 = B_k;
		N_0 = a / sqrt(1 - e * e * sin(B_0) * sin(B_0));
		B_k = atan2((z + N_0 * e * e * sin(B_0)), sqrt(x * x + y * y));
		iterCount++;
	}

	b = B_k;
	l = atan2(y, x);
	h = sqrt(x * x + y * y) / cos(B_k) - a / sqrt(1 - e * e * sin(B_k) * sin(B_k));

	return BLH(b,l,h);
}
//传入的BLH中角度单位为：弧度rad，距离单位为：米m
XYZ BLH2XYZ(const BLH& geoPoint, double a, double f)
{
	double x = 0;
	double y = 0;
	double z = 0;
	
	double b = geoPoint.b;
	double l = geoPoint.l;
	double h = geoPoint.h;

	double e = sqrt(2.0 * f - f * f);
	double N = a / sqrt(1 - e * e * sin(b) * sin(b));

	x = (N + h) * cos(b) * cos(l);
	y = (N + h) * cos(b) * sin(l);
	z = (N * (1 - e * e) + h) * sin(b);


	return XYZ(x, y, z);
}
