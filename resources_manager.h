#pragma once
#include"atlas.h"
#include<string>
#include<graphics.h>
#include<unordered_map>
using namespace std;
class ResourcesManager
{
public:
	static ResourcesManager* Instance();

	void Load();

	Atlas* FindAtlas(const string& id);
	IMAGE* FindImage(const string& id);

private:
	static ResourcesManager* instance;

	unordered_map<string, Atlas*> atlasPool;
	unordered_map<string, IMAGE*> imagePool;

private:
	ResourcesManager();
	~ResourcesManager();

	void FlipImage(IMAGE* srcImage, IMAGE* dstImage, int num = 1);
	void FlipImage(const string& srcId, const  string& dstId, int num = 1);
	void FlipAtlas(const string& srcId, const  string& dstId);
};