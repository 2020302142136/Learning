#include"TimeStruct.h"

MJDTime Com2MJD(const CommonTime& comTime)
{
	double days;
	double fracDay;

	unsigned short y;
	unsigned short m;
	if (comTime.month<=2)
	{
		y = comTime.year - 1;
		m = comTime.month + 12;
	}
	else if(comTime.month>2)
	{
		y = comTime.year;
		m = comTime.month;
	}

	double UT = comTime.hour + (comTime.minute / 60.0) + (comTime.second / 3600.0);

	days = floor(365.25 * y) + floor(30.6001 * (m + 1)) + comTime.day + UT / 24.0 + 1720981.5;

	days = days - 2400000.5;
	fracDay = days - (int)(days);

	return MJDTime((int)days, fracDay);
}
CommonTime MJD2Com(const MJDTime& mjdTime)
{
	MJDTime jd = MJDTime(mjdTime.days + 2400000, mjdTime.fracDay + 0.5);
	//调整小数位
	if (jd.fracDay>=1.0)
	{
		int addToDays = (int)jd.fracDay;
		jd.fracDay -= addToDays;
		jd.days += addToDays;
	}
	int a = (int)(jd.days + jd.fracDay + 0.5);
	int b = a + 1537;
	int c = (int)((b - 122.1) / 365.25);
	int d = (int)(365.25 * c);
	int e = (int)((b - d) / 30.6001);
	double D = b - d - (int)(30.6001 * e) + ((jd.days + jd.fracDay + 0.5) - a);
	unsigned short M = e - 1 - 12 * (int)(e / 14);
	unsigned short Y = c - 4715 - (int)((7 + M) / 10);

	return CommonTime(Y,M,D);
}
GPSTime MJD2GPST(const MJDTime& mjdTime)
{
	unsigned short week;
	week = (int)((mjdTime.days - 44244) / 7.0);
	double secOfWeek = (mjdTime.days + mjdTime.fracDay - 44244 - week * 7) * 86400.0;

	return GPSTime(week,secOfWeek);
}
MJDTime GPST2MJD(const GPSTime& gpsTime)
{
	double mjd = 44244 + gpsTime.week * 7 + gpsTime.secOfWeek / 86400.0;

	return MJDTime((int)mjd, mjd - (int)mjd);
}
GPSTime Com2GPST(const CommonTime& comTime)
{
	MJDTime mjd = Com2MJD(comTime);
	GPSTime gps = MJD2GPST(mjd);
	return gps;
}
CommonTime GPST2Com(const GPSTime& gpsTime)
{
	MJDTime mjd = GPST2MJD(gpsTime);
	CommonTime com = MJD2Com(mjd);
	return com;
}
double GPST2DOY(const GPSTime& gpsTime)
{
	CommonTime com = GPST2Com(gpsTime);
	unsigned short month = com.month;
	unsigned short year = com.year;
	unsigned short day = com.day;

	double N = floor(month * 275 / 9.0) -
		floor((month + 9) / 12.0) * (floor((year - 4 * floor(year / 4) + 2) / 3.0) + 1)
		+ day - 30;


	return N;
}
GPSTime DOY2GPST(const double& doy,const unsigned short& year)
{
	//有个疑惑，年积日是否要考虑小数，从而精确到时分秒？
	
	unsigned short c_year = year;
	unsigned short c_month;
	double c_day;


	int monthDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year%4==0&&year%100!=0)||year%400==0)
	{
		//该年二月份有29天，一整年有366天
		monthDay[1] = 29;
	}
	int monthSumDay[12];
	int sum = 0;
	for (int i = 0; i < 12; i++)
	{
		sum += monthDay[i];
		monthSumDay[i] = sum;
	}

	if (doy <= monthDay[0])
	{
		c_day = doy;
		c_month = 1;

	}

	for (int i = 0; i < 11; i++)
	{
		if (doy>=monthSumDay[i]&&doy<=monthSumDay[i+1])
		{
			c_day = doy - monthSumDay[i];
			c_month = i + 2;
			break;
		}
		
	}

	CommonTime com = CommonTime(c_year, c_month, c_day);



	return GPSTime(Com2GPST(com));
}

GPSTime AddBDSOffset(const GPSTime& gpsTime)
{
	return GPSTime(gpsTime.week + 1356, gpsTime.secOfWeek + 14);
}