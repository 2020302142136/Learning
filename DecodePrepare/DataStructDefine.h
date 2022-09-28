#pragma once
#ifndef DATASTRUCTDEFINE
#define DATASTRUCTDEFINE
#include"TimeStruct.h"

#define NFREQ 2 /*��ʱ����Ϊ˫Ƶ*/

/// <summary>
/// ϵͳ��ö�٣�����+GPS
/// </summary>
enum GNSS_System
{
	GPS, BDS,OtherSYS
};

/// <summary>
/// Ŀ����ź����ͣ���ֻ����Щ��
/// </summary>
enum Signal_type
{
	L1CA,L2PY,B1I,B3I,OtherSIG
};



/// <summary>
/// /*ĳ��ʱ�̣�ĳ�����ǵĹ۲��¼*/
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

	/*����Ⱥ�ͨ��״̬*/

} obs_s;


/// <summary>
/// һ�����ݿ��е�����
/// </summary>
typedef	struct
{
	uint8_t buff[MAXRAWLEN];//�������һ�ֽڵ�δ��������
	uint16_t msgID;
	uint8_t msgHLen;//ͷ���ĳ��ȣ��ֽڣ�
	uint16_t msgLen; //��Ϣbody�ĳ��ȣ��ֽڣ�

	unsigned long nobs;	//һ��������Ĺ۲�ֵ����

	obs_s a_obs[MAXOBSPEREPOCH];//����Ԫ�۲�ֵ����

	GPSTime gps_time;
	CommonTime com_time;

}raw_ob;







/// <summary>
/// /*ĳ��ʱ�̣��������ǵĹ۲��¼,/ĳ����Ԫ�Ĺ۲��¼*/
/// </summary>
typedef	struct
{
	CommonTime obs_time;

	/// <summary>
	/// ���顾MAXEPOCH��
	/// </summary>
	obs_s obs_s[MAXSATCOUNT];/*��̬���� �۲�ֵ����*/

	unsigned short nSat;/*������*/

	/*��λ���*/


} obs_t;





/// <summary>
/// /*������������*/
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
/// /*GPS��������*/
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
	/*λ�ã��ٶȣ����ȣ�dop����������*/


} ore_result;




///��������




#endif // !DATASTRUCT



