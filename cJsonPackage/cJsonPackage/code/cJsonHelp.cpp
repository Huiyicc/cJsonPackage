#include "cJSON.h"
#include "cJsonHelp.h"
#include <string>

//@ ȡ�����ı�
const char* cJSONH::GetErrorString() {
	return LastError;
}

//@ ��������
bool cJSONH::Create() {
	root = cJSON_CreateObject();
	if (root == NULL) {
		LastError = cJSON_GetErrorPtr();
		return false;
	}
	return true;
}

//@ �ͷ�����
void cJSONH::Delete() {
	cJSON_Delete(root);
	root = NULL;
}

//@ ��������
bool cJSONH::Parse(const char* JsonStr) {
	if (root != NULL) {
		cJSON_Delete(root);
	}
	root = cJSON_Parse(JsonStr);
	if (root == NULL) {
		LastError = cJSON_GetErrorPtr();
		return false;
	}
	IfInitialize = true;
	return true;
}

//@ ȡ����ָ��
cJSON* cJSONH::GetObject() {
	return root;
}

//@ ���ö���ָ��
void cJSONH::SetObject(cJSON* Object) {
	if (root!=NULL) {
		cJSON_Delete(root);
	}
	root = Object;
}

//@ ��������
cJSON* cJSONH::CreateObject() {
	return cJSON_CreateObject();
}

//@ �����������
cJSON* cJSONH::CreateArray() {
	return cJSON_CreateArray();
}

//@ �����ն���
cJSON* cJSONH::CreateNull() {
	return cJSON_CreateNull();
}

//@ �����߼�����
cJSON* cJSONH::CreateBool(bool boolean) {
	return cJSON_CreateBool(boolean);
}

//@ �����ı�����
cJSON* cJSONH::CreateString(const char* string) {
	return cJSON_CreateString(string);
}

//@ ������ֵ����
cJSON* cJSONH::CreateNumber(double num) {
	return cJSON_CreateNumber(num);
}

//@ ȡJson�����ı�
char* cJSONH::GetJsonforString(bool formatted) {
	if (formatted) {
		return cJSON_Print(root);
	}
	else {
		return cJSON_PrintUnformatted(root);
	}
}

//@ ȡ����
int cJSONH::GetItemType(const char* path){
	cJSON* ltp = PathParsed(root, path);
	if (ltp==NULL) {
		return 0;
	}
	return ltp->type;
}

//@ ȡ����
cJSON* cJSONH::GetParent(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return 0;
	}
	return ltp->prev;
}

//@ ȡ��Ա��
int cJSONH::GetArraySize(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return 0;
	}
	return cJSON_GetArraySize(ltp);
}

//@ ȡ�ı�����
const char* cJSONH::GetStringValue(const char* Path) {
	cJSON* ret = PathParsed(root, Path);
	if (ret!=NULL) {
		printf("%s\n" ,ret->valuestring);
		return ret->valuestring;
	}
	else {
		return "";
	}
	return "";
}





//						==================
//				==================================
//						==================

//@ ��·��ȡ��Ӧ�ڵ�
cJSON* cJSONH::PathParsed(cJSON* root, const char* path) {
	std::string stpath = path;
	if (path==NULL) {
		return NULL;
	}
	size_t StrLen			///< ·������
		= stpath.length();
	if (StrLen==0) {
		return NULL;
	}
	
	size_t OldSubscript		///< ��һ����ǵ�λ��
		= 0;
	size_t pos		///< ��ǵ㵱ǰλ��
		= 0;
	bool inArray=false;		///< ��һ����ǵ��Ƿ�������ͷ [
	cJSON* ctmp = root;
	bool hasName = false;
	bool hasIndex = true;
	size_t namePos = 0,nameLen,indexPos = 0;
	
	while (pos <= StrLen)
	{
		char wchar = stpath[pos];
		if (wchar == '\\') {
			char nextchar = stpath[pos + 1];
			if (nextchar == '.'
			|| nextchar == '['
			|| nextchar == ']'
			|| nextchar == '\\'
			) {
				stpath.erase(pos,1);
				--StrLen;
			}
		}
		else if (wchar == '.' || pos == StrLen)	//.���߽�β
		{
			hasName = namePos < pos;
			if (hasName) {
				nameLen = pos - namePos;
				//printf( ".:%s\n", stpath.substr(namePos, nameLen).c_str());
				ctmp = cJSON_GetObjectItem(ctmp, stpath.substr(namePos, nameLen).c_str());
			}
			namePos = pos + 1;
		}
		else if (wchar == '[')
		{
			indexPos = pos + 1;
			hasIndex = true;
			hasName = namePos < pos;
			if (hasName) {
				nameLen = pos - namePos;
				//printf("[:%s\n", stpath.substr(namePos, nameLen).c_str());
				ctmp = cJSON_GetObjectItem(ctmp, stpath.substr(namePos, nameLen).c_str());
			}
			namePos = pos + 1;
		}
		else if (wchar == ']')
		{
			if (hasIndex) {
				nameLen = pos - indexPos;
				//printf("]:%d\n", atoi(stpath.substr(namePos, nameLen).c_str()));
				ctmp = cJSON_GetArrayItem(ctmp, atoi(stpath.substr(namePos, nameLen).c_str()));
			}
			namePos = pos + 1;
		}
		if (ctmp==NULL) {
			return NULL;
		}
		++pos;
		//OldSubscript = Subscript;
		
	}
	return ctmp;
}


cJSON* cJSONH::SelectNoCreate(cJSON* root,const char* path) {


	return 0;
}


