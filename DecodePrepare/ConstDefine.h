#pragma once
#ifndef CONSTDEFINE
#define CONSTDEFINE

#define OEM4HLEN    28     
#define MAXFILELEN 40960
#define MAXSATCOUNT 50
#define MAXRAWLEN   16384               /* max length of receiver raw message */
#define MAXOBSPEREPOCH 200				/*一个历元最多的观测值个数*/


#define OEM4SYNC1 0xAA
#define OEM4SYNC2 0x44
#define OEM4SYNC3 0x12

#define pi 3.1415926535897932384626433832795
#define D2R (pi/180.0)                  /* Radians per degree */
#define R2D (180.0/pi)                  /* Degrees per radian */

#define POLYCRC32 0xEDB88320u 

#define ID_RANGECMP     140     
#define ID_RANGE        43      
#define ID_RAWEPHEM     41      
#define ID_BDSEPHEMERIS 1696   
#define ID_GPSEPHEM		7



#define GPSL1CA 1575.42
#define GPSL1CP 1575.42
#define GPSL2CM 1227.6
#define GPSL2P  1227.6
#define GPSL2PY 1227.6
#define GPSL5Q  1176.45

#define BDSB1I 1561.098
#define BDSB1CP 1575.42
#define BDSB2I  1207.14
#define BDSB2AP 1176.45
#define BDSB3I  1268.52

#endif // !CONSTDEFINE

