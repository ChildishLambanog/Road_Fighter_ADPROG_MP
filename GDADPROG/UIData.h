#pragma once
#include <unordered_map>
#include <string>
#include "UIButton.h"
#include "UIText.h"

typedef std::unordered_map<std::string, int> IntTable;
typedef std::unordered_map<std::string, float> floatTable;

typedef std::unordered_map<std::string, UIButton*> ButtonTable;
typedef std::unordered_map<std::string, UIText*> TextTable;
using namespace std;



class UIData
{
public:
	~UIData();
	void putInt(string key, int value);
	void putFloat(string key, float value);
	int getInt(string key,int defaultVal);
	float getFloat(string key, float defaultVal);

	void bindUIText( UIText* text);
	void refreshTextFromData(string objName, string key, string preix = "");

private:
	IntTable intTable;
	floatTable floatTable;
	

	// Texts that are bound to the data
	TextTable textTable;

};

