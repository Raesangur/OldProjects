#include <fstream>


#define BUFFER_MAX_SIZE 256

int main()
{
	std::ifstream inputFile{ "input.txt", std::ios::in | std::ios::binary };
	std::ifstream keyFile{ "key.txt", std::ios::in | std::ios::binary };
	std::ofstream outputFile{ "output.txt", std::ios::out | std::ios::binary };

	static char inputString[BUFFER_MAX_SIZE];
	static char keyString[BUFFER_MAX_SIZE];
	static char outputString[BUFFER_MAX_SIZE];

	inputFile.read(inputString, BUFFER_MAX_SIZE);
	keyFile.read(keyString, BUFFER_MAX_SIZE);

	int i = 0;
	for (; i < BUFFER_MAX_SIZE; i++)
	{
		outputString[i] = inputString[i] ^ keyString[i];

		if (inputString[i] == '\0')
			break;
	}

	outputFile.write(outputString, i);
}