// Turn off warnings for using sprintf - which is unsafe, as it states, but portable
#undef UNICODE

// Turn off warnings for using sprintf - which is unsafe, as it states, but portable
#define _CRT_SECURE_NO_WARNINGS 1

// Only keep the main windows functions from windows.h:
#define WIN32_LEAN_AND_MEAN
// Use 4 byte IP addresses - old mode
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

// You MUST include this header file at the top of your main program file and MUST NOT modify the contents of the header file.
// We will use our own version of this header file for the marking.
#include "DoNotChangeThese.h"
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Pick a port
#define DEFAULT_PORT 27015

// And choose a size for the buffer for data - make it big enough for any input
#define DEFAULT_BUFLEN 512

struct DataForThread
{
	SOCKET ClientSocket;
	int iConnectionNumber;
};

struct DataClientToServer
{
	int processID;
	int resource7msg;
	int resource8msg;
	int resource9msg;
	int resource10msg;
	int resource11msg;
	int resource12msg;
};
union WrapperDataClientToServer
{
	DataClientToServer a;
	char b[sizeof(DataClientToServer)];
};

struct DataServerToClient
{
	int processID;
	int resource7msg;
	int resource8msg;
	int resource9msg;
	int resource10msg;
	int resource11msg;
	int resource12msg;
};
union WrapperDataServerToClient
{
	DataServerToClient a;
	char b[sizeof(DataServerToClient)];
};

#define PROCCOUNT 5

// Data structure to treat the shared memory
struct MyDataStructure
{
	int iNumberProcesses;
	int iCount;
	char c;
	char str[128];

	volatile int resource7 = 0;
	volatile int resource8 = 0;
	volatile int resource9 = 0;
	volatile int resource10 = 0;
	volatile int resource11 = 0;
	volatile int resource12 = 0;
};
HANDLE hMapFile = CreateFileMapping(
	INVALID_HANDLE_VALUE,    // use paging file
	NULL,                    // default security
	PAGE_READWRITE,          // read/write access
	0, sizeof(MyDataStructure), // max size high,low DWORDs
	"Local\\MyFileMappingObject"); // name of mapping object

// Assuming we mapped the memory correctly,
// treat the memory as if it had this structure:
volatile MyDataStructure * pMyData =
(MyDataStructure *)MapViewOfFile(
hMapFile,   // handle to map object
FILE_MAP_ALL_ACCESS, // read/write permission
0,
0,
sizeof(MyDataStructure));


//global varialbes for critical sections and mutexes 
CRITICAL_SECTION criticalSection7;
CRITICAL_SECTION criticalSection8;
CRITICAL_SECTION criticalSection9;
CRITICAL_SECTION criticalSection10;
CRITICAL_SECTION criticalSection11;
CRITICAL_SECTION criticalSection12;
HANDLE mutexResource9;
HANDLE mutexResource10;
HANDLE mutexResource11;
HANDLE mutexResource12;


// IMPORTANT: You may ADD to the following functions but you MUST NOT delete anything

void TestCase1()
{
	//This function will help us test your code when we mark it
	StartingFunction(1); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection7);

	//using resource
	pMyData->resource7++;
	UseResource(7);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection7);

	// This function will help us test your code when we mark it
	EndingFunction(1); // Do not remove - for testing purposes
}

void TestCase2()
{
	StartingFunction(2); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection8);

	//using resource
	pMyData->resource8++;
	UseResource(8);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection8);

	EndingFunction(2); // Do not remove - for testing purposes
}

void TestCase3()
{
	StartingFunction(3); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection9);

	//using resource
	pMyData->resource9++;
	UseResource(9);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection9);

	EndingFunction(3); // Do not remove - for testing purposes
}

void TestCase4()
{
	StartingFunction(4); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection10);

	//using resource
	pMyData->resource10++;
	UseResource(10);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection10);

	EndingFunction(4); // Do not remove - for testing purposes
}

void TestCase5()
{
	StartingFunction(5); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection11);

	//using resource
	pMyData->resource11++;
	UseResource(11);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection11);

	EndingFunction(5); // Do not remove - for testing purposes
}

void TestCase6()
{
	StartingFunction(6); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection7);
	EnterCriticalSection(&criticalSection8);

	//using resources
	pMyData->resource7++;
	pMyData->resource8++;
	UseTwoResources(7, 8);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection7);
	LeaveCriticalSection(&criticalSection8);

	EndingFunction(6); // Do not remove - for testing purposes 
}

