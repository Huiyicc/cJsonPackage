#include "cJSON.h"
#include "cJsonHelp.h"
#include <string>

//@ 取错误文本
const char* cJSONH::GetErrorString() {
	return LastError;
}

//@ 创建对象
bool cJSONH::Create() {
	root = cJSON_CreateObject();
	if (root == NULL) {
		LastError = cJSON_GetErrorPtr();
		return false;
	}
	return true;
}

//@ 释放数据
void cJSONH::Delete() {
	cJSON_Delete(root);
	root = NULL;
}

//@ 解析数据
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

//@ 取对象指针
cJSON* cJSONH::GetObject() {
	return root;
}

//@ 设置对象指针
void cJSONH::SetObject(cJSON* Object) {
	if (root!=NULL) {
		cJSON_Delete(root);
	}
	root = Object;
}

//@ 创建对象
cJSON* cJSONH::CreateObject() {
	return cJSON_CreateObject();
}

//@ 创建数组对象
cJSON* cJSONH::CreateArray() {
	return cJSON_CreateArray();
}

//@ 创建空对象
cJSON* cJSONH::CreateNull() {
	return cJSON_CreateNull();
}

//@ 创建逻辑对象
cJSON* cJSONH::CreateBool(bool boolean) {
	return cJSON_CreateBool(boolean);
}

//@ 创建文本对象
cJSON* cJSONH::CreateString(const char* string) {
	return cJSON_CreateString(string);
}

//@ 创建数值对象
cJSON* cJSONH::CreateNumber(double num) {
	return cJSON_CreateNumber(num);
}

//@ 取Json数据文本
char* cJSONH::GetJsonforString(bool formatted) {
	if (formatted) {
		return cJSON_Print(root);
	}
	else {
		return cJSON_PrintUnformatted(root);
	}
}

//@ 取类型
int cJSONH::GetItemType(const char* path){
	cJSON* ltp = PathParsed(root, path);
	if (ltp==NULL) {
		return 0;
	}
	return ltp->type;
}

//@ 取父级
cJSON* cJSONH::GetParent(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return 0;
	}
	return ltp->prev;
}

//@ 取成员数
int cJSONH::GetArraySize(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return 0;
	}
	return cJSON_GetArraySize(ltp);
}

//@ 取文本数据
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

//@ 由路径取对应节点
cJSON* cJSONH::PathParsed(cJSON* root, const char* path) {
	std::string stpath = path;
	if (path==NULL) {
		return NULL;
	}
	size_t StrLen			///< 路径长度
		= stpath.length();
	if (StrLen==0) {
		return NULL;
	}
	
	size_t OldSubscript		///< 上一个标记点位置
		= 0;
	size_t pos		///< 标记点当前位置
		= 0;
	bool inArray=false;		///< 上一个标记点是否是数组头 [
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
		else if (wchar == '.' || pos == StrLen)	//.或者结尾
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


