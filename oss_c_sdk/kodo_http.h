/*
 ============================================================================
 Name        : http.h
 Author      : Qiniu.com
 Copyright   : 2012(c) Shanghai Qiniu Information Technologies Co., Ltd.
 Description :
 ============================================================================
 */

#ifndef QINIU_HTTP_H
#define QINIU_HTTP_H

#include "kodo_base.h"

/*============================================================================*/
/* type Qiniu_Auth */

#pragma pack(1)

typedef struct curl_slist Qiniu_Header;

typedef struct _Qiniu_Auth_Itbl {
	Qiniu_Error (*Auth)(void* self, Qiniu_Header** header, const char* url, const char* addition, size_t addlen);
	void (*Release)(void* self);
} Qiniu_Auth_Itbl;

typedef struct _Qiniu_Auth {
	void* self;
	Qiniu_Auth_Itbl* itbl;
} Qiniu_Auth;

QINIU_DLLAPI extern Qiniu_Auth Qiniu_NoAuth;

/*============================================================================*/
/* type Qiniu_Client */

typedef struct _Qiniu_Client {
	void* curl;
	Qiniu_Auth auth;
	Qiniu_Buffer b;
	Qiniu_Buffer respHeader;

	// Use the following field to specify which NIC to use for sending packets.
	const char* boundNic;

	// Use the following field to specify the average transfer speed in bytes per second (Bps)
	// that the transfer should be below during lowSpeedTime seconds for this SDK to consider
	// it to be too slow and abort.
	long lowSpeedLimit;

	// Use the following field to specify the time in number seconds that
	// the transfer speed should be below the logSpeedLimit for this SDK to consider it
	// too slow and abort.
	long lowSpeedTime;
} Qiniu_Client;

/*============================================================================*/
/* func Qiniu_Client_InitNoAuth/InitMacAuth  */

typedef struct _Qiniu_Mac {
	const char* accessKey;
	const char* secretKey;
} Qiniu_Mac;

Qiniu_Auth Qiniu_MacAuth(Qiniu_Mac* mac);

QINIU_DLLAPI extern char* Qiniu_Mac_Sign(Qiniu_Mac* self, char* data);
QINIU_DLLAPI extern char* Qiniu_Mac_SignToken(Qiniu_Mac* self, char* data);

QINIU_DLLAPI extern void Qiniu_Client_InitNoAuth(Qiniu_Client* self, size_t bufSize);
QINIU_DLLAPI extern void Qiniu_Client_InitMacAuth(Qiniu_Client* self, size_t bufSize, Qiniu_Mac* mac);

/*============================================================================*/

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif /* QINIU_HTTP_H */