void TestCase7()
{
	StartingFunction(7); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection8);
	EnterCriticalSection(&criticalSection9);

	//using resources
	pMyData->resource8++;
	pMyData->resource9++;
	UseTwoResources(8, 9);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection9);
	LeaveCriticalSection(&criticalSection8);

	EndingFunction(7); // Do not remove - for testing purposes 
}

void TestCase8()
{
	StartingFunction(8); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection9);

	//using resources
	pMyData->resource9++;
	int iTemp = StartToUseResource(9); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection11);
	EnterCriticalSection(&criticalSection12);

	//using resources
	pMyData->resource11++;
	pMyData->resource12++;
	UseTwoResources(11, 12);  // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection12);
	LeaveCriticalSection(&criticalSection11);

	FinishUsingResource(9, iTemp); // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection9);

	EndingFunction(8); // Do not remove - for testing purposes 
}

void TestCase9()
{
	StartingFunction(9); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection10);

	//using resources
	pMyData->resource10++;
	int iTemp = StartToUseResource(10); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes
	FinishUsingResource(10, iTemp); // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection10);

	EndingFunction(9); // Do not remove - for testing purposes 
}

void TestCase10()
{
	StartingFunction(10); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection7);

	//using resources
	pMyData->resource7++;
	int iTemp = StartToUseResource(7); // Do not remove - for testing purposes

	TestCase7(); // Do not remove - for testing purposes
	FinishUsingResource(7, iTemp); // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection7);

	EndingFunction(10); // Do not remove - for testing purposes 
}

void TestCase11()
{
	StartingFunction(11); // Do not remove - for testing purposes

	DWORD count = 0, wait9, wait10, wait11, wait12;

	// Request ownership of mutex.

	while (count < 1)
	{
		wait9 = WaitForSingleObject(mutexResource9, INFINITE);
		wait10 = WaitForSingleObject(mutexResource10, INFINITE);
		wait11 = WaitForSingleObject(mutexResource11, INFINITE);
		wait12 = WaitForSingleObject(mutexResource12, INFINITE);

		switch (wait9, wait10, wait11, wait12)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{
			//using resources
			pMyData->resource9++;
			int iTemp3 = StartToUseResource(9); // Do not remove - for testing purposes

			//using resources
			pMyData->resource10++;
			int iTemp4 = StartToUseResource(10); // Do not remove - for testing purposes

			//using resources
			pMyData->resource11++;
			pMyData->resource12++;
			UseTwoResources(5, 6);  // Do not remove - for testing purposes

			FinishUsingResource(9, iTemp3); // Do not remove - for testing purposes

			FinishUsingResource(10, iTemp4); // Do not remove - for testing purposes

			count++;

			// Release ownership of mutex objects
			ReleaseMutex(mutexResource9);
			ReleaseMutex(mutexResource10);
			ReleaseMutex(mutexResource11);
			ReleaseMutex(mutexResource12);
		}
		break;

		case WAIT_ABANDONED:
			printf("Wait abandoned\n");
			break;
		}
	}

	EndingFunction(11); // Do not remove - for testing purposes 
}

void TestCase12()
{
	StartingFunction(12); // Do not remove - for testing purposes

	DWORD count = 0, wait11;

	// Request ownership of mutex.

	while (count < 1)
	{
		wait11 = WaitForSingleObject(mutexResource11, INFINITE);

		switch (wait11)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{
			//using resources
			pMyData->resource11++;
			int iTemp = StartToUseResource(11); // Do not remove - for testing purposes
			TestCase3(); // Do not remove - for testing purposes
			FinishUsingResource(11, iTemp); // Do not remove - for testing purposes

			count++;

			// Release ownership of mutex objects
			ReleaseMutex(mutexResource11);
		}
		break;

		case WAIT_ABANDONED:
			printf("Wait abandoned\n");
			break;
		}
	}

	EndingFunction(12); // Do not remove - for testing purposes */
}

void TestCase13()
{
	StartingFunction(13); // Do not remove - for testing purposes

	TestCase1(); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	TestCase8(); // Do not remove - for testing purposes

	EndingFunction(13); // Do not remove - for testing purposes  
}

