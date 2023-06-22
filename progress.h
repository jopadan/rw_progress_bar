#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width, char filled, char empty);
size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width, char filled, char empty);

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width, char filled, char empty)
{
	/* read status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;
	/* initialize empty progress bar */
	char bar[width];
	memset(bar, empty, width);
	bar[width] = '\0';

	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* read from stream in buffered block mode */
		const size_t len = MIN(size - transfered, block_size);
		if((res = fread((unsigned char*)ptr + transfered, 1, len, stream)) == 0)
			break;

		size_t fill_last = progress * width / 100;
		/* increment progress */
		transfered += res;
		progress = (unsigned char)(transfered * 100 / size);
		size_t fill_now = progress * width / 100;
		memset(bar + fill_last, '=', fill_now - fill_last);
		memset(bar + fill_now, ' ', width - fill_now);
		bar[width] = '\0';

		/* read status progress bar output */
		printf("\r%40s: [%.*s%.03hhu%%%s] %13zu %c", filename, 
		                               (int)fill_now, bar, progress,
		                                 bar + fill_now, transfered,
		                 rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}

size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width, char filled, char empty)
{
	/* write status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;
	/* initialize empty progress bar */
	char bar[width];
	memset(bar, empty, width);
	bar[width] = '\0';

	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* read from stream in buffered block mode */
		const size_t len = MIN(size - transfered, block_size);
		if((res = fwrite((unsigned char*)ptr + transfered, 1, len, stream)) == 0)
			break;

		size_t fill_last = progress * width / 100;
		/* increment progress */
		transfered += res;
		progress = (unsigned char)(transfered * 100 / size);
		size_t fill_now = progress * width / 100;
		memset(bar + fill_last, '=', fill_now - fill_last);
		memset(bar + fill_now, ' ', width - fill_now);
		bar[width] = '\0';

		/* read status progress bar output */
		printf("\r%40s: [%.*s%.03hhu%%%s] %13zu %c", filename, 
		                         (int)fill_now, bar, progress,
		                           bar + fill_now, transfered,
		           rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}

