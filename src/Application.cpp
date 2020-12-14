#include "fmt/color.h"

#include "ArgParser.h"
#include "ImageManip.h"

#ifdef _MSC_VER
#include "ConsoleController.h"
#endif

#ifdef _MSC_VER
auto block = fmt::format("{0}", (char)219);
#endif

void printImage(const char *path, const int targetWidth, const double hwratio);

int main(int argc, char **argv)
{
	ArgParser parser(argc, argv);
	auto parsedArgs = parser.ParseArguments();
#ifdef _MSC_VER
	ConsoleController ccont;
	bool isTermOnByDef = ccont.IsVTAlreadyOn();
	if (!isTermOnByDef)
		ccont.EnableVT();
#endif

	printImage(parsedArgs.Path.c_str(), parsedArgs.Width, parsedArgs.Ratio);

#ifdef _MSC_VER
	if (!isTermOnByDef)
		ccont.RestoreDefaults();
#endif
	return 0;
}

void printImage(const char *path, const int targetWidth, const double hwratio)
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
#ifdef _MSC_VER
			fmt::print(fmt::fg(fmt::rgb(r, g, b)), block);
#else
			fmt::print(fmt::fg(fmt::rgb(r, g, b)), "\u2588");
#endif
		}
		fmt::print("\n");
	}
}