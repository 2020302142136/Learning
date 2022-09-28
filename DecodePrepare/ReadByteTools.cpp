#include "ReadByteTools.h"
#include "DataStructDefine.h"
#include <iostream>
using namespace std;

/// <summary>
/// 进行文件数据块的同步帧
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
/// 从文件体里面读取两个数据头标识符AA4412之间的内容
/// </summary>
/// <param name="buff">需要填充的缓存区</param>
/// <param name="fp">文件指针</param>
/// <returns></returns>
bool GetOneBlockData(raw_ob& raw, FILE* fp)
{
	//1.找到同步字节
	//2.往后获取数据头和数据体的长度，确定要读取的buff长度
	//3.返回成功标识

	//uint8_t buff2[MAXRAWLEN];

	bool flag = false;

	int nbyte = 0;

	for (int i = 0; i < MAXFILELEN; i++)
	{
		int data = fgetc(fp);
		if (sync_header(raw.buff, data))
		{
			nbyte = 3;
			break;//同步成功
		}
		data = 0;
	}

	raw.msgHLen = fgetc(fp);//头部的长度（字节）
	nbyte++;//(4
	raw.buff[nbyte - 1] = raw.msgHLen;

	for (unsigned short i = nbyte; i < raw.msgHLen; i++)
	{
		raw.buff[i] = fgetc(fp);
	}

	raw.msgLen = U2(raw.buff + 8); //信息body的长度（字节）
	nbyte = raw.msgHLen;//28

	/*msg头部信息至此读取完毕*/
	if ((raw.msgHLen+ raw.msgLen)>MAXRAWLEN-4/*扣除crc校验位*/)
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
	/*msg头部+body的信息至此读取完毕*/
	
	for (int i = 0; i < 4; i++)
	{
		raw.buff[nbyte+i] = fgetc(fp);
	}
	/*CRC校验位也读取成功*/
	
	/*至此一个信息块的初始数据已被读取成功*/
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