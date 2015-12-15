////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Send priority
#ifndef SP_DEFINED
#define SP_DEFINED
#define SP_IDLE		0
#define SP_LOW		1
#define SP_NORMAL	2
#define SP_HIGH		3
#define SP_ALWAYS	4
#endif

#define MAX_PACKET_SIZE 4096
#define MAX_QUEUE_SIZE	1024

typedef struct {
	DWORD dwSender;
	DWORD dwSize;
	BYTE pData[MAX_PACKET_SIZE];
} sNetPacket;

class INet
{
public:
	INet(){};
	virtual ~INet(){};
	virtual HRESULT Send(DWORD dwRecepient, UINT mID, void * pData, DWORD dwSize, UINT iPriority) = 0;
	virtual HRESULT Receive(UINT mID, void * pData, DWORD dwSize) = 0;
	virtual HRESULT InitDirectPlay() = 0;
	virtual HRESULT CreateSession(const char * lpServerName, const char * lpSessionName, DWORD dwPort) = 0;
	virtual DWORD   GetID() = 0;
	virtual DWORD	QueueGetSize() = 0;
	virtual void	QueuePopFront(sNetPacket * pNetPacket) = 0;
};

class INetLibrary
{
public:

	INetLibrary(){};
	~INetLibrary(){};
	virtual void CreateLocalHost(void) = 0;
	virtual void CreateStdHost(void) = 0;
	
	virtual INet* GetServer() = 0;
	virtual INet* GetClient() = 0;


public:
#if defined(_WIN32) || defined(_WIN64)
	HMODULE m_pModule;
#endif
};
