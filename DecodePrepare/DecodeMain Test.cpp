#include<iostream>
#include <string> 
#include <fstream>
#include "DecodeTools.h"
#include "ReadByteTools.h"
#include "DataStructDefine.h"
using namespace std;


int main()
{
	//���ļ�
	string path = "NovatelOEM20211114-01.log";
	FILE* fp = fopen(path.c_str(), "rb");



	//��ȡԭʼ�ֽ�����
	raw_ob raw;
	
	while (!feof(fp))
	{

		//�����raw����
		memset(&raw, 0, sizeof(raw));
		GetOneBlockData(raw, fp);//��ʱ�ļ�δ�رգ��ļ�ָ������һ���ݿ��ĩβ

		//cout << U4(raw.buff + ((int)raw.msgHLen + raw.msgLen)) << endl;
		//cout <<  (int)raw.msgHLen<< endl;


		//����crcУ��
		if (crc32(raw.buff, (raw.msgLen + (int)raw.msgHLen)) != U4(raw.buff + ((int)raw.msgHLen + raw.msgLen)))
		{
			cout << "crc check failed." << endl;
			continue;
		}

		//ȷ����Ϣ����
		int msgType;
		raw.msgID = U2(raw.buff + 4);
		msgType = (U1(raw.buff + 6) >> 4) & 0x3;

		/*if (stat == 20 || week == 0) {

		}*/

		//Ŀǰֻ��������
		switch (raw.msgID) 
		{
		case ID_RANGE:			DecodeRange	(raw);	break;
		case ID_BDSEPHEMERIS:	DecodeBDSEph(raw);	break;
		case ID_GPSEPHEM:		DecodeGPSEph(raw);	break;
		default:									break;
		}
	}
	

	fclose(fp);

	
}




