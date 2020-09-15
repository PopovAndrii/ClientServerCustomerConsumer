#include <iostream>
#include <windows.h>
#include <vector>

HANDLE h1 = INVALID_HANDLE_VALUE;
HANDLE h2 = INVALID_HANDLE_VALUE;
std::vector<int> data;

int SetEventName(const char* name) {
    HANDLE h = OpenEventA(EVENT_MODIFY_STATE, true, name);
    if (h == INVALID_HANDLE_VALUE) return -1;
    SetEvent(h);
    return 0;
}

DWORD WINAPI Client(LPVOID arg) {
    SetEventName("MyClient"); // activate server 

    std::cout << "Client Event. Wait data[]\n";
    DWORD res = WaitForSingleObject(h2, INFINITE);

    std::cout << data[0] << " " << data[1] << "\n";
    return 0;
}

DWORD WINAPI Server(LPVOID arg) {
    std::cout << "Server Start. Wait Client Event\n";
    DWORD res = WaitForSingleObject(h1, INFINITE);

    data.push_back(1001);
    data.push_back(1002);

    SetEventName("MyServer"); // activate client 
    return 0;
}

int main()
{
    h1 = CreateEventA(0, FALSE, FALSE, "MyClient");
    if (h1 == INVALID_HANDLE_VALUE) return -1;

    h2 = CreateEventA(0, FALSE, FALSE, "MyServer");
    if (h2 == INVALID_HANDLE_VALUE) return -1;

    CreateThread(0, 0, Server, 0, 0, 0);
    CreateThread(0, 0, Client, 0, 0, 0);
       
    Sleep(1000);

    return 0;
}

