// RapidJsonTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Json.h"
#include "common.h"
#include <iostream>


using namespace std;
void TestOutputJson();

using namespace std;
int main(int argc, char* argv[])
{
  //  OspInit(true, 2401);
    string strWait;
    cin >> strWait;
	TestOutputJson();

    //string strLogFileName = "JsonLog.txt";
    //if (!OspOpenLogFile(strLogFileName.c_str(), 1, 3))
    //{
    //    cout <<"Log file open failed"<<endl;
    //    OspPrintf(true, true, "Log file open failed \n");
    //}
    //OspPrintf(true, true, "Osp ��ʼ���ɹ�\n");
    CJson cTemp;
    string strPath1 = "D:\\TestData\\2json.txt";
    if(!cTemp.ReadFromFile(strPath1))
    {
        cout <<"read error" <<endl;
        return -1;
    }
    //�õ�����1������2������
    string strUtf8 = ws2utf8(L"����1");
    string strDst;  
    if (!cTemp.GetNodeValue(strUtf8.c_str(), strDst))
    {
        cout <<"������"<<endl;
        return -1;
    }
    cout << utf8_2_s(strDst)  <<endl;
    strUtf8 = ws2utf8(L"����2");
    if (!cTemp.GetNodeValue(strUtf8.c_str(), strDst))
    {
        cout <<"������"<<endl;
        return -1;
    }
    cout << utf8_2_s(strDst)  <<endl;
    strUtf8 = ws2utf8(L"����");
    int nDst;
    if (!cTemp.GetNodeValue(strUtf8.c_str(), nDst))
    {
        cout <<"������"<<endl;
        return -1;
    }
    cout << nDst <<endl;

    //��������  
    strUtf8 = ws2utf8(L"����1");
    std::vector<double> vtTemp;
    if(!cTemp.GetNodeArrayValue(strUtf8.c_str(), vtTemp))
    {
        cout <<"������"<<endl;
        return -1;
    }

    //���ʽڵ�
    strUtf8 = ws2utf8(L"�ڵ�1");
    Value *pNode;
    if(!cTemp.GetNodeValue(strUtf8.c_str(), pNode))
    {
        cout <<"������"<<endl;
        return -1;
    }
    //�õ��ڵ�1�� ����11������
    strUtf8 = ws2utf8(L"����11");
    if (!cTemp.GetNodeValue(strUtf8.c_str(), strDst, pNode))
    {
        cout <<"������"<<endl;
        return -1;
    }
    cout << utf8_2_s(strDst)  <<endl;
    //�õ��ڵ�1�Ľڵ�11�Ľڵ�
    strUtf8 = ws2utf8(L"�ڵ�1111");
    Value* pNode11;
    if(!cTemp.GetNodeValue(strUtf8.c_str(),pNode11, pNode))
    {
        cout <<"������"<<endl;
        return -1;
    }
    //��������ڵ�Ĳ�������
    //ֱ�ӴӸ�����ĳ���ڵ������
    strUtf8 = ws2utf8(L"�ڵ�1\\�ڵ�1111\\����111");
    string vTemp2;
    if (!cTemp.GetNodeValueByPath(strUtf8.c_str(), vTemp2))
    {
        cout <<"������"<<endl;
        return -1;
    }
    cout << utf8_2_s(vTemp2)  <<endl;
    //�����������
    strUtf8 = ws2utf8(L"�ڵ�1\\�ڵ�1111");
    Value* pNode111; 
    if (!cTemp.GetNodeValueByPath(strUtf8.c_str(), pNode111))
    {
        cout <<"������"<<endl;
        return -1;
    }

    strUtf8 = ws2utf8(L"�ڵ�1\\�ڵ�2");
    std::vector<string> vtstrTemp; 
    if (!cTemp.GetNodeArrayValueByPath(strUtf8.c_str(), vtstrTemp))
    {
        cout <<"������"<<endl;
        return -1;
    }
    for (int i = 0; i < (int)vtstrTemp.size(); ++i)
    {
        cout << utf8_2_s(vtstrTemp[i])  <<endl;
    }


    std::vector<Value *> vtVTemp;
    strUtf8 = ws2utf8(L"����111");
    if (!cTemp.GetNodeArrayValue(strUtf8.c_str(), vtVTemp, pNode111))
    {
        cout <<"������"<<endl;
        return -1;
    }
    strUtf8 = ws2utf8(L"����1111");
    if (!cTemp.GetNodeValue(strUtf8.c_str(),  strDst, vtVTemp[0]))
    {
        cout <<"������"<<endl;
        return -1;
    }
    cout << utf8_2_s(strDst)  <<endl;

    strUtf8 = ws2utf8(L"����1111");
    if (!cTemp.GetNodeValue(strUtf8.c_str(),  nDst, vtVTemp[0]))
    {
        cout <<"������"<<endl;
        return -1;
    }
	

    cout << nDst  <<endl;
	cTemp.OutputToString(strUtf8);
	cout << utf8_2_s(strUtf8)  <<endl;
	//�˴������һ���ڵ�

	rapidjson::Document doc1;
	doc1.SetObject();
	Value author;
	char buffer[10];
	int len = sprintf(buffer, "%s %s", "�й�", "�й�"); // ��̬�������ַ�����
	author.SetString(buffer, len, doc1.GetAllocator());
	memset(buffer, 0, sizeof(buffer));
	doc1.AddMember ("aa", author, doc1.GetAllocator());
	//char *p1 = "aa";
	//const char *p2 = "bb";
	//doc1.AddMember (p2, author, doc1.GetAllocator());
	StringBuffer buffer2;
	Writer<StringBuffer> writer(buffer2);
	if (!doc1.Accept(writer))
	{
	//	OspPrintf(true, true, "ת���ַ���ʧ��");
        return false;
	}
	string str2 = buffer2.GetString();
	cout<<str2<<endl;



	cout << nDst  <<endl;
	cTemp.OutputToString(strUtf8);
	cout << utf8_2_s(strUtf8)  <<endl;

    string strTemp2;
    cin>>strTemp2;

  //  OspCloseLogFile();
//    OspQuit();
    return 0;
   
    getchar(); 
	return 0;
}
void TestOutputJson()
{
	CJson cTemp;
	string strPath1 = "{\"����2\": \"�������\"}";
//	string strUtf8 = ws2utf8(L"{\"����2\": \"�������\"}");
    if(!cTemp.ReadUtf8(strPath1.c_str()))
    {
        cout <<"read error" <<endl;
        return;
    }
	
	cout << strPath1.c_str() <<endl;
	string strOut;
	cTemp.OutputToString(strOut);

	string strSavePath = "D:/TestData/1/a10.txt";
	FILE*	fp	=	fopen(strSavePath.c_str(),	"wb");	//	��Windowsƽ̨ʹ��"w"
	if (!fp)
	{
//		OspPrintf(true, true, "�ļ�%s��ʧ��",  strSavePath.c_str());
		return ;
	}
	fwrite(strOut.c_str(), 1, strOut.size(), fp);
	fclose(fp);



	//
	StringBuffer s;
	//Writer<StringBuffer> writer(s);
	PrettyWriter<StringBuffer> writer(s);
	writer.StartObject();
	std::string str1 = "hello";
	writer.Key(str1.c_str());
	writer.String("world");
	writer.Key("t");
	writer.Bool(true);
	writer.Key("f");
	writer.Bool(false);
	writer.Key("n");
	writer.Null();
	writer.Key("i");
	writer.Uint(123);
	writer.Key("pi");
	writer.Double(3.1416);
	writer.Key("a");
	writer.StartArray();
	for (unsigned i = 0; i < 4; i++)
		writer.Uint(i);
	writer.EndArray();

	writer.Key("�ڵ�11");
	writer.StartObject();
	writer.Key("����3");
	writer.StartArray();
	for (unsigned i = 0; i < 4; i++)
	{
		writer.StartObject();
		char ch = 'a' + i;
		string strTemp, strTemp2;
		strTemp = "test 5";
		strTemp2 = "name 5";
		strTemp[5] = ch;
		writer.Key(strTemp2.c_str());
		writer.String(strTemp.c_str());
		writer.EndObject();
	}
	writer.EndArray();
	writer.EndObject();
	writer.EndObject();
	cout << s.GetString() << endl;
}