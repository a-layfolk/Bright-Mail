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

EMAIL_INFO *Json_To_Email_List(const char *JSON, int *list_size)
{
    Document d;
    ParseResult ok = d.Parse(JSON);
    EMAIL_INFO *CI = NULL;
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
                if (d["info"].Size() > 0 && d["info"][0].HasMember("emailTitle") && d["info"][0].HasMember("targetUsername") && d["info"][0].HasMember("emailTime") && d["info"][0].HasMember("emailId"))
                {

                    int size = d["size"].GetInt();
                    *list_size = size;
                    CI = new EMAIL_INFO[size];
                    for (int i = 0; i < d["info"].Size(); i++)
                    {
                        CI[i].emailTitle = new char[d["info"][i]["emailTitle"].GetStringLength()];
                        strcpy(CI[i].emailTitle, d["info"][i]["emailTitle"].GetString());

                        CI[i].targetUsername = new char[d["info"][i]["targetUsername"].GetStringLength()];
                        strcpy(CI[i].targetUsername, d["info"][i]["targetUsername"].GetString());

                        CI[i].emailTime = new char[d["info"][i]["emailTime"].GetStringLength()];
                        strcpy(CI[i].emailTime, d["info"][i]["emailTime"].GetString());

                        CI[i].emailId = new char[d["info"][i]["emailId"].GetStringLength()];
                        strcpy(CI[i].emailId, d["info"][i]["emailId"].GetString());
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
    // DataBag::EMAIL_INFO *EI = new EMAIL_INFO[2];
    // cout << "fuck1";
    // EI->emailId = (char *)"shit";
    // EI->emailTime = (char *)"bull";
    // EI->emailTitle = (char *)"fuck";
    // EI->targetUsername = (char *)"ffff";
    // char *str = DataBag::DataBag_Sd_List(2, EI);
    // cout << str << endl;
    // Document d;
    // d.Parse(str);
    // if (d["info"].IsArray())
    // {
    //     for (int i = 0; i < d["info"].Size(); i++)
    //     {
    //         cout << d["info"][i]["emailTitle"].GetStringLength() << endl;
    //     }
    // }
    int size;
    cout << "input list size" << endl;
    cin >> size;
    EMAIL_INFO *EI = new EMAIL_INFO[size];
    for (int i = 0; i < size; i++)
    {
        cout << "id:" << endl;
        char *id = new char[10];
        cin >> id;
        cout << "time:" << endl;
        char *ti = new char[10];
        cin >> ti;
        cout << "title:" << endl;
        char *tt = new char[10];
        cin >> tt;
        cout << "target:" << endl;
        char *tu = new char[10];
        cin >> tu;
        EI[i].emailId = id;
        EI[i].emailTime = ti;
        EI[i].emailTitle = tt;
        EI[i].targetUsername = tu;
        cout << endl;
    }
    char *JSON = DataBag_Sd_Mail_List(size, EI);
    cout << JSON << endl;
    int newSize;
    EMAIL_INFO *newEI = Json_To_Email_List(JSON, &newSize);

    for (int i = 0; i < newSize; i++)
    {
        cout << "id:" << newEI[i].emailId << endl;
        cout << "time:" << newEI[i].emailTime << endl;
        cout << "title:" << newEI[i].emailTitle << endl;
        cout << "target:" << newEI[i].targetUsername << endl;

        cout << endl;
    }
    delete[] newEI;
    delete[] JSON;
    delete[] EI;
    return 0;
}
