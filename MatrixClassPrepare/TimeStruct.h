#pragma once
#ifndef TIMESTRUT
#define TIMESTRUT

#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
/******************
*存放不同时间结构体的定义
*******************/

/******************
*结构体定义
*******************/
struct CommonTime
{
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	double second;

	CommonTime(unsigned short year,
		unsigned short month,
		unsigned short day,
		unsigned short hour,
		unsigned short minute,
		double second
	)
	{
		this->year = year;
		this->month = month;
		this->day = day;
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}

	CommonTime(unsigned short year,
		unsigned short month,
		double day)
	{
		this->year = year;
		this->month = month;

		this->day = (int)day;
		double fracDay = day - (int)day;
		
		this->hour = (int)(fracDay * 24);
		double fracHour = fracDay * 24 - (int)(fracDay * 24);

		this->minute = (int)(fracHour * 60);
		double fracMinute = fracHour * 60 - (int)(fracHour * 60);

		this->second = fracMinute * 60.0;
	}

	void PrintCom()
	{
		cout << year << "年" << month << "月" << day << "日" << hour << "时" << minute << "分" << second << "秒" << endl;

	}

};

struct MJDTime
{
	int days;
	double fracDay;//小数部分天

	MJDTime() {
		days = 0;
		fracDay = 0.0;
	}

	MJDTime(int days,double fracDay)
	{
		this->days = days;
		this->fracDay = fracDay;
	}

	void PrintMJD()
	{
		cout << std::fixed << setprecision(3) << "整数天：" << days << " " << "小数天：" << fracDay << endl;
	}

};


struct GPSTime
{
	unsigned short week;
	double secOfWeek;

	GPSTime()
	{
		week = 0;
		secOfWeek = 0.0;
	}

	GPSTime(unsigned short week,
		double secOfWeek)
	{
		this->week = week;
		this->secOfWeek = secOfWeek;
	}

	void PrintGPST()
	{
		cout << "周：" << week << " " << "周秒：" << secOfWeek << endl;
	}

};

/******************
*函数声明
*******************/
MJDTime Com2MJD(const CommonTime& comTime);
CommonTime MJD2Com(const MJDTime& mjdTime);
MJDTime GPST2MJD(const GPSTime& gpsTime);
GPSTime MJD2GPST(const MJDTime& mjdTime);
GPSTime Com2GPST(const CommonTime& comTime);
CommonTime GPST2Com(const GPSTime& gpsTime);
double GPST2DOY(const GPSTime& gpsTime);
GPSTime DOY2GPST(const double& doy, const unsigned short& year);

GPSTime AddBDSOffset(const GPSTime& gpsTime);


#endif // !TIMESTRUT
