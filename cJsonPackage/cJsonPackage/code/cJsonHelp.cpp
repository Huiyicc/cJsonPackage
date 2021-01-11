#include "cJSON.h"
#include "cJsonHelp.h"


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
	if (root==NULL) {
		return NULL;
	}
	else {
		if (formatted) {
			return cJSON_Print(root);
		}
		else {
			return cJSON_PrintUnformatted(root);
		}
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

//@ 分离
cJSON* cJSONH::DetachItem(const char* path, const char* ItemName,bool Case) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return NULL;
	}
	if (Case) {
		return cJSON_DetachItemFromObject(ltp,ItemName);
	}
	else {
		return cJSON_DetachItemFromObjectCaseSensitive(ltp, ItemName);
	}
}

//@ 移除属性
void cJSONH::DeleteItem(const char* path, const char* Item) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp != NULL) {
		cJSON_DeleteItemFromObject(ltp, Item);
	}
}

//@ 移除成员
void cJSONH::DeleteItemFromArray(const char* path, int which) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp != NULL) {
		cJSON_DeleteItemFromArray(ltp, which);
	}
}

//@ 清空
void cJSONH::Clear(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp==NULL) {
		return;
	}
	cJSON_Delete(ltp);
}

//@ 取属性
cJSON* cJSONH::GetAttributes(const char* path) {
	return PathParsed(root, path);
}

//@ 取属性名
const char* cJSONH::GetItemName(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL || ltp->string == NULL) {
		return "";
	}
	return ltp->string;
}

//@ 添加成员
cJSON_bool cJSONH::AddItemToArray(const char* path, cJSON* item) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL || ltp->string == NULL) {
		return false;
	}
	return cJSON_AddItemReferenceToArray(ltp, item);
}

