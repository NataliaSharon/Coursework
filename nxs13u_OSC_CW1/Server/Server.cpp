#undef UNICODE

// Turn off warnings for using sprintf - which is unsafe, as it states, but portable
#define _CRT_SECURE_NO_WARNINGS 1

// Only keep the main windows functions from windows.h:
#define WIN32_LEAN_AND_MEAN
// Use 4 byte IP addresses - old mode
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


//checks count for fake message
int fakeMessage = 0;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Pick a port
#define DEFAULT_PORT 27015

// And choose a size for the buffer for data - make it big enough for any input
#define DEFAULT_BUFLEN 512

//global varialbes for critical sections
CRITICAL_SECTION criticalSectionResources;

//handles for windows
HWND handleThreadWindow;
HWND handleResourceWindow;

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


#define NUM_RESOURCES 12
#define NUM_CLIENTS 10

int threadValues[NUM_CLIENTS];
int resourceValues[NUM_RESOURCES];



// The following code should be copy-pasted into the WM_PAINT section for the window which will be displaying the resource usage information:
// This code is added only to help you out, do you may freely modify it if you wish as long as you get the correct output at the end
LRESULT CALLBACK WndProcThreads(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
	{	// Added for the painting
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		{
			//place values recieved into array
			int aiValuesToShow[NUM_CLIENTS];
			for (int i = 0; i < NUM_CLIENTS; i++)
				aiValuesToShow[i] = threadValues[i];

			// Now work out how high to make each bar
			int iMax = -10000000; int iMin = 10000000;
			for (int i = 0; i < 10; i++)
			{
				if (aiValuesToShow[i] < iMin) iMin = aiValuesToShow[i];
				if (aiValuesToShow[i] > iMax) iMax = aiValuesToShow[i];
			}
			if (iMin < 0) iMin = 0;
			if (iMax < (iMin + 1)) iMax = iMin + 1;
			int iDiff = iMax - iMin;


			HBRUSH hbrush[6];
			hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
			hbrush[1] = CreateSolidBrush(RGB(255, 255, 0));
			hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
			hbrush[3] = CreateSolidBrush(RGB(0, 255, 255));
			hbrush[4] = CreateSolidBrush(RGB(0, 0, 255));
			hbrush[5] = CreateSolidBrush(RGB(255, 0, 255));
			RECT rc;
			GetClientRect(hwnd, &rc);
			RECT rect[NUM_RESOURCES];
			for (int i = 0; i < NUM_CLIENTS; i++)
				rect[i] = rc; // Copy original size
			for (int i = 1; i < NUM_CLIENTS; i++)
				rect[i - 1].right = rect[i].left = rc.right * i / NUM_CLIENTS;
			// Fix heights to be relative to total
			int iFullHeight = rc.bottom - rc.top;
			for (int i = 0; i < NUM_CLIENTS; i++)
				rect[i].top = rect[i].bottom - (iFullHeight * aiValuesToShow[i]) / iMax;
			for (int i = 0; i < NUM_CLIENTS; i++)
				FillRect(hdc, &rect[i], hbrush[i % 6]);
			for (int i = 0; i < 6; i++)
				DeleteObject(hbrush[i]); // Free the brush resources
		} // End of draw the background
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_USER + 1:
	{
		threadValues[wParam - 1]++; //update 
		InvalidateRect(hwnd, NULL, true);
		UpdateWindow(hwnd); //redraw
	}
	break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcResources(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
	{	// Added for the painting
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		{
			//place values recieved into array
			int aiValuesToShow[NUM_RESOURCES];

			for (int i = 0; i < NUM_RESOURCES; i++)
				aiValuesToShow[i] = resourceValues[i];

			// Now work out how high to make each bar
			int iMax = -10000000; int iMin = 10000000;
			for (int i = 0; i < 10; i++)
			{
				if (aiValuesToShow[i] < iMin) iMin = aiValuesToShow[i];
				if (aiValuesToShow[i] > iMax) iMax = aiValuesToShow[i];
			}
			if (iMin < 0) iMin = 0;
			if (iMax < (iMin + 1)) iMax = iMin + 1;
			int iDiff = iMax - iMin;

			HBRUSH hbrush[6];
			hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
			hbrush[1] = CreateSolidBrush(RGB(255, 255, 0));
			hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
			hbrush[3] = CreateSolidBrush(RGB(0, 255, 255));
			hbrush[4] = CreateSolidBrush(RGB(0, 0, 255));
			hbrush[5] = CreateSolidBrush(RGB(255, 0, 255));
			RECT rc;
			GetClientRect(hwnd, &rc);
			RECT rect[NUM_RESOURCES];
			for (int i = 0; i < NUM_RESOURCES; i++)
				rect[i] = rc; // Copy original size
			for (int i = 1; i < NUM_RESOURCES; i++)
				rect[i - 1].right = rect[i].left = rc.right * i / NUM_RESOURCES;
			// Fix heights to be relative to total
			int iFullHeight = rc.bottom - rc.top;
			for (int i = 0; i < NUM_RESOURCES; i++)
				rect[i].top = rect[i].bottom - (iFullHeight * aiValuesToShow[i]) / iMax;
			for (int i = 0; i < NUM_RESOURCES; i++)
				FillRect(hdc, &rect[i], hbrush[i % 6]);
			for (int i = 0; i < 6; i++)
				DeleteObject(hbrush[i]); // Free the brush resources
		} // End of draw the background
		EndPaint(hwnd, &ps);
	}
	break;

	case WM_USER + 1:
	{
		resourceValues[lParam] = wParam; //update 
		InvalidateRect(hwnd, NULL, true);
		UpdateWindow(hwnd); //redraw
	}
	break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

// Handle a single client connection until it disconnects
DWORD WINAPI HandleConnection(LPVOID lpData)
{

	// Grab the info that was passed in ...
	DataForThread* pDataPassedIn = (DataForThread*)lpData;
	SOCKET ClientSocket = pDataPassedIn->ClientSocket;
	int iConnectionNumber = pDataPassedIn->iConnectionNumber;
	// And then delete the data that was passed in
	// (We could just keep using it and delete it later but this prevents forgetting to do so)
	free(pDataPassedIn); // Matches the malloc below (search for it if not sure)
	// Now all of our data is on the stack - so will be tidied up for us

	// We have our own buffer for receiving data
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	// New for handling a struct-based system.
	int iReceiveIndex = 0; // Index into struct that we are getting
	WrapperDataClientToServer dataReceived = { 0 }; // Initialise the structure to 0

	// Receive until the peer shuts down the connection
	do
	{
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf("Connection %d: Bytes received: %d\n", iConnectionNumber, iResult);

			// This code will handle the current message
			for (int i = 0; i < iResult; i++)
			{	// Copy the bytes in
				dataReceived.b[iReceiveIndex++] = recvbuf[i];
				// As soon as a message is completed then handle it
				if (iReceiveIndex >= sizeof(DataClientToServer))
				{ // We have a full message now so do something with it:

					if (dataReceived.a.processID == 0){
						fakeMessage++;
					}
					else
					{
						//handle thread/process count
						threadValues[dataReceived.a.processID - 1]++;

						// Request ownership of the critical section.
						EnterCriticalSection(&criticalSectionResources);

						resourceValues[6] = dataReceived.a.resource7msg;
						resourceValues[7] = dataReceived.a.resource8msg;
						resourceValues[8] = dataReceived.a.resource9msg;
						resourceValues[9] = dataReceived.a.resource10msg;
						resourceValues[10] = dataReceived.a.resource11msg;
						resourceValues[11] = dataReceived.a.resource12msg; 

						// Release ownership of the critical section.
						LeaveCriticalSection(&criticalSectionResources);

						for (int i = 5; i < NUM_CLIENTS; i++)
							printf("process %d: %d\n", i, threadValues[i]);

						for (int i = 6; i < NUM_RESOURCES; i++)
							printf("resource %d: %d\n", i, resourceValues[i]); 


						iReceiveIndex = 0; // Go back to start for the next one.
						// Now any code to handle this message goes here:


						//update windows
						InvalidateRect(handleResourceWindow, NULL, true);
						UpdateWindow(handleResourceWindow); //redraw
						InvalidateRect(handleThreadWindow, NULL, true);
					}
				} // End of if condition for the whole message having been received.
			} // End of for loop, looping through the received data

		}
		else if (iResult == 0)
			printf("Connection %d: Connection closing...\n", iConnectionNumber);
		else
		{
			printf("ClientSocket recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}  
	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("ClientSocket shutdown failed with error: %d\n", WSAGetLastError());
	}

	// cleanup
	closesocket(ClientSocket);
	return 0; // success
}

DWORD WINAPI Socket(LPVOID lpData)
{
	////////////////////////////////////////////////////////////////////////SOCKETS
		int iResult;
		SOCKET ListenSocket = INVALID_SOCKET;
		SOCKET ClientSocket = INVALID_SOCKET;

		struct sockaddr_in localaddress;
		localaddress.sin_family = AF_INET;
		localaddress.sin_addr.s_addr = inet_addr("127.0.0.1");
		localaddress.sin_port = htons(DEFAULT_PORT);

		// Create a SOCKET for connecting to server
		ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ListenSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			printf("Finished: press RETURN");
			while (getchar() != '\n')
				;
			WSACleanup();
			return 0;
		}


		// Setup the TCP listening socket
		iResult = bind(ListenSocket, (SOCKADDR *)&localaddress, sizeof(localaddress));
		if (iResult == SOCKET_ERROR)
		{
			printf("bind failed with error: %d\n", WSAGetLastError());

			closesocket(ListenSocket);
			WSACleanup();

			while (getchar() != '\n')
				;
			return 0;
		}

		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR)
		{
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			while (getchar() != '\n')
				;
			return 0;
		}

		int iConnectionNumber = 0;

		// wait for incoming connections and accept them as they come in:
		while (TRUE)
		{
			// Accept a client socket
			ClientSocket = accept(ListenSocket, NULL, NULL);
			if (ClientSocket == INVALID_SOCKET)
			{
				printf("accept failed with error: %d\n", WSAGetLastError());
				closesocket(ListenSocket);
				while (getchar() != '\n')
					;
				return 0;
			}
			// Allocate some memory to store any data we need to pass to the thread
			DataForThread* p = (DataForThread*)malloc(sizeof(DataForThread));
			p->ClientSocket = ClientSocket; // Socket to get data from
			p->iConnectionNumber = iConnectionNumber + 1; // number of this connection - add 1 to make it 1-based

			// Now create a thread to handle this connection, giving it the connection details
			// Note: calling the function direct would be:  HandleConnection( (LPVOID)p ); 
			HANDLE h = CreateThread(NULL, 0, HandleConnection, p, 0, NULL);
			CloseHandle(h); // We no longer need the handle to the thread - it is on its own
			
		}
	return 0;
}


int main()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Initialize the critical section one time only.
		if (!InitializeCriticalSectionAndSpinCount(&criticalSectionResources, 1024))
			return 1;

	////////////////////////////////////////////////////////////////////////////////////WINDOW FOR RESOURCES

	WNDCLASSEX resourcesWindow;
	resourcesWindow.cbSize = sizeof(WNDCLASSEX);
	resourcesWindow.style = 0;
	resourcesWindow.lpfnWndProc = WndProcResources;
	resourcesWindow.cbClsExtra = 0;
	resourcesWindow.cbWndExtra = 0;
	resourcesWindow.hInstance = GetModuleHandle(NULL);
	resourcesWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	resourcesWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
	resourcesWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	resourcesWindow.lpszMenuName = NULL;
	resourcesWindow.lpszClassName = "Resources";
	resourcesWindow.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&resourcesWindow))
	{
		MessageBox(NULL, "Resource Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	handleResourceWindow = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"Resources", // NEEDS TO MATCH THE CLASS NAME
		"Resource Access window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 500,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (handleResourceWindow == NULL)
	{
		MessageBox(NULL, "Resource Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(handleResourceWindow, SW_SHOW);
	UpdateWindow(handleResourceWindow);

	//////////////////////////////////////////////////////////////////////////////////WINDOW FOR THREADS

	WNDCLASSEX threadsWindow;
	threadsWindow.cbSize = sizeof(WNDCLASSEX);
	threadsWindow.style = 0;
	threadsWindow.lpfnWndProc = WndProcThreads;
	threadsWindow.cbClsExtra = 0;
	threadsWindow.cbWndExtra = 0;
	threadsWindow.hInstance = GetModuleHandle(NULL);
	threadsWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	threadsWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
	threadsWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	threadsWindow.lpszMenuName = NULL;
	threadsWindow.lpszClassName = "Threads";
	threadsWindow.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&threadsWindow))
	{
		MessageBox(NULL, "Threads Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	handleThreadWindow = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"Threads", // NEEDS TO MATCH THE CLASS NAME
		"Thread Progress window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 500,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (handleThreadWindow == NULL)
	{
		MessageBox(NULL, "Threads Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(handleThreadWindow, SW_SHOW);
	UpdateWindow(handleThreadWindow);

	//THREAD TO HANDLE CONNECTIONS////////////////////////////////

	HANDLE thread;
	thread = CreateThread(NULL, 0, Socket, NULL, 0, NULL);
	
	CloseHandle(thread); // We no longer need the handle to the thread - it is on its own
	

	MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);

	}
	return Msg.wParam; 

	DeleteCriticalSection(&criticalSectionResources);
				
}

