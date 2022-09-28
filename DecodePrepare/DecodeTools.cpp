#include "DecodeTools.h"
#include<vector>

/// <summary>
/// 跳过header，解码具体body数据
/// 该函数解码Range数据
/// </summary>
/// <param name="raw"></param>
/// <returns></returns>
int DecodeRange(raw_ob& raw)
{
	uint8_t* p = raw.buff;
	//这里处理头里的内容
	raw.gps_time.week = U2(p + 14);
	raw.gps_time.secOfWeek = U4(p + 16)*0.001;
	raw.com_time = GPST2Com(raw.gps_time);
	//raw.com_time.PrintCom();



	//这里开始处理体内容
	p = raw.buff + raw.msgHLen;
	raw.nobs = U4(p);

	vector<obs_s> v_obs;

	for (int i = 0; i < raw.nobs; i++)
	{
		obs_s one_obs;
		memset(&one_obs, 0, sizeof(one_obs));//结构体数据置零

		one_obs.prn = U2(p + 4);
		one_obs.pseRange = R8(p + 8);
		one_obs.carPhase = R8(p + 20);
		one_obs.doppler = R4(p + 32);
		one_obs.snr = R4(p + 36);
		unsigned long tr_status = U4(p + 44);
		TrackingStatus(tr_status, one_obs);
		//只识别GPS和BDS的卫星
		//只识别GPS的1 2频点 和BDS的2 6频点
		if (one_obs.system==GPS||one_obs.system==BDS)
		{
			if (one_obs.sigType==L1CA||
				one_obs.sigType==L2PY||
				one_obs.sigType==B1I||
				one_obs.sigType==B3I)
			{
				v_obs.push_back(one_obs);
			}
		}
		p += 44;//寻找下一条记录
		
	}
	//把向量的数据转移到数组里
	for (int i = 0; i < v_obs.size(); i++)
	{
		raw.a_obs[i] = v_obs[i];
	}
	raw.nobs = v_obs.size();
	
	//输出观测数据
	PrintDecodeResult(raw);


	return 0;
}

int DecodeBDSEph(raw_ob& raw)
{




	return 0;
}

int DecodeGPSEph(raw_ob& raw)
{
	uint8_t* p = raw.buff;
	//这里处理头里的内容
	raw.gps_time.week = U2(p + 14);
	raw.gps_time.secOfWeek = U4(p + 16) * 0.001;
	raw.com_time = GPST2Com(raw.gps_time);


	return 0;
}


void TrackingStatus(const uint32_t& status, obs_s& obs)
{
	//卫星系统
	int satsys = (status >> 16) & 7;
	//信号类型
	int sigtype = (status >> 21) & 0x1F;

	if (satsys==0)
	{
		obs.system = GPS;
		switch (sigtype)
		{
		case 0:obs.freq = GPSL1CA; obs.sigType = L1CA; break;
		case 5:obs.freq = GPSL2P;  obs.sigType = OtherSIG; break;
		case 9:obs.freq = GPSL2PY; obs.sigType = L2PY; break;
		case 14:obs.freq = GPSL5Q; obs.sigType = OtherSIG; break;
		case 16:obs.freq = GPSL1CP; obs.sigType = OtherSIG; break;
		case 17:obs.freq = GPSL2CM; obs.sigType = OtherSIG; break;
		default:obs.freq = 0.0; obs.sigType = OtherSIG;
			break;
		}
	}
	else if(satsys==4)
	{
		obs.system = BDS;
		switch (sigtype)
		{
		case 0:obs.freq = BDSB1I; obs.sigType = B1I; break;
		case 1:obs.freq = BDSB2I; obs.sigType = OtherSIG; break;
		case 2:obs.freq = BDSB3I; obs.sigType = B3I; break;
		case 4:obs.freq = BDSB1I; obs.sigType = B1I; break;
		case 5:obs.freq = BDSB2I; obs.sigType = OtherSIG; break;
		case 6:obs.freq = BDSB3I; obs.sigType = B3I; break;
		case 7:obs.freq = BDSB1CP; obs.sigType = OtherSIG; break;
		case 9:obs.freq = BDSB2AP; obs.sigType = OtherSIG; break;
		default:obs.freq = 0.0; obs.sigType = OtherSIG;
			break;
		}
	}
	else
	{
		obs.system = OtherSYS;
		obs.sigType = OtherSIG;
	}
}


//输出一块/一历元的观测数据
void PrintDecodeResult(const raw_ob& raw)
{
	ofstream ofs;
	ofs.open("decodedObsData.txt", ios::app);

	/*输出代码*/
	ofs << "> " 
		<<setw(5)<<setfill(' ') << raw.com_time.year << " "
		<< setw(2) << setfill(' ') << raw.com_time.month << " "
		<< setw(2) << setfill(' ') << raw.com_time.day << " "
		<< setw(2) << setfill(' ') << raw.com_time.hour << " "
		<< setw(2) << setfill(' ') << raw.com_time.minute << " "
		<< fixed << setprecision(7) << setw(10) << raw.com_time.second << " " << endl;
	/*补一个Sat的数量*/

	GNSS_System currentSys = OtherSYS;
	uint16_t currentPrn;
	string sys_prn;
	for (int i = 0; i <raw.nobs; i++)
	{
		if (raw.a_obs[i].system!=currentSys||raw.a_obs[i].prn!=currentPrn)
		{
			currentSys = raw.a_obs[i].system;
			currentPrn = raw.a_obs[i].prn;
			if (currentSys == GPS)
			{
				sys_prn = "G";
			}
			else if (currentSys == BDS)
			{
				sys_prn = "C";
			}
			
			ofs << setw(1) << sys_prn; 
			ofs << setw(2) << setfill('0') << raw.a_obs[i].prn << " ";
		}
			
		ofs << setw(12) << setfill(' ') << fixed << setprecision(3) << raw.a_obs[i].pseRange << "  "
			<< setw(15) << setfill(' ') << fixed << setprecision(3) << -raw.a_obs[i].carPhase << "      "
			<< setw(9) << setfill(' ') << fixed << setprecision(3) << raw.a_obs[i].doppler << "          "
			<< setw(6) << setfill(' ') << fixed << setprecision(3) << raw.a_obs[i].snr << "    ";

		//这个地方要保证a_obs的容量至少比nobs大1
		if (raw.a_obs[i+1].system != currentSys || raw.a_obs[i+1].prn != currentPrn)
		{
			ofs << endl;
		}	
		
	}

	ofs.close();
}