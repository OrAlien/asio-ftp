#pragma once
#include <vector>
//#define RAPIDJSON_HAS_STDSTRING  1
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h" 
#include "rapidjson/writer.h" 
#include "rapidjson/stringbuffer.h" 
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/encodedstream.h"


const int g_nMaxReadFileLen = 65536;
const int g_nMaxWriteFileLen = 65536;
//readme

//��Ҫ���ƻ�ԭ��DOM�Ľṹ����Ҫ������ȿ���
//Value.CopyFrom(vTemp, m_document.GetAllocator());
using namespace   rapidjson;
//����ڵ��������ظ��ģ���������������ȡһ�����أ�������ֲ����ڣ��򷵻�false;  ɾ��ͬ��
//�����뱣֤���ֵ�Ψһ��,����ܿ��ܵò�������õ��Ľ����
//Ϊ�����Ķ���ֱ�ӽ����в�ѯ�����г�
//����ֵ֧�����¼�������
//int, unsigned, int64_t, uint64_t,double,float,string,bool,Vaule*

//��ø��ڵ���ָ�����ֵ
//bool GetNodeValue(const char* pszName, T& retValue) 

//��ø��ڵ���ָ�������ֵ
//bool GetNodeArrayValue(const char* pszName, std::vector<T>& retValue);

//���ָ���ڵ���ָ�����ֵ
//bool GetNodeValue(const char* pszName, const rapidjson::Value& vNode, T& retValue); 

//���ָ���ڵ���ָ�������ֵ
//bool GetNodeArrayValue(const char* pszName,const rapidjson::Value& vNode, std::vector<T>& retValue);

//�Ӹ��ڵ㿪ʼ��ѯ�������ڵ���\�ָ�,��"root\department\section\office\zhangsan"  ���ٲ�ѯ�����ڵ㣨һ���ڵ���ֱ��ʹ������ĺ�����
//bool GetNodeValueByPath(const char* pszName, const rapidjson::Value& vNode, T& retValue); 

//bool GetNodeArrayValueByPath(const char* pszName, const rapidjson::Value& vNode, T& retValue); 

class CJson
{
public:
    CJson(void);
    virtual ~CJson(void);
    //��ȡ
    //���ֽ�����ȡ 
    bool ReadUtf8(const char* pchJson);
    bool ReadUtf16LE(const wchar_t* pchJson);
    bool ReadUtf16BE(const wchar_t* pchJson);
    bool ReadUtf32LE(const unsigned int* pchJson);
    bool ReadUtf32BE(const unsigned int*pchJson);
    //���ļ���ȡ
    bool ReadFromFile(const std::string& strPath);
    //��ѯ
    template <typename T>
    bool GetNodeValue(const char* pszName, T& retValue) //Ŀǰ֧��int, unsigned, int64_t, uint64_t,double,string,bool,Vaule �������ͣ����෵�ش���
    {
        if (m_document.FindMember(pszName) == m_document.MemberEnd())
        {
            return false;
        }
        Value& vTemp = m_document[pszName]; 
        return GetValue(vTemp, retValue);
    }


    template <typename T>
    bool GetNodeArrayValue(const char* pszName, std::vector<T>& retValue)
    {
        if (m_document.FindMember(pszName) == m_document.MemberEnd())
        {
            return false;
        }
        Value& vTemp = m_document[pszName];
        if (!vTemp.IsArray())
        {
            return false;
        }
        retValue.clear();
        int kTemp = vTemp.Size();
        for (SizeType	i	=	0; i	<	vTemp.Size();	i++)
        {
            Value& vArrayTemp = vTemp[i];
            T retTempValue;
            if (GetValue(vArrayTemp, retTempValue))
            {
                retValue.push_back(retTempValue);
            }
            else
            {
                retValue.clear();
                return false;
            }
        }
        return true;
    }

    template <typename T>
    bool GetNodeValue(const char* pszName, T& retValue,  rapidjson::Value* pNode)  //Ŀǰ֧��int, unsigned, int64_t, uint64_t,double,string,bool��Vaule �������ͣ����෵�ش���
    {
        if (pNode->FindMember(pszName) == pNode->MemberEnd())
        {
            return false;
        }
        Value& vTemp = (*pNode)[pszName]; 
        return GetValue(vTemp, retValue);
    }
    template <typename T>
    bool GetNodeArrayValue(const char* pszName, std::vector<T>& retValue,  rapidjson::Value* pNode)
    {
        if (pNode->FindMember(pszName) == pNode->MemberEnd())
        {
            return false;
        }
        Value& vTemp = (*pNode)[pszName];
        if (!vTemp.IsArray())
        {
            return false;
        }
        retValue.clear();
        for (SizeType	i	=	0; i	<	vTemp.Size();	i++)
        {
            Value& vArrayTemp = vTemp[i];
            T retTempValue;
            if (GetValue(vArrayTemp, retTempValue))
            {
                retValue.push_back(retTempValue);
            }
            else
            {
                retValue.clear();
                return false;
            }
        }
        return true;
    }

