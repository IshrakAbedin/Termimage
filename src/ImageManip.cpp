#include "ImageManip.h"

#include "fmt/core.h"

ImageManip::ImageManip(const char *path)
	: ImageManip(path, 0U)
{
}

ImageManip::ImageManip(const char *path, const unsigned int desiredChannel)
	: m_OWidth(0U), m_OHeight(0U), m_OChannels(0U), m_OImage(nullptr)
{
	m_Image = stbi_load(path, &m_Width, &m_Height, &m_Channels, desiredChannel);
	if (m_Image == nullptr)
	{
		fmt::print("Cannot find/open {0}.\n", path);
		exit(1);
	}
}

ImageManip::~ImageManip()
{
	if (m_Image != nullptr)
		stbi_image_free(m_Image);
	if (m_OImage != nullptr)
		delete[] m_OImage;
}

void ImageManip::ResizeImage(const unsigned int targetWidth, const unsigned int targetHeight, const unsigned int targetChannel)
{
	m_OWidth = targetWidth;
	m_OHeight = targetHeight;
	m_OChannels = targetChannel;
	m_OImage = new unsigned char[m_OWidth * m_OHeight * m_OChannels];
	stbir_resize_uint8(m_Image, m_Width, m_Height, m_Width * 3, m_OImage, m_OWidth, m_OHeight, m_OWidth * 3, m_OChannels);
}

int ImageManip::WriteOutImage(const char *writePath)
{
	return stbi_write_png(writePath, m_OWidth, m_OHeight, m_OChannels, m_OImage, m_OWidth * m_OChannels);
}
