// Flex_Console.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>

#include <windows.h>
#include <process.h>
#include <queue>



#include "VCECLB.h"


struct tagElemQueue
{
	SYSTEMTIME time;
	BYTE* Buffer;
	DWORD size;
}ElemQueue,FrontElemQueue;

std::queue <tagElemQueue> QUE;


_TCHAR FileName[MAX_PATH];
_TCHAR SaveType[MAX_PATH];
_TCHAR OutFolderName[MAX_PATH];
_TCHAR TimeStamp[MAX_PATH];
char Port;

HANDLE DeviceID;
VCECLB_Configuration config;

HANDLE hThread;
HANDLE hEvent[2];
unsigned threadID;

unsigned Counter;

bool inOpt(_TCHAR* str)
{
	if(wcscmp(str,_T("-c"))==0)return(true);
	if(wcscmp(str,_T("-p"))==0)return(true);
	if(wcscmp(str,_T("-t"))==0)return(true);
	if(wcscmp(str,_T("-f"))==0)return(true);
	return(false);
}

static void WINAPI GrabbingThread(LPVOID lpUserData,VCECLB_FrameInfoEx* pFrameInfo)
{
	if(pFrameInfo->dma_status != VCECLB_DMA_STATUS_OK)
		return;

	ElemQueue.Buffer =(BYTE*)malloc(pFrameInfo->bufferSize);
	ElemQueue.size = pFrameInfo->bufferSize;
	memcpy(ElemQueue.Buffer,pFrameInfo->lpRawBuffer,pFrameInfo->bufferSize);
	GetLocalTime(&ElemQueue.time);

	QUE.push(ElemQueue);
	
	////////////////////////////
	// Set Event ImageReady
	////////////////////////////
	SetEvent(hEvent[1]);
}

