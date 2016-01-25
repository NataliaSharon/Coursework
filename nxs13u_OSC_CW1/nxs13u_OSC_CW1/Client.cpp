#include "DoNotChangeThese.h"
#include <windows.h>
#include <stdio.h>

#define THREADCOUNT 5

volatile int resource1 = 0;
volatile int resource2 = 0;
volatile int resource3 = 0;
volatile int resource4 = 0;
volatile int resource5 = 0;
volatile int resource6 = 0;

//global varialbes for critical sections and mutexes 
CRITICAL_SECTION criticalSection1;
CRITICAL_SECTION criticalSection2;
CRITICAL_SECTION criticalSection3;
CRITICAL_SECTION criticalSection4;
CRITICAL_SECTION criticalSection5;
CRITICAL_SECTION criticalSection6;
HANDLE mutexResource3;
HANDLE mutexResource4;
HANDLE mutexResource5;
HANDLE mutexResource6;

// IMPORTANT: You may ADD to the following functions but you MUST NOT delete anything

void TestCase1()
{
	//This function will help us test your code when we mark it
	StartingFunction(1); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection1);

	//using resource
	resource1++;
	UseResource(1);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection1);

	// This function will help us test your code when we mark it
	EndingFunction(1); // Do not remove - for testing purposes
}

void TestCase2()
{
	StartingFunction(2); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection2);

	//using resource
	resource2++;
	UseResource(2);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection2);

	EndingFunction(2); // Do not remove - for testing purposes
}

void TestCase3()
{
	StartingFunction(3); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection3);

	//using resource
	resource3++;
	UseResource(3);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection3);

	EndingFunction(3); // Do not remove - for testing purposes
}

void TestCase4()
{
	StartingFunction(4); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection4);

	//using resource
	resource4++;
	UseResource(4);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection4);

	EndingFunction(4); // Do not remove - for testing purposes
}

void TestCase5()
{
	StartingFunction(5); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection5);

	//using resource
	resource5++;
	UseResource(5);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection5);

	EndingFunction(5); // Do not remove - for testing purposes
}

void TestCase6()
{
	 StartingFunction(6); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection1);
	EnterCriticalSection(&criticalSection2);

	//using resources
	resource1++;
	resource2++;
	UseTwoResources(1, 2);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection2);
	LeaveCriticalSection(&criticalSection1);

	EndingFunction(6); // Do not remove - for testing purposes 
}

void TestCase7()
{
	 StartingFunction(7); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection2);
	EnterCriticalSection(&criticalSection3);

	//using resources
	resource2++;
	resource3++;
	UseTwoResources(2, 3);	// Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection3);
	LeaveCriticalSection(&criticalSection2);

	EndingFunction(7); // Do not remove - for testing purposes 
}

void TestCase8()
{
	StartingFunction(8); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection3);

	//using resources
	resource3++;
	int iTemp = StartToUseResource(3); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection5);
	EnterCriticalSection(&criticalSection6);

	//using resources
	resource5++;
	resource6++;
	UseTwoResources(5, 6);  // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection6);
	LeaveCriticalSection(&criticalSection5);

	FinishUsingResource(3, iTemp); // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection3);

	EndingFunction(8); // Do not remove - for testing purposes 
}

void TestCase9()
{
	StartingFunction(9); // Do not remove - for testing purposes

	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection4);

	//using resources
	resource4++;
	int iTemp = StartToUseResource(4); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp); // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection4);

	EndingFunction(9); // Do not remove - for testing purposes 
}

void TestCase10()
{
	StartingFunction(10); // Do not remove - for testing purposes
	
	// Request ownership of the critical section.
	EnterCriticalSection(&criticalSection1);

	//using resources
	resource1++;
	int iTemp = StartToUseResource(1); // Do not remove - for testing purposes

	TestCase7(); // Do not remove - for testing purposes
	FinishUsingResource(1, iTemp); // Do not remove - for testing purposes

	// Release ownership of the critical section.
	LeaveCriticalSection(&criticalSection1);

	EndingFunction(10); // Do not remove - for testing purposes 
}

