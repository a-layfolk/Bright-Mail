#include <iostream>
#include "Communi_Core.hpp"
int main(int argc, char const *argv[])
{
    COMMUNI::Communi_Core CC("0.0.0.0");
    char fuck[200];
    while (1)
    {
        cin >> fuck;
        CC.Send_Data(fuck);
    }

    return 0;
}
