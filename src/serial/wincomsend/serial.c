#include <stdio.h>
#include <windows.h>
#include "serial.h"



PORT OpenPort(const char * data)
{


	HANDLE hComm;
	//TCHAR comname[100];
	//wsprintf(comname, TEXT("\\\\.\\COM%d"), idx);
	hComm = CreateFile(data,            //port name
		GENERIC_READ | GENERIC_WRITE, //Read/Write
		0,            // No Sharing
		NULL,         // No Security
		OPEN_EXISTING,// Open existing port only
		0,            // Non Overlapped I/O
		NULL);        // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE)
		return NULL;
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout =10;
	timeouts.ReadTotalTimeoutConstant =10;
	timeouts.ReadTotalTimeoutMultiplier =10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier =50;

	if (SetCommTimeouts(hComm, &timeouts) == FALSE)
		return NULL;

	if (SetCommMask(hComm, EV_RXCHAR) == FALSE)
		return NULL;

	printf("open%s ok\r\n",data);

		  COMMTIMEOUTS xxx;
GetCommTimeouts(hComm,&xxx);


	return hComm;
}

void ClosePort(PORT com_port)
{
	CloseHandle(com_port);
}

int SetPortBoudRate(PORT com_port, int rate)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.BaudRate = rate;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}

int SetPortDataBits(PORT com_port, int bits)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.ByteSize = bits;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}

int SetPortStopBits(PORT com_port, int bits)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.StopBits = bits;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}


	//默认为无校验。NOPARITY 0； ODDPARITY 1；EVENPARITY 2；MARKPARITY 3；SPACEPARITY 4
int SetPortParity(PORT com_port, int parity)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return FALSE;
	dcbSerialParams.Parity = parity;
	Status = SetCommState(com_port, &dcbSerialParams);
	return Status;
}

int GetPortBoudRate(PORT com_port)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.BaudRate;
}

int GetPortDataBits(PORT com_port)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.ByteSize;
}

int GetPortStopBits(PORT com_port)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.StopBits;
}

int GetPortParity(PORT com_port)
{
	DCB dcbSerialParams = { 0 };
	BOOL Status;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	Status = GetCommState(com_port, &dcbSerialParams);
	if (Status == FALSE)
		return -1;
	return dcbSerialParams.Parity;
}

int SendData(PORT com_port, const char * data)
{
	DWORD  dNoOFBytestoWrite = strlen(data);
	DWORD  dNoOfBytesWritten;
	BOOL Status = WriteFile(com_port,
				data,
				dNoOFBytestoWrite,
				&dNoOfBytesWritten,
				0);
	if (Status == FALSE)
	{
			return -1;
	}
	else
	{
		printf("%s\n",data);
	}

	return dNoOfBytesWritten;
}

int ReciveData(PORT com_port, char * data,int len)
{
	DWORD dwEventMask;
	DWORD NoBytesRead;

	BOOL Status = WaitCommEvent(com_port, &dwEventMask, 0);
	if (Status == FALSE)
    {
		return FALSE;
	}
	Status = ReadFile(com_port, data, len, &NoBytesRead, 0);
	data[NoBytesRead] = 0;

	if (Status == FALSE)
    {
		return FALSE;
	}
	else
    {
		printf("%s\n",data);
	}

	return TRUE;
}


PORT serial_init(const char * data, int rate, int databits, int stopbits, int parity)
{
    int ret = 0;
   PORT com_port;
   com_port = OpenPort(data);
   if (com_port == INVALID_HANDLE_VALUE)
   {
       printf("open%s fail\n", data);
       return NULL;
   }
   ret = SetPortBoudRate(com_port, rate);
   if(ret == FALSE)
   {
       printf("set%s band fail\n", data);
       return NULL;
   }
   ret = SetPortDataBits(com_port, databits);
   if(ret == FALSE)
   {
       printf("set%s databits fail\n", data);
       return NULL;
   }
   stopbits = ONESTOPBIT;
    ret = SetPortStopBits(com_port, stopbits);
   if(ret == FALSE)
   {
       printf("set%s stopbits fail\n", data);
       return NULL;
   }
   ret = SetPortParity(com_port, parity);
   if(ret == FALSE)
   {
       printf("set%s parity fail\n", data);
       return NULL;
   }

   return com_port;
}

int Serial_SendData(PORT com_port, const char *data, int len)
{
    DWORD  dNoOfBytesWritten;
    BOOL Status = WriteFile(com_port,
				data,
				len,
				&dNoOfBytesWritten,
				0);

	if (Status == FALSE)
		return -1;
	else
		printf("send ok\r\n");

    return 0;
}

int Serial_ReciveData(PORT com_port, char * data, int len)
{
	DWORD dwEventMask;
	DWORD NoBytesRead;
	BOOL Status;

	//Status = WaitCommEvent(com_port, &dwEventMask,0);
	//if(over.hEvent)
	//{printf("over->hEvent=%d   ",over.hEvent);}
	//if (Status == FALSE)
    //{
	//	return -1;
	//}
	Status = ReadFile(com_port, data, len, &NoBytesRead,0);
	data[NoBytesRead] = 0;
	//printf("over->hEvent=%d   ",over.hEvent);

	if (Status == FALSE)
		return -1;
	//else
		//printf("RD=%d ",NoBytesRead);

	return NoBytesRead;
}


