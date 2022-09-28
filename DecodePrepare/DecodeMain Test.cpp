#include<iostream>
#include <string> 
#include <fstream>
#include "DecodeTools.h"
#include "ReadByteTools.h"
#include "DataStructDefine.h"
using namespace std;


int main()
{
	//打开文件
	string path = "NovatelOEM20211114-01.log";
	FILE* fp = fopen(path.c_str(), "rb");



	//获取原始字节数据
	raw_ob raw;
	
	while (!feof(fp))
	{

		//先清空raw数据
		memset(&raw, 0, sizeof(raw));
		GetOneBlockData(raw, fp);//此时文件未关闭，文件指针在上一数据块的末尾

		//cout << U4(raw.buff + ((int)raw.msgHLen + raw.msgLen)) << endl;
		//cout <<  (int)raw.msgHLen<< endl;


		//进行crc校验
		if (crc32(raw.buff, (raw.msgLen + (int)raw.msgHLen)) != U4(raw.buff + ((int)raw.msgHLen + raw.msgLen)))
		{
			cout << "crc check failed." << endl;
			continue;
		}

		//确定消息类型
		int msgType;
		raw.msgID = U2(raw.buff + 4);
		msgType = (U1(raw.buff + 6) >> 4) & 0x3;

		/*if (stat == 20 || week == 0) {

		}*/

		//目前只解这三个
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




