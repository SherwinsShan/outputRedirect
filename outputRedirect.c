
#include "outputRedirect.h"
#include <stdio.h>



int outputRedirect_Init(outputRedirect* or, const char* filename, const char* mode)
{
	or->pfile = fopen(filename, mode);
	if(or->pfile == NULL)
	{
		return -1;
	}

	{//mark
		or->pstdout = stdout;
		or->pstderr = stderr;
	}
	{
		pthread_mutex_init(&(or->lock), 0);
	}

	or->ptemp = or->pfile;

	or->isRedirect = false;
	return 0;
}

void outputRedirect_Close(outputRedirect* or)
{
	bool temp;

	pthread_mutex_lock(&(or->lock));
	temp = or->isRedirect;
	pthread_mutex_unlock(&(or->lock));

	if(temp)
	{
		outputRedirect_End(or);
	}

	pthread_mutex_destroy(&(or->lock));
	fclose(or->pfile);
}

int outputRedirect_Start(outputRedirect* or)
{
	int ret = -1;
	pthread_mutex_lock(&(or->lock));
	if(!or->isRedirect)
	{
		or->ptemp = stdout;
		stdout = or->pfile;
		or->isRedirect = true;
		ret =  0;
	}
	pthread_mutex_unlock(&(or->lock));
	return ret;
}


void outputRedirect_Flush(outputRedirect* or)
{
	if(or->pfile != NULL)
		fflush(or->pfile);
}

int outputRedirect_End(outputRedirect* or)
{
	int ret = -1;
	pthread_mutex_lock(&(or->lock));
	if(or->isRedirect)
	{
		outputRedirect_Flush(or);
		
		stdout = or->ptemp;
		or->ptemp = or->pfile;
		or->isRedirect = false;
		ret = 0;
	}

	pthread_mutex_unlock(&(or->lock));
	return ret;

}


