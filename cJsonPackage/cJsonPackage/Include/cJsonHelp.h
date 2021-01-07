#ifndef cJSONHelp__h
#define cJSONHelp__h

extern "C"
{
#include "cJSON.h"
}

class cJSONH {
private:
	bool IfInitialize = false;	///< ������Ƿ��Ѿ���ʼ��	
	cJSON* root = NULL;				///< ������ĸ�����ָ��
	const char* LastError="";	///< ��������ı�

	cJSON* PathParsed(cJSON* root, const char* path);
	cJSON* SelectNoCreate(cJSON* root, const char* path);

public:


	/**
	* @����: ����һ���յ�JSON���� ����Ѿ�����һ���ɶ�����������������
	*
	* @���� BOOL
	*		-false ����ʧ��
	*		-true �����ɹ�
	*/
	bool Create();

	/**
	* @����: �ͷŶ���
	*/
	void Delete();

	/**
	* @����: ȡ����ָ��
	*
	* @���� ���ڰ󶨵�JSON����ָ��
	*/
	cJSON* GetObject();

	/**
	* @����: ���ö���ָ��,���֮ǰ���ڶ���,�ɶ�����Զ��ͷ�
	* @����: void
	*
	* @���� ���һ�εĴ�����Ϣ
	*/
	void SetObject(cJSON* Object);

	/**
	* @����: ��ȡ���Ĵ����ı�
	*
	* @���� ���һ�εĴ�����Ϣ
	*/
	const char* GetErrorString();

	/**
	* @����: ����һ���յ�cJSON����	��̬����
	*
	* @���� �����Ķ���ָ��
	*/
	cJSON* CreateObject();

	/**
	* @����: ����һ���յ�cJSON�������	��̬����
	*
	* @���� �������������ָ��
	*/
	cJSON* CreateArray();

	/**
	* @����: ����һ��cJSON NULL ����	��̬����
	*
	* @���� �����Ķ���ָ��
	*/
	cJSON* CreateNull();

	/**
	* @����: ����һ��cJSON bool ����	��̬����
	* @����: ������boolֵ
	*
	* @���� �����Ķ���ָ��
	*/
	cJSON* CreateBool(bool);

	/**
	* @����: ����һ��cJSON string ����	��̬����
	* @����: ������stringֵ
	*
	* @���� �����Ķ���ָ��
	*/
	cJSON* CreateString(const char* string);

	/**
	* @����: ����һ��cJSON��ֵ����	��̬����
	* @����: ��������ֵ
	*
	* @���� �����Ķ���ָ��
	*/
	cJSON* CreateNumber(double num);

	/**
	* @����: ���ֽ�������Json,���֮ǰ�Ѿ�������,����Զ��ͷ�
	* @����: JsonStr	[in]		ָ��json�ַ����ı���
	*
	* @���� BOOL
	*		-false ����ʧ��
	*		-true �����ɹ�
	*/
	bool Parse(const char* JsonStr);

	/**
	* @����: ��ȡת���ı����Json����
	* @����: �Ƿ�Է��ص���Ϣ���и�ʽ��
	*
	* @���� ���ı���ʽչ�ֵ�Json����
	*/
	char* GetJsonforString(bool formatted);

	/**
	* @����: ��ȡ��ֵ������
	* @����: Path [in]		��ֵ����·�� ����:root.arr[0].key
	*
	* @���� ���ͳ���,��Ӧ cJSON_
	*/
	int GetItemType(const char* path);

	/**
	* @����: ��ȡ��������ָ��
	* @����: Path [in]		��ֵ����·�� ����:root.arr[0].key
	*
	* @���� ���������ָ��
	*/
	cJSON* GetParent(const char* path);

	/**
	* @����: ��ȡ�����Ա����
	* @����: Path [in]		��ֵ����·�� ����:root.arr[0].key
	*
	* @���� ���������ָ��
	*/
	int GetArraySize(const char* path);

	/**
	* @����: ��ȡ��Ӧ��ֵ��Stringֵ
	*			ע��:�����Ӧ��ֵ��ֵ���Ͳ�ΪString���ܻ���ִ���
	* @����: Path [in]		��ֵ����·�� ����:root.arr[0].key
	*
	* @���� ��Ӧ���ַ���,ʧ�ܷ��ؿ�
	*/
	const char* GetStringValue(const char* Path);


};

#endif