#pragma once

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"

class ImageManip 
{
private:
	int m_Width;
	int m_Height;
	int m_Channels;
	unsigned char* m_Image;

	int m_OWidth;
	int m_OHeight;
	int m_OChannels;
	unsigned char* m_OImage;
public:
	ImageManip() = delete;
	ImageManip(const char* path);
	ImageManip(const char* path, int desiredChannel);
	~ImageManip();

	void ResizeImage(int targetWidth, int targetHeight, int targetChannel);
	int WriteOutImage(const char* writePath);

	inline int GetInputWidth() const { return m_Width; }
	inline int GetInputHeight() const { return m_Height; }
	inline int GetInputChannelCount() const { return m_Channels; }

	inline int GetOutputWidth() const { return m_OWidth; }
	inline int GetOutputHeight() const { return m_OHeight; }
	inline int GetOutputChannelCount() const { return m_OChannels; }

	inline unsigned char* GetInputImagePtr() { return m_Image; }
	inline unsigned char* GetOutputImagePtr() { return m_OImage; }
};