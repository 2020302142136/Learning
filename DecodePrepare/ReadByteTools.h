#pragma once
#include <cstdint>
#include <corecrt_memory.h>
#include <cstdio>
#include "ConstDefine.h"
#include"DataStructDefine.h"
#ifndef READBYTETOOLS
#define READBYTETOOLS



#define U1(p) (*((uint8_t *)(p)))
#define I1(p) (*((int8_t  *)(p)))
static uint16_t U2(uint8_t* p) { uint16_t u; memcpy(&u, p, 2); return u; }
static uint32_t U4(uint8_t* p) { uint32_t u; memcpy(&u, p, 4); return u; }
static int32_t  I4(uint8_t* p) { int32_t  i; memcpy(&i, p, 4); return i; }
static float    R4(uint8_t* p) { float    r; memcpy(&r, p, 4); return r; }
static double   R8(uint8_t* p) { double   r; memcpy(&r, p, 8); return r; }


/// <summary>
/// 从文件体里面读取两个数据头标识符AA4412之间的内容
/// </summary>
/// <param name="buff">需要填充的缓存区</param>
/// <param name="fp">文件指针</param>
/// <returns></returns>
bool GetOneBlockData(raw_ob& raw, FILE* fp);

/// <summary>
/// 进行文件数据块的同步帧
/// </summary>
/// <param name="buffer"></param>
/// <param name="data"></param>
/// <returns></returns>
bool sync_header(uint8_t* buffer, uint8_t data);

/* crc-32 parity ---------------------------------------------------------------
* compute crc-32 parity for novatel raw
* args   : unsigned char *buff I data
*          int    len    I      data length (bytes)
* return : crc-32 parity
* notes  : see NovAtel OEMV firmware manual 1.7 32-bit CRC
*-----------------------------------------------------------------------------*/
uint32_t crc32(const uint8_t* buff, int len);

#endif // !READBYTETOOLS

