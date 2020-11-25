#include <iostream>
#include "fmt/color.h"
#include "ImageManip.h"
#include "ConsoleController.h"

#define ESC "\x1b"
#define CSI "\x1b["

constexpr char block = 219;

void printImage(const char* path, int targetWidth, double hwratio);

int main()
{
	ConsoleController ccont;
	bool isTermOnByDef = ccont.IsVTAlreadyOn();
	if (!isTermOnByDef) ccont.EnableVT();

	printImage("G:\\REPOS\\Termimage\\testimg\\heavy.jpg", 120, 2.2);
	std::cin.get();

	if (!isTermOnByDef) ccont.RestoreDefaults();
	return 0;
}

void printImage(const char* path, int targetWidth, double hwratio)
{
	ImageManip img(path, 3);
	auto w = img.GetInputWidth();
	auto h = img.GetInputHeight();
	auto c = img.GetInputChannelCount();

	auto ratio = (double)h / (double)w;
	auto targetHeight = int((targetWidth * ratio) / hwratio);

	img.ResizeImage(targetWidth, targetHeight, 3);
	auto outputImagePtr = img.GetOutputImagePtr();
	
	// Iterate and print
	for (int i = 0; i < targetHeight; i++)
	{
		for (int j = 0; j < targetWidth; j++)
		{
			auto r = outputImagePtr[i * targetWidth * 3 + j * 3 + 0];
			auto g = outputImagePtr[i * targetWidth * 3 + j * 3 + 1];
			auto b = outputImagePtr[i * targetWidth * 3 + j * 3 + 2];
			fmt::print(fmt::fg(fmt::rgb(r, g, b)), "{0}", block);
		}
		fmt::print("\n");
	}
}