#pragma once
#ifndef TIMESTRUT
#define TIMESTRUT

#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
/******************
*��Ų�ͬʱ��ṹ��Ķ���
*******************/

/******************
*�ṹ�嶨��
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
		cout << year << "��" << month << "��" << day << "��" << hour << "ʱ" << minute << "��" << second << "��" << endl;

	}

};

struct MJDTime
{
	int days;
	double fracDay;//С��������

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
		cout << std::fixed << setprecision(3) << "�����죺" << days << " " << "С���죺" << fracDay << endl;
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
		cout << "�ܣ�" << week << " " << "���룺" << secOfWeek << endl;
	}

};

/******************
*��������
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
