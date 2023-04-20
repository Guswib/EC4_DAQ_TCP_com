//#include <cstring>
#include <iostream>
#include <string>

//#include <sys/types.h>
//#include <unistd.h>
#include <WS2TCPIP.h>
//#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    cout << "start Winsock, Err #"  << endl;
    //Create a winsocket
    string ipAddress = "127.0.0.1";

    int port =3364;

    WSAData data;
    WORD ver = MAKEWORD(2,2);
    int wsResult = WSAStartup(ver, &data);
    if(wsResult!=0){
        cout << "Cant start Winsocket, Err #" << wsResult << endl;
        return -1;
    }
    //Create Socket
    SOCKET sock=socket(AF_INET,SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
        {
             cout << "Cant create socket, Err #" << WSAGetLastError() << endl;
             return -1;
        }
    //fill hint struct
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connResult==SOCKET_ERROR){
        cout << "Cant connect to socket, Err #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }
    //Do-while loop to send and receive data
    char buf[4096];
    string userInput;
     cout << "Looping:" << endl;
    do{
        cout << "> ";
        getline(cin,userInput);
        if (userInput.size()>0)
        {
        cout << "Looping:" << userInput << endl;
        userInput=userInput+ "\r\n";
        int sendResult = send(sock, userInput.c_str(), userInput.size(),0);
        cout << "sendResult:" << sendResult << endl;
        if(sendResult !=SOCKET_ERROR)
            //wait ffor responce
            ZeroMemory(buf,4096);
            int bytesReceived =recv(sock,buf,4096,0);
            cout << "bytesReceived:" << bytesReceived << endl;

            if (bytesReceived>0)
            {
                //Echo to the console
                cout << "SERVER> " << string(buf,0,bytesReceived) << endl;
            }
        }
    }while (userInput.size()>0);

    closesocket(sock);
    WSACleanup();
}
