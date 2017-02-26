#ifndef _OUTPUTREDIRECT_H
#define _OUTPUTREDIRECT_H

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

typedef struct
{
	FILE* pfile;
	FILE* pstdout;
	FILE* pstderr;
	FILE* ptemp;
	bool  isRedirect;
	pthread_mutex_t lock;
}outputRedirect;

#define MOED_WR_ONCE	"w"
#define MODE_WR_APPEND	"a"

#define FONT_COLOR_BLACK		"\33[30m"
#define FONT_COLOR_RED			"\33[31m"
#define FONT_COLOR_GREEN		"\33[32m"
#define FONT_COLOR_YELLOW		"\33[33m"
#define FONT_COLOR_BLUE			"\33[34m"
#define FONT_COLOR_PURPLE		"\33[35m"
#define FONT_COLOR_DARK_GREEN	"\33[36m"
#define FONT_COLOR_WHITE		"\33[37m"


int outputRedirect_Open(outputRedirect* or, const char* filename, const char* mode);//打开重定向文件
void outputRedirect_Close(outputRedirect* or);//关闭重定向文件
int outputRedirect_Start(outputRedirect* or);//开始重定向
void outputRedirect_Flush(outputRedirect* or);//刷新重定向文件
int outputRedirect_End(outputRedirect* or);//结束重定向



//总是输出到原标准输出
#define outputRedirect_OriPrintf(a,format, ...) fprintf((a)->pstdout, (format), ##__VA_ARGS__)

//总是输出到文件
#define outputRedirect_FilePrintf(a,format, ...) fprintf((a)->pfile, (format), ##__VA_ARGS__)


//同时输出原标准输出和重定向文件
#define outputRedirect_AllPrintf(a,format, ...)	{ 	fprintf((a)->pstdout, (format), ##__VA_ARGS__);	\
													fprintf((a)->pfile, (format), ##__VA_ARGS__);	\
												}

#endif
