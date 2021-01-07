#ifndef cJSONHelp__h
#define cJSONHelp__h

extern "C"
{
#include "cJSON.h"
}

class cJSONH {
private:
	bool IfInitialize = false;	///< 类对象是否已经初始化	
	cJSON* root = NULL;				///< 解析后的根对象指针
	const char* LastError="";	///< 最后错误的文本

	cJSON* PathParsed(cJSON* root, const char* path);
	cJSON* SelectNoCreate(cJSON* root, const char* path);

public:


	/**
	* @简述: 创建一个空的JSON对象 如果已经存在一个旧对象则会清空所有数据
	*
	* @返回 BOOL
	*		-false 创建失败
	*		-true 创建成功
	*/
	bool Create();

	/**
	* @简述: 释放对象
	*/
	void Delete();

	/**
	* @简述: 取对象指针
	*
	* @返回 类内绑定的JSON对象指针
	*/
	cJSON* GetObject();

	/**
	* @简述: 设置对象指针,如果之前存在对象,旧对象会自动释放
	* @参数: void
	*
	* @返回 最后一次的错误信息
	*/
	void SetObject(cJSON* Object);

	/**
	* @简述: 获取最后的错误文本
	*
	* @返回 最后一次的错误信息
	*/
	const char* GetErrorString();

	/**
	* @简述: 创建一个空的cJSON对象	静态方法
	*
	* @返回 创建的对象指针
	*/
	cJSON* CreateObject();

	/**
	* @简述: 创建一个空的cJSON数组对象	静态方法
	*
	* @返回 创建的数组对象指针
	*/
	cJSON* CreateArray();

	/**
	* @简述: 创建一个cJSON NULL 对象	静态方法
	*
	* @返回 创建的对象指针
	*/
	cJSON* CreateNull();

	/**
	* @简述: 创建一个cJSON bool 对象	静态方法
	* @参数: 创建的bool值
	*
	* @返回 创建的对象指针
	*/
	cJSON* CreateBool(bool);

	/**
	* @简述: 创建一个cJSON string 对象	静态方法
	* @参数: 创建的string值
	*
	* @返回 创建的对象指针
	*/
	cJSON* CreateString(const char* string);

	/**
	* @简述: 创建一个cJSON数值对象	静态方法
	* @参数: 创建的数值
	*
	* @返回 创建的对象指针
	*/
	cJSON* CreateNumber(double num);

	/**
	* @简述: 从字节流解析Json,如果之前已经解析过,则会自动释放
	* @参数: JsonStr	[in]		指向json字符串的变量
	*
	* @返回 BOOL
	*		-false 解析失败
	*		-true 解析成功
	*/
	bool Parse(const char* JsonStr);

	/**
	* @简述: 获取转成文本后的Json数据
	* @参数: 是否对返回的信息进行格式化
	*
	* @返回 以文本形式展现的Json数据
	*/
	char* GetJsonforString(bool formatted);

	/**
	* @简述: 获取键值的类型
	* @参数: Path [in]		键值所在路径 例如:root.arr[0].key
	*
	* @返回 类型常量,对应 cJSON_
	*/
	int GetItemType(const char* path);

	/**
	* @简述: 获取父级对象指针
	* @参数: Path [in]		键值所在路径 例如:root.arr[0].key
	*
	* @返回 父级对象的指针
	*/
	cJSON* GetParent(const char* path);

	/**
	* @简述: 获取数组成员数量
	* @参数: Path [in]		键值所在路径 例如:root.arr[0].key
	*
	* @返回 父级对象的指针
	*/
	int GetArraySize(const char* path);

	/**
	* @简述: 获取对应键值的String值
	*			注意:如果对应键值的值类型不为String可能会出现错误
	* @参数: Path [in]		键值所在路径 例如:root.arr[0].key
	*
	* @返回 对应的字符串,失败返回空
	*/
	const char* GetStringValue(const char* Path);


};

#endif