void TestCase14()
{
	DWORD count = 0, wait10, wait11, wait12;

	// Request ownership of mutex.

	while (count < 1)
	{
		wait10 = WaitForSingleObject(mutexResource10, INFINITE);
		wait11 = WaitForSingleObject(mutexResource11, INFINITE);
		wait12 = WaitForSingleObject(mutexResource12, INFINITE);

		switch (wait10, wait11, wait12)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{

			StartingFunction(14); // Do not remove - for testing purposes

			//Using resources
			pMyData->resource10++;
			int iTemp4 = StartToUseResource(10); // Do not remove - for testing purposes

			//Using resources
			pMyData->resource11++;
			int iTemp5 = StartToUseResource(11); // Do not remove - for testing purposes

			//Using resources
			pMyData->resource12++;
			int iTemp6 = StartToUseResource(12); // Do not remove - for testing purposes

			FinishUsingResource(10, iTemp4); // Do not remove - for testing purposes
			FinishUsingResource(11, iTemp5); // Do not remove - for testing purposes
			FinishUsingResource(12, iTemp6); // Do not remove - for testing purposes

			count++;

			// Release ownership of mutex objects
			ReleaseMutex(mutexResource10);
			ReleaseMutex(mutexResource11);
			ReleaseMutex(mutexResource12);
		}
		break;

		case WAIT_ABANDONED:
			printf("Wait abandoned\n");
			break;
		}
	}

	EndingFunction(14); // Do not remove - for testing purposes */
}

void TestCase15()
{
	DWORD count = 0, wait10, wait11, wait12;

	// Request ownership of mutex.

	while (count < 1)
	{
		wait10 = WaitForSingleObject(mutexResource10, INFINITE);
		wait11 = WaitForSingleObject(mutexResource11, INFINITE);
		wait12 = WaitForSingleObject(mutexResource12, INFINITE);

		switch (wait10, wait11, wait12)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{

			StartingFunction(15); // Do not remove - for testing purposes

			//Using resources
			pMyData->resource10++;
			int iTemp4 = StartToUseResource(10); // Do not remove - for testing purposes

			//Using resources
			pMyData->resource11++;
			int iTemp5 = StartToUseResource(11); // Do not remove - for testing purposes

			//Using resources
			pMyData->resource12++;
			int iTemp6 = StartToUseResource(12); // Do not remove - for testing purposes

			TestCase1(); // Do not remove - for testing purposes
			TestCase7(); // Do not remove - for testing purposes
			TestCase6(); // Do not remove - for testing purposes

			FinishUsingResource(10, iTemp4); // Do not remove - for testing purposes
			FinishUsingResource(11, iTemp5); // Do not remove - for testing purposes
			FinishUsingResource(12, iTemp6); // Do not remove - for testing purposes


			count++;

			// Release ownership of mutex objects
			ReleaseMutex(mutexResource10);
			ReleaseMutex(mutexResource11);
			ReleaseMutex(mutexResource12);
		}
		break;

		case WAIT_ABANDONED:
			printf("Wait abandoned\n");
			break;
		}
	}


	EndingFunction(15); // Do not remove - for testing purposes 
}

void InitialCode(int iDelay) //This simulates the thread doing some initial work before reaching any critical section.
{
	StartingFunction(-1); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay);
	EndingFunction(-1); // Do not remove - for testing purposes
}

void RemainderCode(int iDelay) //This simulates the thread doing some work after it has completed a critical section.
{
	StartingFunction(-2); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay); // Do not remove - for testing purposes
	EndingFunction(-2); // Do not remove - for testing purposes
}

