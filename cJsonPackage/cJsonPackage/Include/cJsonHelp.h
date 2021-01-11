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
	bool IfInitialize = false;	///< 类对象是否已经初始化	
	cJSON* root = NULL;				///< 解析后的根对象指针
	const char* LastError="";	///< 最后错误的文本

	cJSON* PathParsed(cJSON* root, const char* path);
	std::vector<JSONTYPESTUCT> PathParsedOrCreate(const char* path);
	bool SetValueOfJsonArr(cJSON* root, std::vector<JSONTYPESTUCT> jsonarr, int type, void* dataaddress);

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
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	*
	* @返回 类型常量,对应 cJSON_
	*/
	int GetItemType(const char* path);

	/**
	* @简述: 获取父级对象指针
	* @参数: Path [in]		属性在路径 例如:root.arr[0].key
	*
	* @返回 父级对象的指针
	*/
	cJSON* GetParent(const char* path);

	/**
	* @简述: 获取数组成员数量
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	*
	* @返回 父级对象的指针
	*/
	int GetArraySize(const char* path);

	/**
	* @简述: 删除属性
	* @参数: Path [in]		属性所在父路径 例如:root.arr[0]
	* @参数: ItemName [in]	属性名
	* @参数: Case [in]		属性名是否大小写敏感
	*
	* @返回 分离的节点指针
	*/
	cJSON* DetachItem(const char* path, const char* ItemName, bool Case);

	/**
	* @简述: 删除属性
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	* @参数: Item [in]		属性名
	*/
	void DeleteItem(const char* path, const char* Item);

	/**
	* @简述: 删除成员
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	* @参数: which [in]		成员下标
	*/
	void DeleteItemFromArray(const char* path, int which);

	/**
	* @简述: 清空值，包括所有下级属性和成员
	* @参数: Path [in]		父属性路径 例如:root.arr[0]
	*/
	void Clear(const char* path);

	/**
	* @简述: 取对象属性
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	*
	* @返回 指向对应属性的指针
	*/
	cJSON* GetAttributes(const char* path);

	/**
	* @简述: 取自身属性名
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	*
	* @返回 属性名字符串
	*/
	const char* GetItemName(const char* path);

	/**
	* @简述: 添加数组成员
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	* @参数: item [in]		数组成员指针
	* 
	* @返回 bool
	*/
	cJSON_bool AddItemToArray(const char* path, cJSON* item);

	/**
	* @简述: 设置对象属性
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	* @参数: Value [in]		属性指针
	*
	* @返回 bool
	*/
	cJSON_bool SetObjectValue(const char* Path, cJSON* Value);



	/**
	* @简述: 获取对应属性的String值
	* @参数: Path [in]		属性路径 例如:root.arr[0].key
	*
	* @返回 对应的字符串,失败返回空
	*/
	const char* GetStringValue(const char* Path);

	/**
	* @简述: 设置对应键值的文本值
	* @参数: Path [in]		属性路径 例如:root.arr[0].key	不存在会自行创建
	* @参数: String [in]		需要设置的值
	*
	* @返回 bool
	*/
	cJSON_bool SetStringValue(const char* Path, const char* String);

	/**
	* @简述: 设置对应键值的数值
	* @参数: Path [in]		属性路径 例如:root.arr[0].key	不存在会自行创建
	* @参数: num [in]		需要设置的值
	*
	* @返回 bool
	*/
	cJSON_bool SetNumberValue(const char* Path, double num);
};

#endif