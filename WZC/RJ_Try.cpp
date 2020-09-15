#include "Dependencies/My_Json.h"
#include "Dependencies/rapidjson/rapidjson.h"
#include "Dependencies/rapidjson/document.h"
#include "Dependencies/rapidjson/reader.h"
#include "Dependencies/rapidjson/writer.h"
#include "Dependencies/rapidjson/stringbuffer.h"
#include <iostream>
using namespace std;
using namespace DataBag;
using namespace rapidjson;
using namespace My_Json;
CONTATCT_INFO *Json_To_Contact_List(const char *JSON, int *list_size)
{
    Document d;
    ParseResult ok = d.Parse(JSON);
    CONTATCT_INFO *CI = NULL;
    bool is_ok = false;
    if (!ok)
    {
        is_ok = false;
    }
    else
    {
        if (d.HasMember("info") && d.HasMember("size"))
        {
            if (d["info"].IsArray())
            {
                if (d["info"].Size() > 0 && d["info"][0].HasMember("telephone") && d["info"][0].HasMember("userId") && d["info"][0].HasMember("userName"))
                {

                    int size = d["size"].GetInt();
                    *list_size = size;
                    CI = new CONTATCT_INFO[size];
                    for (int i = 0; i < d["info"].Size(); i++)
                    {
                        CI[i].telephone = new char[d["info"][i]["telephone"].GetStringLength()];
                        strcpy(CI[i].telephone, d["info"][i]["telephone"].GetString());

                        CI[i].userId = new char[d["info"][i]["userId"].GetStringLength()];
                        strcpy(CI[i].userId, d["info"][i]["userId"].GetString());

                        CI[i].userName = new char[d["info"][i]["userName"].GetStringLength()];
                        strcpy(CI[i].userName, d["info"][i]["userName"].GetString());
                    }
                    is_ok = true;
                }
            }
        }
    }
    if (is_ok)
    {
        return CI;
    }
    else
    {
        return NULL;
    }
}

int main(int argc, char const *argv[])
{
    DataBag::EMAIL_INFO *EI = new EMAIL_INFO[2];
    cout << "fuck1";
    EI->emailId = (char *)"shit";
    EI->emailTime = (char *)"bull";
    EI->emailTitle = (char *)"fuck";
    EI->targetUsername = (char *)"ffff";
    char *str = DataBag::DataBag_Sd_List(2, EI);
    cout << str << endl;
    Document d;
    d.Parse(str);
    if (d["info"].IsArray())
    {
        for (int i = 0; i < d["info"].Size(); i++)
        {
            cout << d["info"][i]["emailTitle"].GetStringLength() << endl;
        }
    }

    return 0;
}
