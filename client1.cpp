#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include <iostream>
using namespace std;
void error_handling(const char *message);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[1024];
    int str_len = 0;
    int read_len = 0;

    ofstream ofs;
    ofs.open("text.dat", ios::binary);

    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(6666);

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error!");
    const char  *msg = "{\"key\": 1, \"data\": \"ppp\"}";
    while(1)
    {
        send(sock, msg, strlen(msg), 0);
        read_len = recv(sock, message, 1024, 0);
        message[read_len] = 0;
        std::cout << "recv: "<< message << "len " << read_len << std::endl;
        if(read_len <= 0)
            error_handling("read() error!");
        sleep(1);
        //ofs.write(message,read_len);
        //str_len += read_len;
        //if(str_len > 10 *1024 * 1024)
        //    break;

    }
    ofs.close();
    close(sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    //exit(1);
}
