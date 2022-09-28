#include "ReadByteTools.h"
#include "DataStructDefine.h"
#include <iostream>
using namespace std;

/// <summary>
/// �����ļ����ݿ��ͬ��֡
/// </summary>
/// <param name="buffer"></param>
/// <param name="data"></param>
/// <returns></returns>
bool sync_header(uint8_t* buffer, uint8_t data)
{
	bool syncFlag = false;

	buffer[0] = buffer[1];
	buffer[1] = buffer[2];
	buffer[2] = data;

	if (buffer[0] == OEM4SYNC1 && buffer[1] == OEM4SYNC2 && buffer[2] == OEM4SYNC3)
	{
		syncFlag = true;
	}
	return syncFlag;
}


/// <summary>
/// ���ļ��������ȡ��������ͷ��ʶ��AA4412֮�������
/// </summary>
/// <param name="buff">��Ҫ���Ļ�����</param>
/// <param name="fp">�ļ�ָ��</param>
/// <returns></returns>
bool GetOneBlockData(raw_ob& raw, FILE* fp)
{
	//1.�ҵ�ͬ���ֽ�
	//2.�����ȡ����ͷ��������ĳ��ȣ�ȷ��Ҫ��ȡ��buff����
	//3.���سɹ���ʶ

	//uint8_t buff2[MAXRAWLEN];

	bool flag = false;

	int nbyte = 0;

	for (int i = 0; i < MAXFILELEN; i++)
	{
		int data = fgetc(fp);
		if (sync_header(raw.buff, data))
		{
			nbyte = 3;
			break;//ͬ���ɹ�
		}
		data = 0;
	}

	raw.msgHLen = fgetc(fp);//ͷ���ĳ��ȣ��ֽڣ�
	nbyte++;//(4
	raw.buff[nbyte - 1] = raw.msgHLen;

	for (unsigned short i = nbyte; i < raw.msgHLen; i++)
	{
		raw.buff[i] = fgetc(fp);
	}

	raw.msgLen = U2(raw.buff + 8); //��Ϣbody�ĳ��ȣ��ֽڣ�
	nbyte = raw.msgHLen;//28

	/*msgͷ����Ϣ���˶�ȡ���*/
	if ((raw.msgHLen+ raw.msgLen)>MAXRAWLEN-4/*�۳�crcУ��λ*/)
	{
		flag = false;
		return flag;
	}
	else
	{
		for (unsigned short i = nbyte; i < raw.msgHLen + raw.msgLen; i++)
		{
			raw.buff[i] = fgetc(fp);
		}
	}	

	nbyte = raw.msgHLen + raw.msgLen;
	/*msgͷ��+body����Ϣ���˶�ȡ���*/
	
	for (int i = 0; i < 4; i++)
	{
		raw.buff[nbyte+i] = fgetc(fp);
	}
	/*CRCУ��λҲ��ȡ�ɹ�*/
	
	/*����һ����Ϣ��ĳ�ʼ�����ѱ���ȡ�ɹ�*/
	flag = true;

	return flag;
}

/// <summary>
/// CRC
/// </summary>
/// <param name="buff"></param>
/// <param name="len"></param>
/// <returns></returns>
uint32_t crc32(const uint8_t* buff, int len)
{
	int i, j;
	uint32_t crc = 0;

	for (i = 0; i < len; i++) 
	{
		crc ^= buff[i];
		for (j = 0; j < 8; j++) 
		{
			if (crc & 1) crc = (crc >> 1) ^ POLYCRC32;
			else crc >>= 1;
		}
	}
	return crc;
}