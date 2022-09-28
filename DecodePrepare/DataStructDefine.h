#pragma once
#ifndef DATASTRUCTDEFINE
#define DATASTRUCTDEFINE
#include"TimeStruct.h"

#define NFREQ 2 /*暂时定义为双频*/

/// <summary>
/// 系统的枚举，北斗+GPS
/// </summary>
enum GNSS_System
{
	GPS, BDS,OtherSYS
};

/// <summary>
/// 目标的信号类型，（只存这些）
/// </summary>
enum Signal_type
{
	L1CA,L2PY,B1I,B3I,OtherSIG
};



/// <summary>
/// /*某个时刻，某颗卫星的观测记录*/
/// </summary>
typedef struct
{
	CommonTime obs_time;

	GNSS_System system;
	Signal_type sigType;

	uint16_t prn;
	double freq;

	double pseRange;
	double carPhase;
	double doppler;
	float snr;

	/*还差精度和通道状态*/

} obs_s;


/// <summary>
/// 一段数据块中的数据
/// </summary>
typedef	struct
{
	uint8_t buff[MAXRAWLEN];//存放所有一字节的未解码数据
	uint16_t msgID;
	uint8_t msgHLen;//头部的长度（字节）
	uint16_t msgLen; //信息body的长度（字节）

	unsigned long nobs;	//一块数据里的观测值个数

	obs_s a_obs[MAXOBSPEREPOCH];//单历元观测值数组

	GPSTime gps_time;
	CommonTime com_time;

}raw_ob;







/// <summary>
/// /*某个时刻，所有卫星的观测记录,/某个历元的观测记录*/
/// </summary>
typedef	struct
{
	CommonTime obs_time;

	/// <summary>
	/// 数组【MAXEPOCH】
	/// </summary>
	obs_s obs_s[MAXSATCOUNT];/*动态分配 观测值条数*/

	unsigned short nSat;/*卫星数*/

	/*定位结果*/


} obs_t;





/// <summary>
/// /*北斗星历类型*/
/// </summary>
typedef struct
{
	unsigned long satID;
	unsigned long week;
	double URA;

	unsigned long health1;
	double tgd1, tgd2;

	unsigned long AODC;
	unsigned long AODE;
	unsigned long toc;
	unsigned long toe;
	double a0, a1, a2;

	double RootA;
	double ecc;
	double omega;
	double delta_N;
	double M_0;
	double Omega_0;
	double Omega_dot;
	double i_dot_0;
	double IDOT;
	double cuc, cus, crc, crs, cic, cis;


} bds_eph_t;

/// <summary>
/// /*GPS星历类型*/
/// </summary>
typedef struct
{
	string prn;
	double tow;
	unsigned long health;
	unsigned long IODE1, IODE2;
	unsigned long week;
	unsigned long z_week;

	double toe;
	double A;
	double deltaN;
	double M_0;
	double ecc;
	double omega;
	double cuc, cus, crc, crs, cic, cis;
	double l_0;

	double I_dot;
	double omega_0;
	double omega_dot;

	unsigned long iodc;

	double toc, tgd;
	
	double af0, af1, af2;

	bool AS; /*Anti_Spoofing*/

	double N;
	double URA;

} gps_eph_t;


typedef struct
{
	CommonTime orentTime;
	/*位置，速度，精度，dop，卫星数等*/


} ore_result;




///电离层参数




#endif // !DATASTRUCT



