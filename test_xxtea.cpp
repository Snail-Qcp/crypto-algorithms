#include <iostream>
#include <stdint.h>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "xxtea.h"

#define  DEF_XXTEA_KEY "1234567890"

void test_xxtea(int buffer_size, int times)
{
	uint8_t *buffer = (uint8_t*)malloc(buffer_size);
	if (nullptr == buffer)
	{
		std::cout << "no memory" << std::endl;
		return;
	}

	srand((unsigned int)time(nullptr));

	for (int i = 0; i < buffer_size; ++i)
	{
		buffer[i] = ('a' + rand() % 26);
	}

	size_t out_len = 0;
	auto time_start = std::chrono::steady_clock::now();
	for (int j = 0; j < times; ++j)
	{
		void *out_buffer = xxtea_encrypt(buffer, buffer_size, DEF_XXTEA_KEY, &out_len);
		if (nullptr != out_buffer)
		{
			free(out_buffer);
		}
	}
	auto time_end = std::chrono::steady_clock::now();
	auto _diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
	std:: cout << "buffer size " << buffer_size << ", times " << times << ", use time : " << _diff.count() << " ms" << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "usage : test_xxtea buffer_size times" << std::endl;
	}
	else
	{
		auto buffer_size = atoi(argv[1]);
		auto times = atoi(argv[2]);
		test_xxtea(buffer_size, times);
	}	

	return 0;
}