void TestCase11()
{ 
	 StartingFunction(11); // Do not remove - for testing purposes

	 DWORD count = 0, wait3, wait4, wait5, wait6;

	 // Request ownership of mutex.

	 while (count < 1)
	 {
		 wait3 = WaitForSingleObject(mutexResource3, INFINITE);
		 wait4 = WaitForSingleObject(mutexResource4, INFINITE);
		 wait5 = WaitForSingleObject(mutexResource5, INFINITE);
		 wait6 = WaitForSingleObject(mutexResource6, INFINITE);

		 switch (wait3, wait4, wait5, wait6)
		 {
			 // The thread got ownership of the mutex
		 case WAIT_OBJECT_0:
		 {
				 //using resources
				 resource3++;
				 int iTemp3 = StartToUseResource(3); // Do not remove - for testing purposes

				 //using resources
				 resource4++;
				 int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes

				 //using resources
				 resource5++;
				 resource6++;
				 UseTwoResources(5, 6);  // Do not remove - for testing purposes

				 FinishUsingResource(3, iTemp3); // Do not remove - for testing purposes

				 FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes

				 count++;
	
				 // Release ownership of mutex objects
				 ReleaseMutex(mutexResource3);
				 ReleaseMutex(mutexResource4);
				 ReleaseMutex(mutexResource5);
				 ReleaseMutex(mutexResource6);
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

	DWORD count = 0, wait5;

	// Request ownership of mutex.

	while (count < 1)
	{
		wait5 = WaitForSingleObject(mutexResource5, INFINITE);

		switch (wait5)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{
			//using resources
			resource5++;
			int iTemp = StartToUseResource(5); // Do not remove - for testing purposes
			TestCase3(); // Do not remove - for testing purposes
			FinishUsingResource(5, iTemp); // Do not remove - for testing purposes

			count++;

			// Release ownership of mutex objects
			ReleaseMutex(mutexResource5);
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
	DWORD count = 0, wait4, wait5, wait6;

	// Request ownership of mutex.

	while (count < 1)
	{
		wait4 = WaitForSingleObject(mutexResource4, INFINITE);
		wait5 = WaitForSingleObject(mutexResource5, INFINITE);
		wait6 = WaitForSingleObject(mutexResource6, INFINITE);

		switch (wait4, wait5, wait6)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{

			StartingFunction(14); // Do not remove - for testing purposes

			//Using resources
			resource4++;
			int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes

			//Using resources
			resource5++;
			int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes

			//Using resources
			resource6++;
			int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes

			FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
			FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
			FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes

			count++;

			// Release ownership of mutex objects
			ReleaseMutex(mutexResource4);
			ReleaseMutex(mutexResource5);
			ReleaseMutex(mutexResource6);
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
	DWORD count = 0, wait4, wait5, wait6;

	// Request ownership of mutex.

	while (count < 1)
	{
		wait4 = WaitForSingleObject(mutexResource4, INFINITE);
		wait5 = WaitForSingleObject(mutexResource5, INFINITE);
		wait6 = WaitForSingleObject(mutexResource6, INFINITE);

		switch (wait4, wait5, wait6)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{

			StartingFunction(15); // Do not remove - for testing purposes

			//Using resources
			resource4++;
			int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes

			//Using resources
			resource5++;
			int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes

			//Using resources
			resource6++;
			int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes

			TestCase1(); // Do not remove - for testing purposes
			TestCase7(); // Do not remove - for testing purposes
			TestCase6(); // Do not remove - for testing purposes

			FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
			FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
			FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes


			count++;

			// Release ownership of mutex objects
			ReleaseMutex(mutexResource4);
			ReleaseMutex(mutexResource5);
			ReleaseMutex(mutexResource6);
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

	// Name matches class name in Server
	HWND handleResourceWindow = FindWindow("Resources", NULL);
	HWND handleThreadWindow = FindWindow("Threads", NULL);

	//Post message is asynchronous - returns without waiting for the thread to process the message.
	//Send mesage is synchronous - does not return until the window procedure has processed the message.

	PostMessage(handleResourceWindow, WM_USER + 1, resource1, 0); // resource 1
	PostMessage(handleResourceWindow, WM_USER + 1, resource2, 1); // resource 2
	PostMessage(handleResourceWindow, WM_USER + 1, resource3, 2); // resource 3
	PostMessage(handleResourceWindow, WM_USER + 1, resource4, 3); // resource 4
	PostMessage(handleResourceWindow, WM_USER + 1, resource5, 4); // resource 5
	PostMessage(handleResourceWindow, WM_USER + 1, resource6, 5); //resource 6

	PostMessage(handleThreadWindow, WM_USER + 1, iProcessOrThreadID, 0); //threadID

	EndingFunction(-3); // Do not remove - for testing purposes
}


// Thread 1 should run this
DWORD WINAPI Procedure1(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Thread 1 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase1(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase6(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase11(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(1); // Do not remove - for testing purposes
		printf("Thread 1 data sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 2 should run this
DWORD WINAPI Procedure2(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Thread 2 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase2(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase7(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase12(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(2); // Do not remove - for testing purposes
		printf("Thread 2 Data Sent\n");
	}
	return 1;
}

// Thread 3 should run this
DWORD WINAPI Procedure3(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Thread 3 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase3(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase8(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase13(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(3); // Do not remove - for testing purposes
		printf("Thread 3 Data Sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 4 should run this
DWORD WINAPI Procedure4(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Thread 4 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase4(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase9(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase14(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(4); // Do not remove - for testing purposes
		printf("Thread 4 Data Sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 5 should run this
DWORD WINAPI Procedure5(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes
	printf("Thread 5 runnning...\n");
	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase5(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase10(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase15(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(5); // Do not remove - for testing purposes
		printf("Thread 5 Data Sent\n");
	} // Do not remove - for testing purposes
	return 1;
}

int main()
{

	// Initialize the critical section one time only.
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection1,1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection2, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection3, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection4, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection5, 1024))
		return 1;
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection6, 1024))
		return 1;

	//create mutexes
	mutexResource3 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource3 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	mutexResource4 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource4 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	mutexResource5 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource5 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	mutexResource6 = CreateMutex(NULL, FALSE, NULL);

	if (mutexResource6 == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}
	

	HANDLE threads[THREADCOUNT];

	// Create worker threads and handle the errors
	threads[0] = CreateThread(NULL, 0, Procedure1, NULL, 0, NULL);
	if (threads[0] == NULL) 
	{
		printf("CreateThread error: %d\n", GetLastError());
		return 1;
	}
	threads[1] = CreateThread(NULL, 0, Procedure2, NULL, 0, NULL);
	if (threads[1] == NULL)
	{
		printf("CreateThread error: %d\n", GetLastError());
		return 1;
	} 
	threads[2] = CreateThread(NULL, 0, Procedure3, NULL, 0, NULL);
	if (threads[2] == NULL)
	{
		printf("CreateThread error: %d\n", GetLastError());
		return 1;
	}
	threads[3] = CreateThread(NULL, 0, Procedure4, NULL, 0, NULL);
	if (threads[3] == NULL)
	{
		printf("CreateThread error: %d\n", GetLastError());
		return 1;
	}
	threads[4] = CreateThread(NULL, 0, Procedure5, NULL, 0, NULL);
	if (threads[4] == NULL)
	{
		printf("CreateThread error: %d\n", GetLastError());
		return 1;
	} 

	// Wait for all threads to terminate
	WaitForMultipleObjects(THREADCOUNT, threads, TRUE, INFINITE);
	
	printf("resource 1: %d\n", resource1);
	printf("resource 2: %d\n", resource2);
	printf("resource 3: %d\n", resource3);
	printf("resource 4: %d\n", resource4);
	printf("resource 5: %d\n", resource5);
	printf("resource 6: %d\n", resource6);
	

	// Close thread 
	for (int i = 0; i < THREADCOUNT; i++)
		CloseHandle(threads[i]); 


	// Release resources used by the critical section object.
	DeleteCriticalSection(&criticalSection1);
	DeleteCriticalSection(&criticalSection2);
	DeleteCriticalSection(&criticalSection3);
	DeleteCriticalSection(&criticalSection4);
	DeleteCriticalSection(&criticalSection5);
	DeleteCriticalSection(&criticalSection6);

	//close mutex handles
	CloseHandle(mutexResource3);
	CloseHandle(mutexResource4);
	CloseHandle(mutexResource5);
	CloseHandle(mutexResource6);

	printf("Finished: press RETURN");
	while (getchar() != '\n')
		;

	return 0;

}