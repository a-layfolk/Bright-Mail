#include "Client.hpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    CLIENT_TO_SOCKET::client_socket clnt_socket;
    // clnt_socket.text_file_transfer("./test");
    clnt_socket.file_transfer(argv[1]);
    return 0;
}
