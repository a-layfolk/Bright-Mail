#include <iostream>

#include "Dependencies/rapidjson/document.h"
#include "Dependencies/rapidjson/writer.h"
#include "Dependencies/rapidjson/stringbuffer.h"
#include "Dependencies/My_Json.h"
using namespace DataBag;
using namespace My_Json;
void test2()
{
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    writer.StartObject();
    // Stcode部分

    // 构造Timestamp
    writer.Key(Key_Type::request_type);
    writer.String(Rq_Type::sd_list);

    writer.Key("info");

    writer.StartArray();
    // 报警监测数据数组列表
    for (int i = 0; i < 5; i++)
    {
        writer.StartObject();

        writer.Key("emailTitle");
        writer.String("hhh");
        writer.Key("targetUsername");
        writer.String("ffff");
        writer.Key("emailTime");
        writer.String("uuuu");
        writer.Key("emailId");
        writer.String("ggggg");
        writer.EndObject();
    }
    writer.Key("size");
    writer.Int(5);
    writer.EndArray();

    writer.EndObject();

    char *JSON = new char[s.GetSize()];
    strcpy(JSON, s.GetString());
    std::cout << JSON;
    s.GetString();

    // 打印生成的json字符串
    // std::cout << "test3(), strJson3为: " << strJson3.c_str() << std::endl;
}

int main(int argc, char *argv[])
{
    test2();

    return 0;
}