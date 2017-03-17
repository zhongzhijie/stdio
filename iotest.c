#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>		/* system()所在头文件 */
//#include <conio.h>	/*getche()和getch() 非标准Linux头文件*/

#define FILE_NAME "iotest.txt"

/* 自己实现getch和getche(参考网上) */
char getch()
{
	char c;
	system("stty -echo");
	system("stty -icanon");
	c=getchar();
	system("stty icanon");
	system("stty echo");
	return c;
}
char getche()
{
	char c;
	system("stty -icanon");
	c=getchar();
	system("stty icanon");
	return c; 
}

void writeFormat(char * format, ...)
{
	va_list args;
	va_start(args, format);
  vprintf(format, args);		/* 使用vprintf需要将va_list参数使用va_start初始化 */
  va_end(args);
}


int main ()
{
  char c;
  char str[256] = {0};
  char strNew[256] = {0};
  int num = 0;
  
  FILE * pFile;
  char *buffer = NULL;
  long lSize = 0;
  
  #ifdef STD_STREAM
  printf("************************std stream***********************\n");
    
  puts("Enter a char:");	/* 将字符串输出到标准输出stdout(屏幕) */
  c = getche();						/* 不需要回车键 */
  putchar('\n');
  putchar(c);
  putchar('\n');

  puts("Enter a char:");	/* 将字符串输出到标准输出stdout(屏幕) */
  c = getch();						/* 不需要回车键，并且输入不会显示在屏幕上 */
  putchar(c);
  putchar('\n');
  
  puts("Enter a string:");
  gets(str);					/* 从标准输入stdin(键盘鼠标)读取一个字符串 */
  puts(str);					/* 将字符串输出到标准输出stdout(屏幕) */
  
  puts("Enter a char again:");	/* 将字符串输出到标准输出stdout(屏幕) */
  c = getchar();			/* 从标准输入stdin(键盘鼠标)读取一个字符 */
  putchar(c);					/* 将字符c输出到标准输出stdout(屏幕) */
  putchar('\n'); 

  memset(str, 0, sizeof(str));
  printf("Enter a string:\n");
  scanf("%s", str);			/* 从标准输入stdin(键盘鼠标)按照指定格式读取一个字符串 */
  printf("%s\n", str);	/* 将字符串按照指定格式输出到标准输出stdout(屏幕) */
  
  printf("*********************string stream***********************\n");
    
  sprintf(str, "%s %d", str, 5);	/* 按照格式写入字符串 */
  printf("%s\n", str);
  
  sscanf(str, "%s %d", strNew, &num);	/* 将str按照格式%s %d拆分，分别写入strNew和num */
  printf("%s %d\n", strNew, num);
  #endif
  
  #ifdef FILE_STREAM
  printf("***********************FILE stream***********************\n");
  
  pFile = fopen(FILE_NAME, "r");
  if (pFile)
  {
  	do
  	{
      c = fgetc (pFile);		/* 从文件stream中读取一个字符，和getc()等价 */
      printf("%c", c);
    }while (c != EOF);
  }
  //fclose(pFile);	/* freopen会先关闭一次 */
  
  pFile = freopen(FILE_NAME, "a", pFile);	/* "a" for append, instead of overwrite */
  if (pFile)
  {
  	fputc('l', pFile);
  	fputc('i', pFile);
  	fputc('n', pFile);
  	fputc('e', pFile);
  	fputc('4', pFile);
  	fputc('\r', pFile);
	}
  
  memset(str, 0, sizeof(str));
  pFile = freopen(FILE_NAME, "r", pFile);
  if (pFile)
  {
  	fgets(str, 100, pFile);	/* 读取100个字符(字符串)，遇到换行或者文件结束止 */
  	puts(str);
  }
  
  memset(str, 0, sizeof(str));
  pFile = freopen(FILE_NAME, "a", pFile);
  if (pFile)
  {
  	puts("Enter a string:");
  	fgets(str, 100, stdin);	/* 从标准输入stdin读取100个字符(字符串) */
  	fputs(str, pFile);
  	fclose(pFile);
  }

  pFile = fopen(FILE_NAME, "rb");
  if (pFile)
  {
  	fseek(pFile, 0, SEEK_END);	/* 设置文件的操作位置为文件结束的地方fsetpos() */
  	lSize = ftell(pFile);				/* 返回stream的当前位置fgetpos() */
  	rewind(pFile);							/* 设置position indicator为文件开头 */
  	
  	buffer = (char*)malloc(lSize*sizeof(char));
  	if (buffer)
  	{
  		fread(buffer, 1, lSize, pFile);	/* 将文件内容读入动态内存buffer中 */
  		printf("file buffer:\n%s\n", buffer);
  		free(buffer);
  	}
  	fclose(pFile);
  }
  
  pFile = fopen(FILE_NAME, "ab");
  memset(str, 0, sizeof(str));
  strcpy(str, "writevalue");
  if (pFile)
  {
  	fwrite(str, sizeof(char), strlen(str), pFile);	/* 将字符串写入文件 */
  	fclose(pFile);		
	}
	
	/* fprintf和fputs类似，只不过是按照格式化输入 */
	/* fscanf和fgets类似，只不过按照格式化从文件中读取数据 */
	#endif
	
	printf("*********************variable argument******************\n");
	writeFormat("call vprintf with %d variable argument\r\n", 1);
	writeFormat("call vprintf with %d variable argument: %s %s\r\n", 3, "hello", "world");
	
	/* vsprintf和vprintf类似，只是写入到字符串流，函数多一个参数(char*) */
	/* vfprintf和vprintf类似，只是写入到文件流，函数多一个参数(FILE*) */
	
  return 0;
}