unsigned __stdcall  SaveThread(void* pArguments)
{
	
	SYSTEMTIME lastTimeStamp;
	DWORD nTSSubNum = 0;
	int Counter=0;

	ZeroMemory(&lastTimeStamp,sizeof(lastTimeStamp));
	
	///////////////////////////////////////////////////////////
	// Wait Quit Event (hEvent[0]) for quit or
	// ImageReady Event (hEvent[1]) for save images from queue
	///////////////////////////////////////////////////////////
	while(WaitForMultipleObjects(2,hEvent,FALSE,INFINITE)!=(WAIT_OBJECT_0 + 0))
	{
		ResetEvent(hEvent[1]);
		while(QUE.size() > 0)
		{
			TCHAR fileName[MAX_PATH];
			
			///////////////////////////////////////////////////////////////////
			// Get a reference to the first element at the front of the queue
			///////////////////////////////////////////////////////////////////
			FrontElemQueue = QUE.front();
			
			///////////////////////////////////////////////////
			// Remove an element from the front of the queue
			///////////////////////////////////////////////////
			QUE.pop();

			//----- Set output format name ---------------------------------------------			

			if(wcscmp(TimeStamp,_T("TimeStamp"))==0)
			{
				if(lastTimeStamp.wYear == FrontElemQueue.time.wYear &&
					lastTimeStamp.wMonth == FrontElemQueue.time.wMonth &&
					lastTimeStamp.wDay == FrontElemQueue.time.wDay &&
					lastTimeStamp.wHour == FrontElemQueue.time.wHour &&
					lastTimeStamp.wMinute == FrontElemQueue.time.wMinute &&
					lastTimeStamp.wSecond == FrontElemQueue.time.wSecond &&
					lastTimeStamp.wMilliseconds == FrontElemQueue.time.wMilliseconds)
					nTSSubNum++;
				else
					nTSSubNum = 0;
				_stprintf_s(fileName,_T("%s\\%04d%02d%02d%02d%02d%02d%03d"),OutFolderName,FrontElemQueue.time.wYear,
					FrontElemQueue.time.wMonth,
					FrontElemQueue.time.wDay,
					FrontElemQueue.time.wHour,
					FrontElemQueue.time.wMinute,
					FrontElemQueue.time.wSecond,
					FrontElemQueue.time.wMilliseconds);
				_stprintf_s(fileName,_T("%s_%d"),fileName,nTSSubNum);
				lastTimeStamp = FrontElemQueue.time;
			}
			if(wcscmp(TimeStamp,_T("Numerate"))==0)
			{
				Counter++;
				_stprintf_s(fileName,_T("%s\\%d"),OutFolderName,Counter);
			}
			
			//---------------------------------------------------------------
			//---------- Save images ----------------------------------------

			if(wcscmp(SaveType,_T("BMP"))==0)
			{
				_stprintf_s(fileName,_T("%s.bmp"),fileName);

				///////////////////////////////////////////
				// Save raw data to bitmap file
				///////////////////////////////////////////
				VCECLB_SaveRawToBMPFile(&config.pixelInfo, FrontElemQueue.Buffer, fileName);
			}
			if(wcscmp(SaveType,_T("JPEG"))==0)
			{
				_stprintf_s(fileName,_T("%s.jpg"),fileName);

				//////////////////////////////////////////
				// Save raw data to JPEG file
				//////////////////////////////////////////
				VCECLB_SaveRawToJPGFile(&config.pixelInfo, FrontElemQueue.Buffer, fileName, 80);
			}
			if(wcscmp(SaveType,_T("TIFF"))==0)
			{
				_stprintf_s(fileName,_T("%s.tiff"),fileName);

				//////////////////////////////////////////////
				// Save raw data to TIFF file
				//////////////////////////////////////////////
				VCECLB_SaveRawToTIFFFile(&config.pixelInfo, FrontElemQueue.Buffer, fileName, VCECLB_EX_FMT_16BIT);
			}
			if(wcscmp(SaveType,_T("RAW"))==0)
			{
				_stprintf_s(fileName,_T("%s.raw"),fileName);
				
				//////////////////////////////////////////////
				// Save raw data to RAW file
				//////////////////////////////////////////////
				FILE* file;
				_wfopen_s(&file,fileName,L"wb"); 
				fwrite(FrontElemQueue.Buffer,FrontElemQueue.size,1,file);
				fclose(file);
			}
			//----------------------------------------------------------------

			free(FrontElemQueue.Buffer);
			
			printf("%S\n",fileName);
		}
		
	}
	
	///////////////////////////////////////////////
	// Terminate a thread 
	///////////////////////////////////////////////
    _endthreadex( 0 );

	return(0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i=1;
	int opt_c=0,opt_p=0,opt_t=0,opt_f=0;

	/////////////////////////////////////////////
	// Initialization default value
	/////////////////////////////////////////////
	
	wcscpy_s(SaveType,_T(""));
	wcscpy_s(SaveType,_T("BMP"));
	wcscpy_s(OutFolderName,_T("Flex_Console OutputFolder"));
	wcscpy_s(TimeStamp,_T("TimeStamp"));
	Port = 0;
	
//----------------------------------------------------------------
	while(i<argc)
	{
		if(wcscmp(argv[i],_T("-c"))==0)
		{
			i++;
			opt_c++;
			if(opt_c>1)
			{
				printf("Error: two keys -c");
				return(-1);
			}
			if(i >= argc)
			{
				printf("Error: Not Argument");
				return(-1);
			}
			if(inOpt(argv[i]))
			{
				printf("Error: Bad %d argument %S",i,argv[i]);
				return(-1);
			}
			else
			{	
				wcscpy_s(FileName,argv[i]);
			}
		}else
		if(wcscmp(argv[i],_T("-p"))==0)
		{
			i++;
			opt_p++;
			if(opt_p>1)
			{
				printf("Error: two keys -p");
				return(-1);
			}
			if(i >= argc)
			{
				printf("Error: Not Argument");
				return(-1);
			}
			if(inOpt(argv[i]))
			{
				printf("Error: Bad %d argument %S",i,argv[i]);
				return(-1);
			}
			else
			{
				_TCHAR* ChPort = new _TCHAR[wcslen(argv[i])];
				wcscpy_s(ChPort,wcslen(ChPort)*sizeof(_TCHAR),argv[i]);
				Port = (char)_wcstoi64(ChPort,NULL,0)-1;
				if(Port != 0 && Port !=1)
				{
					printf("Error: Bad port.Port = [1,2]");
					return(-1);
				}
			}
		}else
		if(wcscmp(argv[i],_T("-t"))==0)
		{
			i++;
			opt_t++;
			if(opt_t>1)
			{
				printf("Error: two keys -t");
				return(-1);
			}
			if(i >= argc)
			{
				printf("Error: Not Argument");
				return(-1);
			}
			if(inOpt(argv[i]))
			{
				printf("Error: Bad %d argument %S",i,argv[i]);
				return(-1);
			}
			else
			{	
				wcscpy_s(SaveType,argv[i]);
				if(wcscmp(SaveType,_T("BMP"))!=0 &&
				   wcscmp(SaveType,_T("JPEG"))!=0 &&
				   wcscmp(SaveType,_T("TIFF"))!=0 &&
				   wcscmp(SaveType,_T("RAW"))!=0)
				{
					printf("Error: Bad Save Type\n");
					return(-1);
				}
			}
		}else
		if(wcscmp(argv[i],_T("-f"))==0)
		{
			i++;
			opt_f++;
			if(opt_f>1)
			{
				printf("Error: two keys -f");
				return(-1);
			}
			if(i >= argc)
			{
				printf("Error: Not Argument");
				return(-1);
			}
			if(inOpt(argv[i]))
			{
				printf("Error: Bad %d argument %S",i,argv[i]);
				return(-1);
			}
			else
			{
				
				wcscpy_s(TimeStamp,argv[i]);
				if(wcscmp(TimeStamp,_T("TimeStamp"))!=0 &&
					wcscmp(TimeStamp,_T("Numerate"))!=0)
				{
					printf("Error: argument is not TimeStamp or Numerate");
					return(-1);
				}
			}
		}else
		if(wcscmp(argv[i],_T("-h"))==0)
		{
			printf("help\n\n");
			printf("Flex_Console.exe [-options]\n\noptions:\n");
			printf("	-h [FileName]		- Camera config file name\n");
			printf("	-p [1|2]		- Port\n");
			printf("	-t [BMP|JPEG|TIFF|RAW]  - Save type\n");
			printf("	-f [TimeStamp,Numerate]	- Save file template\n\n\n");
			return(0);

		}
		else
		{
			printf("Error: Bad argument %S",argv[i]);
			return(-1);
		}


		i++;
	}

	if(wcscmp(FileName,_T(""))==0)
	{
		printf("Error: Camera config file name is null.Input option -c [filename]\n");
		return(-1);
	}
//-----------------------------------------------------------------	

	//////////////////////////////////////////////
	// Create output directory
	//////////////////////////////////////////////
	CreateDirectory(OutFolderName,0);

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

	////////////////////////////////////////
	// Initializes FrameLink frame grabber
	////////////////////////////////////////
	DeviceID=VCECLB_Init();
	if(DeviceID == NULL)
	{
		printf("No FrameLink Express card detected!");
		return(-1);
	}
	
	//////////////////////////////////////////////////////
	// Acquires access to image acquisition on port
	//////////////////////////////////////////////////////
	if(VCECLB_GetDMAAccessEx(DeviceID, Port) != VCECLB_Err_Success)
	{
		printf("Bad Port");
	}
	
	ZeroMemory(&config,sizeof(config));

	TCHAR strManufacturer[MAX_PATH];
	ZeroMemory(strManufacturer, sizeof(strManufacturer));

	TCHAR strModel[MAX_PATH];
	ZeroMemory(strModel, sizeof(strModel));

	TCHAR strDescription[MAX_PATH];
	ZeroMemory(strDescription, sizeof(strDescription));

	TCHAR strAlias[MAX_PATH];
	ZeroMemory(strAlias, sizeof(strAlias));

	config.lpszManufacturer = strManufacturer;
	config.cchManufacturer = MAX_PATH;
	config.lpszModel = strModel;
	config.cchModel = MAX_PATH;
	config.lpszDescription = strDescription;
	config.cchDescription = MAX_PATH;
	config.lpszAlias = strAlias;
	config.cchAlias = MAX_PATH;

	///////////////////////////////////////////////////////////////////////////////////
	// Load configuration from specified FrameLink or FrameLink Express camera file
	///////////////////////////////////////////////////////////////////////////////////
	VCECLB_LoadConfig(FileName, &config);
	
	////////////////////////////////////////////////////
	// Configure frame grabber with specified settings
	////////////////////////////////////////////////////
	if (VCECLB_PrepareEx(DeviceID, Port,&config.pixelInfo.cameraData) != VCECLB_Err_Success)
	{
		// TODO:
	}
	
	//////////////////////////////////
	// Create Event Object for Quit
	//////////////////////////////////
	hEvent[0] = CreateEvent(NULL,TRUE,TRUE,_T("Quit"));

	//////////////////////////////////
	// Create ImageReady Event Object
	//////////////////////////////////
	hEvent[1] = CreateEvent(NULL,TRUE,TRUE,_T("ImageReady"));
	
	ResetEvent(hEvent[0]);
	ResetEvent(hEvent[0]);

	///////////////////////////////////
	// Create a thread for save images
	///////////////////////////////////
	hThread = (HANDLE)_beginthreadex( NULL, 0, &SaveThread, NULL, 0, &threadID );
	
	///////////////////////////////////////////////
	// Start image acquisition on specified port
	///////////////////////////////////////////////
	if(VCECLB_StartGrabEx(DeviceID, Port, 0, (VCECLB_GrabFrame_CallbackEx)GrabbingThread,NULL ) != VCECLB_Err_Success)	
	{
		printf("StartGrab filed");
	}

	////////////////////////////
	// Wait input q for quit
	////////////////////////////
	while(_getch() != 'q');

	///////////////////////////////////////////////
	// Stop image acquisition on specified port
	///////////////////////////////////////////////
	VCECLB_StopGrabEx(DeviceID, Port);
		
	/////////////////////////////////////////////////
	// Release access to image acquisition on port
	/////////////////////////////////////////////////
	VCECLB_ReleaseDMAAccessEx(DeviceID, Port);
	
	///////////////////////////////////
	// Close handle to frame grabber
	///////////////////////////////////
	VCECLB_Done(DeviceID);

	///////////////////////
	// Set Evet for quit
	///////////////////////
	SetEvent(hEvent[0]);

	WaitForSingleObject(hThread, INFINITE );
	
    /////////////////////////////////
	// Destroy the thread object
	/////////////////////////////////
    CloseHandle( hThread );

	printf("\n\n\nOutput Folder : Flex_Console OutputFolder\n\n\n");
	
	return 0;
}

