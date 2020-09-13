#include <iostream>
#include <windows.h>
#include <vector>

HANDLE h = INVALID_HANDLE_VALUE;
std::vector<int> data;

bool getData = false;
bool isDataReady = false;

DWORD WINAPI Client(LPVOID arg) {
    HANDLE he = OpenEventA(EVENT_MODIFY_STATE, true, "MyServer");
    SetEvent(he);
    std::cout << "Client Event\n";
    getData = true;
    std::cout << data[0] << " " << data[1] << "\n";
    return 0;
}

DWORD WINAPI Server(LPVOID arg) {
    std::cout << "Server Wait\n";
    DWORD res = WaitForSingleObject(h, INFINITE);
    data.push_back(1001);
    data.push_back(1002);
    isDataReady = TRUE;
    std::cout << "Server Activ\n";
    return 0;
}

int main()
{
    h = CreateEventA(0, FALSE, FALSE, "MyServer");
    if (h == INVALID_HANDLE_VALUE) {
        return -1;
    }

    CreateThread(0, 0, Server, 0, 0, 0);

    Sleep(2000);
    
    CreateThread(0, 0, Client, 0, 0, 0);

    Sleep(1000);
}
