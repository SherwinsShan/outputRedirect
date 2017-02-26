# outputRedirect
Linux 输出重定向
## 用法 
### 1 创建输出文件
```
outputRedirect testLog = {0};
outputRedirect_Init(&testLog, "test.log", MOED_WR_ONCE);
//MOED_WR_ONCE 创建新的文件（会覆盖存在文件）  
//MODE_WR_APPEND 追加到存在的文件
```
### 2 开始重定向
```
outputRedirect_Start(&testLog);

printf(FONT_COLOR_RED "Test\n" FONT_COLOR_BLACK);
//这个时候printf putc等函数会输出到test.log文件
//其中FONT_COLOR_RED FONT_COLOR_BLACK等是字体颜色宏，参考头文件，用于辅助输出提示

outputRedirect_OriPrintf(FONT_COLOR_RED "Test1\n" FONT_COLOR_BLACK);
//outputRedirect_OriPrintf 函数总会把内容输出到原始的输出源(例如控制台)，不受 outputRedirect_Start 影响
//outputRedirect_FilePrintf 函数总会把内容输出到文件，不受 outputRedirect_Start 影响
//outputRedirect_AllPrintf 函数会把内容同时输出到文件和原始输出源

outputRedirect_Flush(&testLog);//刷新输出缓存，讲输出内容写进硬盘
```

### 3 结束重定向
```
outputRedirect_End(&testLog);//结束重定向，printf等输出恢复
//结束时会强制刷新缓存
```

### 4 关闭输出文件
```
outputRedirect_Close(&testLog);
//关闭时会强制自动结束重定向
``` 

##### 注意，暂时还不支持多线程（可以在多线程下使用全部接口，但是在多线程情况下，printf等输出结果未知， 可以用outputRedirect_OriPrintf、outputRedirect_FilePrintf或outputRedirect_AllPrintf代替）