    //�Ӹ��ڵ㿪ʼ�������ڵ���\�ָ�,��"root\department\section\office\zhangsan"  ,��һ���ڵ������object
    template <typename T>
    bool GetNodeValueByPath(const char* pszName, T& retValue)
    {
        string strTemp = pszName;
        string strSplit = "\\\\";
        vector<string> vtTemp;
        vtTemp = stringsplit(strTemp , strSplit);
        if (0 == (int)vtTemp.size() )
        {
            return false;
        }
        string strName = vtTemp[0];
        if (m_document.FindMember(strName.c_str()) == m_document.MemberEnd())
        {
            return false;
        }
        int nSize = (int)vtTemp.size();
        Value* pVTemp = &m_document[strName.c_str()];
        if (1 == nSize)
        {
            return  GetValue(*pVTemp, retValue);
        }
        for (int i = 1; i < (int)vtTemp.size() - 1; ++i )
        {
            if(!pVTemp->IsObject())
            {
                return false;
            }
            strName = vtTemp[i];
            if (pVTemp->FindMember(strName.c_str()) == pVTemp->MemberEnd())
            {
                return false;
            }
            pVTemp = &(*pVTemp)[strName.c_str()];
        }
        //�������һ��
        strName = vtTemp[(int)vtTemp.size() - 1];
        if (pVTemp->FindMember(strName.c_str()) == pVTemp->MemberEnd())
        {
            return false;
        }
        pVTemp = &(*pVTemp)[strName.c_str()];
        return  GetValue(*pVTemp, retValue);
    }

    template <typename T>
    bool GetNodeArrayValueByPath(const char* pszName, std::vector<T>& retValue)
    {
        string strTemp = pszName;
        string strSplit = "\\\\";
        vector<string> vtTemp;
        vtTemp = stringsplit(strTemp , strSplit);
        if (0 == (int)vtTemp.size() )
        {
            return false;
        }
        string strName = vtTemp[0];
        if (m_document.FindMember(strName.c_str()) == m_document.MemberEnd())
        {
            return false;
        }
        int nSize = (int)vtTemp.size();
        Value* pVTemp = &m_document[strName.c_str()];
        if (1 == nSize)
        {
            if (!(*pVTemp).IsArray())
            {
                return false;
            }
            retValue.clear();
            for (SizeType	i	=	0; i	<	(*pVTemp).Size();	i++)
            {
                Value& vArrayTemp = (*pVTemp)[i];
                T retTempValue;
                if (GetValue(vArrayTemp, retTempValue))
                {
                    retValue.push_back(retTempValue);
                }
                else
                {
                    retValue.clear();
                    return false;
                }
            }
            return  true;
        }
        for (int i = 1; i < (int)vtTemp.size() - 1; ++i )
        {
            if(!pVTemp->IsObject())
            {
                return false;
            }
            strName = vtTemp[i];
            if (pVTemp->FindMember(strName.c_str()) == pVTemp->MemberEnd())
            {
                return false;
            }
            pVTemp = &(*pVTemp)[strName.c_str()];
        }
        //�������һ��
        strName = vtTemp[(int)vtTemp.size() - 1];
        if (pVTemp->FindMember(strName.c_str()) == pVTemp->MemberEnd())
        {
            return false;
        }
        pVTemp = &(*pVTemp)[strName.c_str()];
        if (!(*pVTemp).IsArray())
        {
            return false;
        }
        retValue.clear();
        for (SizeType	i	=	0; i	<	(*pVTemp).Size();	i++)
        {
            Value& vArrayTemp = (*pVTemp)[i];
            T retTempValue;
            if (GetValue(vArrayTemp, retTempValue))
            {
                retValue.push_back(retTempValue);
            }
            else
            {
                retValue.clear();
                return false;
            }
        }
        return  true;
    }
	
    //�����string
    bool OutputToString(std::string& str);//����ǰ������������������string��Ŀǰ����UTF-8����ʽ

	 //�����fule
    bool OutputToFile(const std::string& strPath);//����ǰ�������������������ļ���Ŀǰ����UTF-8����ʽ



private:
    void PrintPhraseError();
    bool GetValue(rapidjson::Value& vTemp, int& retValue);
    bool GetValue(rapidjson::Value& vTemp, double& retValue);
    bool GetValue(rapidjson::Value& vTemp, std::string& retValue);
    bool GetValue(rapidjson::Value& vTemp, bool& retValue);
    bool GetValue(rapidjson::Value& vTemp, int64_t& retValue);
    bool GetValue(rapidjson::Value& vTemp, unsigned& retValue);
    bool GetValue(rapidjson::Value& vTemp, uint64_t& retValue);
    bool GetValue(rapidjson::Value& vTemp, Value*& retValue);


	//���ӣ�ɾ�����޸�
    bool Check();//���DOMͬһ���Ƿ���ͬ���Ľڵ㣬

    rapidjson::Document m_document;
  

//	static char m_scMaxFileReadBuffer[g_nMaxReadFileLen];
//	static char m_scMaxFileWriteBuffer[g_nMaxWriteFileLen];
};

//char CJson::m_scMaxFileReadBuffer[g_nMaxReadFileLen];
//char CJson::m_scMaxFileWriteBuffer[g_nMaxWriteFileLen];


