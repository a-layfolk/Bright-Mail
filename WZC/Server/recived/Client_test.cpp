#include "Client.hpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    CLIENT_TO_SOCKET::Client_socket clnt_socket("127.0.0.1");
    // clnt_socket.text_file_transfer("./test");
    // clnt_socket.file_transfer(argv[1]);
    clnt_socket.Send_to_server("file", (char *)argv[1]);

    return 0;
}