//@ 设置属性
cJSON_bool cJSONH::SetObjectValue(const char* Path, cJSON* Value) {
	if (root == NULL) {
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr(root, bankstr, cJSON_Object, (void*)Value);
}

//@ 取文本数据
const char* cJSONH::GetStringValue(const char* Path) {
	cJSON* ret = PathParsed(root, Path);
	if (ret!=NULL) {
		return ret->valuestring;
	}
	else {
		return "";
	}
	return "";
}

//@ 设置文本数据
cJSON_bool cJSONH::SetStringValue(const char* Path, const char* String) {
	if (root == NULL) {
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr(root, bankstr,cJSON_String,(void*)String);
}

//@ 设置数值数据
cJSON_bool cJSONH::SetNumberValue(const char* Path, double num) {
	if (root == NULL) {
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr(root, bankstr, cJSON_Number, (void*)&num);
}



//						==================
//				==================================
//						==================

//@ 由路径数组设置数据值,不存在的路径会自动创建
bool cJSONH::SetValueOfJsonArr(cJSON* root, std::vector<JSONTYPESTUCT> jsonarr,int type,void* dataaddress) {
	cJSON* ltps = NULL;
	cJSON* cpm = root;
	bool ret = false;
	//取出表达式除了最后一个以外的对象指针
	for (size_t i = 0; i < jsonarr.size() - 1; i++) {
		if (jsonarr[i].Type == cJSON_Object)
		{
			//Object
			ltps = cJSON_GetObjectItem(cpm, jsonarr[i].name);
			if (ltps == NULL)
			{
				ltps = cJSON_CreateObject();
				if (cJSON_AddItemToObject(cpm, jsonarr[i].name, ltps))
				{
					cpm = ltps;
				}
				else {
					return false;
				}
			}
			else {
				cpm = ltps;
			}
		}
		else if (jsonarr[i].Type == cJSON_Array)
		{
			//arr
			ltps = cJSON_GetObjectItem(cpm, jsonarr[i].name);
			if (ltps == NULL) {
				ltps = cJSON_CreateArray();
				ret = cJSON_AddItemToObject (cpm, jsonarr[i].name, ltps);
				if (!ret) {
					return ret;
				}
				
			}
			cpm = ltps;
			int aindex = atoi(jsonarr[i+1].name) + 1;
			int asize = cJSON_GetArraySize(cpm);
			if (asize < aindex) {
				cJSON_bool ift;
				for (int k = asize; k < aindex; k++) {
					ltps = cJSON_CreateObject();
					ift = cJSON_AddItemToArray(cpm, ltps);
					if (!ift) {
						return ift;
					}
					//cpm = ltps;
				}
			}
			cpm = cJSON_GetArrayItem(cpm, aindex - 1);
			free(jsonarr[i].name);
			if (cpm == NULL) {
				return false;
			}
			i++;
		}
		free(jsonarr[i].name);
	}
	//设置或创建上面取出的地址对象
	int sindex = jsonarr.size() - 1;
	ltps = cJSON_GetObjectItem(cpm, jsonarr[sindex].name);
	if (ltps == NULL) {
		//不存在
		if (type == cJSON_String) {
			ltps = cJSON_CreateString((const char*)dataaddress);
			cJSON_AddItemToObject(cpm, jsonarr[sindex].name, ltps);
			//(const char*)dataaddress
			ret = true;
		}
		else if (type == cJSON_Number) {
			ltps = cJSON_CreateNumber(*(double*)dataaddress);
			cJSON_AddItemToObject(cpm, jsonarr[sindex].name, ltps);
			ret = true;
		}
		else if (type == cJSON_Object) {
			ret = cJSON_AddItemToObject(cpm, jsonarr[sindex].name, (cJSON*)dataaddress);
			//cJSON_ReplaceItemInObject(cpm, jsonarr[sindex].name,(cJSON*)dataaddress);
			//cJSON_AddNumberToObject(cpm, jsonarr[sindex].name, *(double*)dataaddress);
		}

	}
	else {
		//存在
		if (type == cJSON_String) {
			std::string fcps = (const char*)dataaddress;
			free(ltps->valuestring);
			ltps->valuestring = (char*)malloc(fcps.length() + 1);
			strcpy(ltps->valuestring, fcps.c_str());
		}
		else if (type == cJSON_Number) {
			ltps->valuedouble = *(double*)dataaddress;
		}
		else if (type == cJSON_Object) {
			ret = cJSON_ReplaceItemInObject(cpm, jsonarr[sindex].name, (cJSON*)dataaddress);
		}
		ret = true;
	}
	free(jsonarr[sindex].name);
	return ret;
}

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

//@ 将路径转为数组
std::vector<JSONTYPESTUCT> cJSONH::PathParsedOrCreate(const char* path) {
	std::string stpath = path;
	std::vector<JSONTYPESTUCT> ret;
	JSONTYPESTUCT le;
	if (path == NULL) {
		return ret;
	}
	size_t StrLen			///< 路径长度
		= stpath.length();
	if (StrLen == 0) {
		return ret;
	}

	size_t OldSubscript		///< 上一个标记点位置
		= 0;
	size_t pos		///< 标记点当前位置
		= 0;
	bool inArray = false;		///< 上一个标记点是否是数组头 [
	bool hasName = false;
	bool hasIndex = true;
	size_t namePos = 0, nameLen, indexPos = 0;

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
				stpath.erase(pos, 1);
				--StrLen;
			}
		}
		else if (wchar == '.' || pos == StrLen)	//.或者结尾
		{
			hasName = namePos < pos;
			if (hasName) {
				nameLen = pos - namePos;
				//printf( ".:%s\n", stpath.substr(namePos, nameLen).c_str());
				le.Type = cJSON_Object;
				int slen = stpath.substr(namePos, nameLen).length()+1;
				le.name = (char*)malloc(slen);
				strcpy (le.name, stpath.substr(namePos, nameLen).c_str());
				ret.push_back(le);
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
				le.Type = cJSON_Array;
				int slen = stpath.substr(namePos, nameLen).length() + 1;
				le.name = (char*)malloc(slen);
				strcpy(le.name, stpath.substr(namePos, nameLen).c_str());
				ret.push_back(le);
			}
			namePos = pos + 1;
		}
		else if (wchar == ']')
		{
			if (hasIndex) {
				nameLen = pos - indexPos;
				//printf("]:%d\n", atoi(stpath.substr(namePos, nameLen).c_str()));
				le.Type = cJSON_Number;
				int slen = stpath.substr(namePos, nameLen).length() + 1;
				le.name = (char*)malloc(slen);
				strcpy(le.name, stpath.substr(namePos, nameLen).c_str());
				ret.push_back(le);
			}
			namePos = pos + 1;
		}
		++pos;
		//OldSubscript = Subscript;

	}
	return ret;
}




