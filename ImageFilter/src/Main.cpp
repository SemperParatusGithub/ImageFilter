#include <stb_image.h>
#include <stb_image_write.h>

#include <functional>
#include <filesystem>

#include "Matrix.h"


unsigned char *FilterData(unsigned char *buffer, int width, int height, const Matrix3f &filter)
{
	struct rgb { unsigned char r, g, b; };
	using rgbPtr = rgb *;

	// allocate memory for two dimensional array
	rgbPtr *data = new rgbPtr[width];
	for (int i = 0; i < width; i++)
		data[i] = new rgb[height];

	// convert buffer to two dimensional array
	int i = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			data[x][y].r = buffer[i + 0];
			data[x][y].g = buffer[i + 1];
			data[x][y].b = buffer[i + 2];

			i += 3;
		}
	}

	// Allocate memory for filtered array
	rgbPtr *filtered = new rgbPtr[width];
	for (int i = 0; i < width; i++)
		filtered[i] = new rgb[height];

	// Write filtered data to filtered array
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Matrix3f matrixR, matrixG, matrixB;
			float sumR = 0, sumG = 0, sumB = 0;

			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					int xIndex = x + i >= width ? width - i : std::abs(x + i);
					int yIndex = y + j >= width ? height - j : std::abs(y + j);

					matrixR(i + 1u, j + 1u) = (float) data[xIndex][yIndex].r;
					matrixG(i + 1u, j + 1u) = (float) data[xIndex][yIndex].g;
					matrixB(i + 1u, j + 1u) = (float) data[xIndex][yIndex].b;
				}
			}

			filtered[x][y] =
			{	(unsigned char) Matrix::ComponentWiseMultiplication(filter, matrixR).GetTotalElementsCount(),
				(unsigned char) Matrix::ComponentWiseMultiplication(filter, matrixG).GetTotalElementsCount(),
				(unsigned char) Matrix::ComponentWiseMultiplication(filter, matrixB).GetTotalElementsCount() };
		}
	}

	// Convert filtered array to one unsigned char buffer
	const std::size_t size = width * height * 3u;
	unsigned char *outputBuffer = new unsigned char[size];
	i = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			outputBuffer[i + 0] = filtered[x][y].r;
			outputBuffer[i + 1] = filtered[x][y].g;
			outputBuffer[i + 2] = filtered[x][y].b;
			i += 3;
		}
	}

	// deallocate no longer used memory
	for (int i = 0; i < width; i++)
	{
		delete[] data[i];
		delete[] filtered[i];
	}

	delete[] data;
	delete[] filtered;

	return outputBuffer;
}
void WriteToFile(unsigned char *data, int width, int height, const std::string &filename)
{
	int success = stbi_write_png(filename.c_str(), width, height, 3, data, width * 3);
	if (success)
		std::cout << "Succesfully wrote to the file: " << filename << std::endl;
	else
		std::cout << "Failed to write to file" << std::endl;
}

const Matrix3f identity {
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f
};
const Matrix3f sharpen {
	 0.0f, -1.0f,  0.0f,
	-1.0f,  5.0f, -1.0f,
	 0.0f, -1.0f,  0.0f
};
const Matrix3f boxBlur {
	1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
	1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
	1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f
};
const Matrix3f gaussianBlur {
	1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
	2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
	1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
};
const Matrix3f edgeDetection {
	-1.0f, -1.0f, -1.0f,
	-1.0f,  8.0f, -1.0f,
	-1.0f, -1.0f, -1.0f
};


int main(int argc, char *argv[])
{
	std::string filepath;

	std::cout << "Filepath: ";
	std::cin >> filepath;

	std::string targetDir;
	if (filepath.find("/") != std::string::npos)
		targetDir = filepath.substr(0, filepath.find_last_of("/")) + "/filtered/";
	
	else 
		targetDir = "filtered/";
	
	std::filesystem::create_directory(targetDir);

	// Load Image
	int width, height, channels;
	stbi_uc *buffer = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb);

	if (!buffer) {
		std::cout << "Failed to load Image" << std::endl;
		stbi_image_free(buffer);
		return EXIT_FAILURE;
	}
	else {
		std::cout << "Successfully loaded image: " << filepath << std::endl;
	}

	unsigned char *filteredIdentity = FilterData(buffer, width, height, identity);
	WriteToFile(filteredIdentity, width, height, targetDir + "Identity.png");

	unsigned char *filteredSharpen = FilterData(buffer, width, height, sharpen);
	WriteToFile(filteredSharpen, width, height, targetDir + "Sharpen.png");

	unsigned char *filteredBoxBlur = FilterData(buffer, width, height, boxBlur);
	WriteToFile(filteredBoxBlur, width, height, targetDir + "BoxBlur.png");

	unsigned char *filteredGaussianBlur = FilterData(buffer, width, height, gaussianBlur);
	WriteToFile(filteredGaussianBlur, width, height, targetDir + "GaussianBlur.png");

	unsigned char *filteredEdgeDetection = FilterData(buffer, width, height, edgeDetection);
	WriteToFile(filteredEdgeDetection, width, height, targetDir + "EdgeDetection.png");

	// Deallocate 
	stbi_image_free(buffer);

	delete[] filteredIdentity;
	delete[] filteredSharpen;
	delete[] filteredBoxBlur;
	delete[] filteredGaussianBlur;
	delete[] filteredEdgeDetection;

	return EXIT_SUCCESS;
}