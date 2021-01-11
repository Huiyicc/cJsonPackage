#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <stdlib.h>
#include "cJsonHelp.h"

using namespace std;

//从文件读入到string里
string readFileIntoString(string filename)
{
	ifstream ifile(filename);
	//将文件读入到ostringstream对象buf中
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	//返回与流对象buf关联的字符串
	return buf.str();
}

//原版生成
void create_monitor()
{
	/*
	{
	"name": "Awesome 4K",
	"resolutions": [{
						"width": 1280,
						"height": 720
					},
					{
						"width": 1920,
						"height": 1080
					},
					{
						"width": 3840,
						"height": 2160
					}]
	}
	*/

	const unsigned int resolution_numbers[3][2] = {
		{1280, 720},
		{1920, 1080},
		{3840, 2160}
	};
	char* string = NULL;
	cJSON* name = NULL;
	cJSON* resolutions = NULL;
	cJSON* resolution = NULL;
	cJSON* width = NULL;
	cJSON* height = NULL;
	size_t index = 0;

	cJSON* monitor = cJSON_CreateObject();
	if (monitor == NULL)
	{
		goto end;
	}

	name = cJSON_CreateString("Awesome 4K");
	if (name == NULL)
	{
		goto end;
	}
	/* after creation was successful, immediately add it to the monitor,
	 * thereby transferring ownership of the pointer to it */
	cJSON_AddItemToObject(monitor, "name", name);

	resolutions = cJSON_CreateArray();
	if (resolutions == NULL)
	{
		goto end;
	}
	cJSON_AddItemToObject(monitor, "resolutions", resolutions);

	for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
	{
		resolution = cJSON_CreateObject();
		if (resolution == NULL)
		{
			goto end;
		}
		cJSON_AddItemToArray(resolutions, resolution);

		width = cJSON_CreateNumber(resolution_numbers[index][0]);
		if (width == NULL)
		{
			goto end;
		}
		cJSON_AddItemToObject(resolution, "width", width);

		height = cJSON_CreateNumber(resolution_numbers[index][1]);
		if (height == NULL)
		{
			goto end;
		}
		cJSON_AddItemToObject(resolution, "height", height);
	}

	string = cJSON_Print(monitor);
	if (string == NULL)
	{
		fprintf(stderr, "Failed to print monitor.\n");
	}

end:
	cJSON_Delete(monitor);
	printf("%s\n", string);
	free(string);
}

//封装版生成
void create_monitor_H() {
	/*
	{
	"name": "Awesome 4K",
	"resolutions": [{
						"width": 1280,
						"height": 720
					},
					{
						"width": 1920,
						"height": 1080
					},
					{
						"width": 3840,
						"height": 2160
					}]
	}
	*/
	const unsigned int resolution_numbers[3][2] = {
	{1280, 720},
	{1920, 1080},
	{3840, 2160}
	};
	cJSONH json;
	bool Parsing = json.Create();
	if (!Parsing) {
		cout << "Error:" << json.GetErrorString() << endl;
		return;
	}
	json.SetStringValue("name","Awesome 4K");

	for (int index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index) {
		string indexp= "resolutions["+to_string(index)+"].";
		string path = indexp + "width";
		json.SetNumberValue(path.c_str(), resolution_numbers[index][0]);
		path = indexp + "height";
		json.SetNumberValue(path.c_str(), resolution_numbers[index][1]);
	}
	json.SetStringValue("user.img.msc", "This is a test Object");
	cout << json.GetJsonforString(true) << endl;
	json.Delete();
}

void Test_Read() {
	cJSONH json;
	string jsonstr = readFileIntoString("test.json");
	bool Parsing = json.Parse(jsonstr.c_str());
	if (!Parsing) {
		cout << "Error:" << json.GetErrorString() << endl;
		return;
	}

	printf("=========\nlibraries size:%d\n", json.GetArraySize("libraries"));
	for (int i = 0; i < json.GetArraySize("libraries"); i++) {
		string path = "libraries[" + to_string(i) + "].name";
		json.GetStringValue(path.c_str());
	}

	json.Delete();

}

void Test_Parsing() {
	cJSON* root = cJSON_CreateObject();
	cJSONH json;
	json.SetObject(root);
	/*
	{
	"programmers": [{
		"firstName": "Brett",
		"lastName": "McLaughlin",
		"id": 1
	}, {
		"firstName": "Jason",
		"lastName": "Hunter",
		"id": 2
	}, {
		"firstName": "Elliotte",
		"lastName": "Harold",
		"id": 3
	}]
	}
	*/
	string jsonstr = "{\"programmers\":[{\"firstName\":\"Brett\",\"lastName\":\"McLaughlin\",\"id\":1},{\"firstName\":\"Jason\",\"lastName\":\"Hunter\",\"id\":2},{\"firstName\":\"Elliotte\",\"lastName\":\"Harold\",\"id\":3}]}";
	char* str = (char*)malloc(jsonstr.length() + 1);
	strcpy(str, jsonstr.c_str());
	bool Parsing = json.Parse(str);
	if (!Parsing) {
		cout << json.GetErrorString() << endl;
		free(str);
		return;
	}
	cout << json.GetJsonforString(true) << endl;

	//semantic.slots[0].name[0]
	cout << "programmers[0].firstName:" << json.GetStringValue("programmers[0].firstName") << endl;
	cout << "programmers[3].firstName:" << json.GetStringValue("programmers[3].firstName") << endl;


	json.Delete();
	free(str);
}

int main()
{
	cout << "create_monitor:" << endl;
	create_monitor();
	cout << "create_monitor_H:" << endl;
	create_monitor_H();
	cout << "Test_Parsing:" << endl;
	Test_Parsing();
	cout << "Test_Read:" << endl;
	Test_Read();
	system("pause");
}


