#ifndef cJSONHelp__h
#define cJSONHelp__h
#include <string>
#include <vector>

extern "C"
{
#include "cJSON.h"
}

typedef struct _JSONTYPESTUCT
{
	int Type;
	char* name;

}JSONTYPESTUCT, * PHJSONTYPESTUCT;

class cJSONH {
private:
	bool IfInitialize = false;	///< ������Ƿ��Ѿ���ʼ��	
	cJSON* root = NULL;				///< ������ĸ�����ָ��
	const char* LastError="";	///< ��������ı�

	cJSON* PathParsed(cJSON* root, const char* path);
	std::vector<JSONTYPESTUCT> PathParsedOrCreate(const char* path);
	bool SetValueOfJsonArr(cJSON* root, std::vector<JSONTYPESTUCT> jsonarr, int type, void* dataaddress);

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
	* @����: Path [in]		����·�� ����:root.arr[0].key
	*
	* @���� ���ͳ���,��Ӧ cJSON_
	*/
	int GetItemType(const char* path);

	/**
	* @����: ��ȡ��������ָ��
	* @����: Path [in]		������·�� ����:root.arr[0].key
	*
	* @���� ���������ָ��
	*/
	cJSON* GetParent(const char* path);

	/**
	* @����: ��ȡ�����Ա����
	* @����: Path [in]		����·�� ����:root.arr[0].key
	*
	* @���� ���������ָ��
	*/
	int GetArraySize(const char* path);

	/**
	* @����: ɾ������
	* @����: Path [in]		�������ڸ�·�� ����:root.arr[0]
	* @����: ItemName [in]	������
	* @����: Case [in]		�������Ƿ��Сд����
	*
	* @���� ����Ľڵ�ָ��
	*/
	cJSON* DetachItem(const char* path, const char* ItemName, bool Case);

	/**
	* @����: ɾ������
	* @����: Path [in]		����·�� ����:root.arr[0].key
	* @����: Item [in]		������
	*/
	void DeleteItem(const char* path, const char* Item);

	/**
	* @����: ɾ����Ա
	* @����: Path [in]		����·�� ����:root.arr[0].key
	* @����: which [in]		��Ա�±�
	*/
	void DeleteItemFromArray(const char* path, int which);

	/**
	* @����: ���ֵ�����������¼����Ժͳ�Ա
	* @����: Path [in]		������·�� ����:root.arr[0]
	*/
	void Clear(const char* path);

	/**
	* @����: ȡ��������
	* @����: Path [in]		����·�� ����:root.arr[0].key
	*
	* @���� ָ���Ӧ���Ե�ָ��
	*/
	cJSON* GetAttributes(const char* path);

	/**
	* @����: ȡ����������
	* @����: Path [in]		����·�� ����:root.arr[0].key
	*
	* @���� �������ַ���
	*/
	const char* GetItemName(const char* path);

	/**
	* @����: ��������Ա
	* @����: Path [in]		����·�� ����:root.arr[0].key
	* @����: item [in]		�����Աָ��
	* 
	* @���� bool
	*/
	cJSON_bool AddItemToArray(const char* path, cJSON* item);

	/**
	* @����: ���ö�������
	* @����: Path [in]		����·�� ����:root.arr[0].key
	* @����: Value [in]		����ָ��
	*
	* @���� bool
	*/
	cJSON_bool SetObjectValue(const char* Path, cJSON* Value);



	/**
	* @����: ��ȡ��Ӧ���Ե�Stringֵ
	* @����: Path [in]		����·�� ����:root.arr[0].key
	*
	* @���� ��Ӧ���ַ���,ʧ�ܷ��ؿ�
	*/
	const char* GetStringValue(const char* Path);

	/**
	* @����: ���ö�Ӧ��ֵ���ı�ֵ
	* @����: Path [in]		����·�� ����:root.arr[0].key	�����ڻ����д���
	* @����: String [in]		��Ҫ���õ�ֵ
	*
	* @���� bool
	*/
	cJSON_bool SetStringValue(const char* Path, const char* String);

	/**
	* @����: ���ö�Ӧ��ֵ����ֵ
	* @����: Path [in]		����·�� ����:root.arr[0].key	�����ڻ����д���
	* @����: num [in]		��Ҫ���õ�ֵ
	*
	* @���� bool
	*/
	cJSON_bool SetNumberValue(const char* Path, double num);
};

#endif