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



void Test_All() {
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
	cJSONH json;
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
	cout << "Test_Parsing:" << endl;
	Test_Parsing();
	cout << "Test_All:" << endl;
	Test_All();
	system("pause");
}


