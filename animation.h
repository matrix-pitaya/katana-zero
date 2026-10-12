#pragma once
#include"util.h"
#include"vector2.h"
#include"atlas.h"
#include"timer.h"
#include<vector>
#include<functional>
class Animation
{
public:
	enum class AnchorMode
	{
		Centered,
		BottomCentered
	};
public:
	Animation()
	{
		timer.SetOneShot(false);
		timer.SetOnTimeout([&]()
			{
				frameIndex++;
				if (frameIndex >= frames.size())
				{
					frameIndex = isLoop ? 0 : frames.size() - 1;
					if (!isLoop && onFinished)
					{
						onFinished();
					}
				}
			}
		);
	}
	~Animation() = default;
	
	void Reset()
	{
		timer.Restart();
		frameIndex = 0;
	}
	void set_anchor_mode(AnchorMode mode)
	{
		anchorMode = mode;
	}
	void SetPosition(const Vector2& position)
	{
		this->position.x = position.x;
		this->position.y = position.y;
	}
	void set_loop(bool val)
	{
		isLoop = val;
	}
	void set_interval(float interval)
	{
		timer.SetWaitTime(interval);
	}
	void set_on_finished(function<void()> onFinished)
	{
		this->onFinished = onFinished;
	}
	void add_frame(IMAGE* image,int num)
	{
		int width = image->getwidth();
		int height = image->getheight();
		int widthFrame = width / num;
		for (int i = 0; i < num; i++)
		{
			Rect srcRect;
			srcRect.x = i * widthFrame;
			srcRect.y = 0;
			srcRect.w = widthFrame;
			srcRect.h = height;
			frames.emplace_back(image, srcRect);
		}
	}
	void add_frame(Atlas* atlas)
	{
		for (int i = 0; i < atlas->GetSize(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			Rect srcRect;
			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = image->getwidth();
			srcRect.h = image->getheight();
			frames.emplace_back(image, srcRect);
		}
	}
	void OnUpdata(float delta)
	{
		timer.OnUpdata(delta);
	}
	void OnRender()
	{
		Frame& frame = frames[frameIndex];
		Rect dstRect;
		dstRect.x = (int)position.x - frame.srcRect.w / 2;
		dstRect.y = (anchorMode == AnchorMode::Centered) ? (int)position.y - frame.srcRect.h / 2 : (int)position.y - frame.srcRect.h;
		dstRect.w = frame.srcRect.w;
		dstRect.h = frame.srcRect.h;
		Utility::PutimageEX(frame.image, &dstRect, &frame.srcRect);
	}
private:
	struct Frame
	{
		Rect srcRect;
		IMAGE* image = nullptr;

		Frame(IMAGE* image, Rect& srcRect):image(image), srcRect(srcRect){}

		Frame() = default;
		~Frame() = default;
	};
private:
	Timer timer;
	Vector2 position;
	vector<Frame> frames;
	function<void()> onFinished;
	bool isLoop = true;
	int frameIndex = 0;
	AnchorMode anchorMode = AnchorMode::Centered;
};