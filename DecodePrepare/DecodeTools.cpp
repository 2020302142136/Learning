#include "DecodeTools.h"
#include<vector>

/// <summary>
/// ����header���������body����
/// �ú�������Range����
/// </summary>
/// <param name="raw"></param>
/// <returns></returns>
int DecodeRange(raw_ob& raw)
{
	uint8_t* p = raw.buff;
	//���ﴦ��ͷ�������
	raw.gps_time.week = U2(p + 14);
	raw.gps_time.secOfWeek = U4(p + 16)*0.001;
	raw.com_time = GPST2Com(raw.gps_time);
	//raw.com_time.PrintCom();



	//���￪ʼ����������
	p = raw.buff + raw.msgHLen;
	raw.nobs = U4(p);

	vector<obs_s> v_obs;

	for (int i = 0; i < raw.nobs; i++)
	{
		obs_s one_obs;
		memset(&one_obs, 0, sizeof(one_obs));//�ṹ����������

		one_obs.prn = U2(p + 4);
		one_obs.pseRange = R8(p + 8);
		one_obs.carPhase = R8(p + 20);
		one_obs.doppler = R4(p + 32);
		one_obs.snr = R4(p + 36);
		unsigned long tr_status = U4(p + 44);
		TrackingStatus(tr_status, one_obs);
		//ֻʶ��GPS��BDS������
		//ֻʶ��GPS��1 2Ƶ�� ��BDS��2 6Ƶ��
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
		p += 44;//Ѱ����һ����¼
		
	}
	//������������ת�Ƶ�������
	for (int i = 0; i < v_obs.size(); i++)
	{
		raw.a_obs[i] = v_obs[i];
	}
	raw.nobs = v_obs.size();
	
	//����۲�����
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
	//���ﴦ��ͷ�������
	raw.gps_time.week = U2(p + 14);
	raw.gps_time.secOfWeek = U4(p + 16) * 0.001;
	raw.com_time = GPST2Com(raw.gps_time);


	return 0;
}


void TrackingStatus(const uint32_t& status, obs_s& obs)
{
	//����ϵͳ
	int satsys = (status >> 16) & 7;
	//�ź�����
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


//���һ��/һ��Ԫ�Ĺ۲�����
void PrintDecodeResult(const raw_ob& raw)
{
	ofstream ofs;
	ofs.open("decodedObsData.txt", ios::app);

	/*�������*/
	ofs << "> " 
		<<setw(5)<<setfill(' ') << raw.com_time.year << " "
		<< setw(2) << setfill(' ') << raw.com_time.month << " "
		<< setw(2) << setfill(' ') << raw.com_time.day << " "
		<< setw(2) << setfill(' ') << raw.com_time.hour << " "
		<< setw(2) << setfill(' ') << raw.com_time.minute << " "
		<< fixed << setprecision(7) << setw(10) << raw.com_time.second << " " << endl;
	/*��һ��Sat������*/

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

		//����ط�Ҫ��֤a_obs���������ٱ�nobs��1
		if (raw.a_obs[i+1].system != currentSys || raw.a_obs[i+1].prn != currentPrn)
		{
			ofs << endl;
		}	
		
	}

	ofs.close();
}