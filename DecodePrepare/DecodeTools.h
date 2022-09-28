#pragma once
#ifndef DECODE
#define DECODE
#include"DataStructDefine.h"
#include"ConstDefine.h"
#include"ReadByteTools.h"
#include <fstream>
int DecodeRange(raw_ob& raw);
int DecodeBDSEph(raw_ob& raw);
int DecodeGPSEph(raw_ob& raw);

void TrackingStatus(const uint32_t&status,obs_s& obs);
void PrintDecodeResult(const raw_ob& raw);


#endif // !DECODE

