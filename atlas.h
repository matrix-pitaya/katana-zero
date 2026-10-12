#pragma once
#include<vector>
#include<graphics.h>
using namespace std;
class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	void Load(LPCTSTR templatePath, int num)
	{
		imgs.clear();
		imgs.resize(num);

		TCHAR filePath[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(filePath, templatePath, i + 1);
			loadimage(&imgs[i], filePath);
		}
	}
	void clear()
	{
		imgs.clear();
	}
	int GetSize()
	{
		return (int)imgs.size();
	}
	IMAGE* get_image(int idx)
	{
		if (idx < 0 || idx >= imgs.size())
		{
			return nullptr;
		}
		return &imgs[idx];
	}
	void add_image(IMAGE& img)
	{
		imgs.push_back(img);
	}
private:
	vector<IMAGE> imgs;
};