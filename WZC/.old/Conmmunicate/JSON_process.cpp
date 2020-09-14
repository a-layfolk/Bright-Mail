#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
using namespace rapidjson;
int main()
{
    // 1. 把 JSON 解析至 DOM。
    const char *json = "{\"project\"sdfsfg:\"rapidjson\",\"stars\":10}";
    Document d;
    ParseResult ok = d.Parse(json); //错误处理
    if (!ok)
    {
        printf("Error");
    }
    else
    {
        printf("%d\n", d["stars"].GetInt());
    }

    // 2. 利用 DOM 作出修改。
    /*    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
 
    // 3. 把 DOM 转换（stringify）成 JSON。
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
 
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;*/
    return 0;
}