void SendDataToServer(int iProcessOrThreadID)
{
	StartingFunction(-3); // Do not remove - for testing purposes

	SOCKET ConnectSocket = INVALID_SOCKET;

	char *sendbuf = "Initial test message from client";
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Local machine
	serveraddress.sin_port = htons(DEFAULT_PORT);

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("ConnectSocket socket failed with error: %ld\n", WSAGetLastError());
		return;
	}

	// Connect to server.
	iResult = connect(ConnectSocket, (sockaddr*)&serveraddress, sizeof(serveraddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("ConnectSocket connect failed with error: %ld\n", WSAGetLastError());
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// New for handling a struct-based system.
	int iReceiveIndex = 0; // Index into struct that we are getting
	WrapperDataServerToClient dataReceived = { 0 }; // Used to hold the received message. Initialise the structure to 0s

	// Build some messages to send
	WrapperDataClientToServer message1;
	message1.a.processID = iProcessOrThreadID;
	message1.a.resource7msg = pMyData->resource7;
	message1.a.resource8msg = pMyData->resource8;
	message1.a.resource9msg = pMyData->resource9;
	message1.a.resource10msg = pMyData->resource10;
	message1.a.resource11msg = pMyData->resource11;
	message1.a.resource12msg = pMyData->resource12;

	iResult = send(ConnectSocket, message1.b, (int)sizeof(message1), 0);
	iResult = shutdown(ConnectSocket, SD_SEND);

	if (iResult == SOCKET_ERROR)
	{
		printf("ConnectSocket shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		return;
	}

	// cleanup
	closesocket(ConnectSocket); 

	EndingFunction(-3); // Do not remove - for testing purposes
}


// Thread 1 should run this
DWORD WINAPI Procedure1(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Process 6 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase1(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase6(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase11(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(6); // Do not remove - for testing purposes
		printf("Process 6 data sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 2 should run this
DWORD WINAPI Procedure2(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Process 7 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase2(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase7(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase12(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(7); // Do not remove - for testing purposes
		printf("Process 7 Data Sent\n");
	}
	return 1;
}

// Thread 3 should run this
DWORD WINAPI Procedure3(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Process 8 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase3(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase8(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase13(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(8); // Do not remove - for testing purposes
		printf("Process 8 Data Sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 4 should run this
DWORD WINAPI Procedure4(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Process 9 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase4(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase9(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase14(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(9); // Do not remove - for testing purposes
		printf("Process 9 Data Sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 5 should run this
DWORD WINAPI Procedure5(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Process 10 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase5(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase10(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase15(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(10); // Do not remove - for testing purposes
		printf("Process 10 Data Sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

int main(int argc, char* argv[])
{

	// Initialize the critical section one time only.
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection7, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection8, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection9, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection10, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection11, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection12, 1024))
		return 1;

	//create mutexes
	mutexResource9 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource9 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	mutexResource10 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource10 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	mutexResource11 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource11 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	mutexResource12 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource12 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}


	/////////////////////////////////////////////////////////////////////////////////////////create processes 
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		printf("Press ENTER to exit\n");
		while (getchar() != '\n')
			;
	}
	else
	{

		if (argc > 1)
		{
			printf("DEBUG: Argc = %d, argv[1] = %s\n", argc, argv[1]);
			printf("\n\n");

			printf("Client %d starting ('%s')...\n", atoi(argv[1]), argv[1]);

			switch (atoi(argv[1]))
			{
			case 1:
				Procedure1(NULL);
				break;
			case 2:
				Procedure2(NULL);
				break;
			case 3:
				Procedure3(NULL);
				break;
			case 4:
				Procedure4(NULL);
				break;
			case 5:
				Procedure5(NULL);
				break;
			}

			printf("Client process %d ending\n", atoi(argv[1]));
		}
		else
		{
			printf("Creating Processes");


			// I'll grab the next number AND increment the number
			int iMyProcess = pMyData->iNumberProcesses++;

			// Work out the filename of the exe for the running process
			char szMyFileName[1024];
			GetModuleFileName(NULL, szMyFileName, 1024);


			for (int i = 0; i < PROCCOUNT; i++)
			{

				if (iMyProcess < PROCCOUNT)
				{ // Start up another copy of this program
					STARTUPINFO info = { sizeof(info) }; // Input
					PROCESS_INFORMATION processInfo; // Output
					char szCommandLine[1024 + 4];
					sprintf_s(szCommandLine, "\"%s\" %d", szMyFileName, i + 1/*Client number*/);
					if (CreateProcess(szMyFileName, szCommandLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &info, &processInfo))
					{ // Created - close handles to it.
						CloseHandle(processInfo.hProcess);
						CloseHandle(processInfo.hThread);
					}
				}
			}

			UnmapViewOfFile((LPCVOID)pMyData);

			CloseHandle(hMapFile);
		}
	}
	SendDataToServer(0); //fake message to indicate completion of messages

	printf("resource 1: %d\n", pMyData->resource7);
	printf("resource 2: %d\n", pMyData->resource8);
	printf("resource 3: %d\n", pMyData->resource9);
	printf("resource 4: %d\n", pMyData->resource10);
	printf("resource 5: %d\n", pMyData->resource11);
	printf("resource 6: %d\n", pMyData->resource12);

	// Release resources used by the critical section object.
	DeleteCriticalSection(&criticalSection7);
	DeleteCriticalSection(&criticalSection8);
	DeleteCriticalSection(&criticalSection9);
	DeleteCriticalSection(&criticalSection10);
	DeleteCriticalSection(&criticalSection11);
	DeleteCriticalSection(&criticalSection12);

	//close mutex handles
	CloseHandle(mutexResource9);
	CloseHandle(mutexResource10);
	CloseHandle(mutexResource11);
	CloseHandle(mutexResource12);

	printf("Finished: press RETURN");
	while (getchar() != '\n')
		;

	return 0;

}