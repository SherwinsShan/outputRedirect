
#include "outputRedirect.h"
#include <stdio.h>
#include <sys/stat.h>  


int outputRedirect_Init(outputRedirect* or, const char* filename, const char* mode)
{
	or->pfile = fopen(filename, mode);
	if(or->pfile == NULL)
	{
		return -1;
	}
	or->fd = fileno(or->pfile);
	{//mark
		or->pstdout = stdout;
		or->pstderr = stderr;
	}
	or->max_size	= 0;
	or->ptemp		= or->pfile;
	or->isRedirect 	= false;
	return 0;
}

void outputRedirect_Close(outputRedirect* or)
{
	if(or->isRedirect)
	{
		outputRedirect_End(or);
	}
	fclose(or->pfile);
}

int outputRedirect_Start(outputRedirect* or)
{
	int ret = -1;
	if(!or->isRedirect)
	{
		or->ptemp = stdout;
		stdout = or->pfile;
		or->isRedirect = true;
		ret =  0;
	}
	return ret;
}

void outputRedirect_SetMaxSize(outputRedirect* or, unsigned long maxSize)
{
	or->max_size = maxSize;
}

void outputRedirect_Flush(outputRedirect* or)
{
	struct stat fileStat;
	if(or->pfile != NULL)
		fflush(or->pfile);
	
	if(or->max_size == 0)
		return ;
	

	if(fstat(or->fd, &fileStat) != -1)
	{
		if(fileStat.st_size > or->max_size)
		{
			ftruncate(or->fd, 0);
			fseek(or->pfile, 0, SEEK_SET);
		}
	}
}

int outputRedirect_End(outputRedirect* or)
{
	int ret = -1;

	if(or->isRedirect)
	{
		outputRedirect_Flush(or);
		
		stdout = or->ptemp;
		or->ptemp = or->pfile;
		or->isRedirect = false;
		ret = 0;
	}
	return ret;

}


