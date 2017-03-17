#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>		/* system()����ͷ�ļ� */
//#include <conio.h>	/*getche()��getch() �Ǳ�׼Linuxͷ�ļ�*/

#define FILE_NAME "iotest.txt"

/* �Լ�ʵ��getch��getche(�ο�����) */
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
  vprintf(format, args);		/* ʹ��vprintf��Ҫ��va_list����ʹ��va_start��ʼ�� */
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
    
  puts("Enter a char:");	/* ���ַ����������׼���stdout(��Ļ) */
  c = getche();						/* ����Ҫ�س��� */
  putchar('\n');
  putchar(c);
  putchar('\n');

  puts("Enter a char:");	/* ���ַ����������׼���stdout(��Ļ) */
  c = getch();						/* ����Ҫ�س������������벻����ʾ����Ļ�� */
  putchar(c);
  putchar('\n');
  
  puts("Enter a string:");
  gets(str);					/* �ӱ�׼����stdin(�������)��ȡһ���ַ��� */
  puts(str);					/* ���ַ����������׼���stdout(��Ļ) */
  
  puts("Enter a char again:");	/* ���ַ����������׼���stdout(��Ļ) */
  c = getchar();			/* �ӱ�׼����stdin(�������)��ȡһ���ַ� */
  putchar(c);					/* ���ַ�c�������׼���stdout(��Ļ) */
  putchar('\n'); 

  memset(str, 0, sizeof(str));
  printf("Enter a string:\n");
  scanf("%s", str);			/* �ӱ�׼����stdin(�������)����ָ����ʽ��ȡһ���ַ��� */
  printf("%s\n", str);	/* ���ַ�������ָ����ʽ�������׼���stdout(��Ļ) */
  
  printf("*********************string stream***********************\n");
    
  sprintf(str, "%s %d", str, 5);	/* ���ո�ʽд���ַ��� */
  printf("%s\n", str);
  
  sscanf(str, "%s %d", strNew, &num);	/* ��str���ո�ʽ%s %d��֣��ֱ�д��strNew��num */
  printf("%s %d\n", strNew, num);
  #endif
  
  #ifdef FILE_STREAM
  printf("***********************FILE stream***********************\n");
  
  pFile = fopen(FILE_NAME, "r");
  if (pFile)
  {
  	do
  	{
      c = fgetc (pFile);		/* ���ļ�stream�ж�ȡһ���ַ�����getc()�ȼ� */
      printf("%c", c);
    }while (c != EOF);
  }
  //fclose(pFile);	/* freopen���ȹر�һ�� */
  
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
  	fgets(str, 100, pFile);	/* ��ȡ100���ַ�(�ַ���)���������л����ļ�����ֹ */
  	puts(str);
  }
  
  memset(str, 0, sizeof(str));
  pFile = freopen(FILE_NAME, "a", pFile);
  if (pFile)
  {
  	puts("Enter a string:");
  	fgets(str, 100, stdin);	/* �ӱ�׼����stdin��ȡ100���ַ�(�ַ���) */
  	fputs(str, pFile);
  	fclose(pFile);
  }

  pFile = fopen(FILE_NAME, "rb");
  if (pFile)
  {
  	fseek(pFile, 0, SEEK_END);	/* �����ļ��Ĳ���λ��Ϊ�ļ������ĵط�fsetpos() */
  	lSize = ftell(pFile);				/* ����stream�ĵ�ǰλ��fgetpos() */
  	rewind(pFile);							/* ����position indicatorΪ�ļ���ͷ */
  	
  	buffer = (char*)malloc(lSize*sizeof(char));
  	if (buffer)
  	{
  		fread(buffer, 1, lSize, pFile);	/* ���ļ����ݶ��붯̬�ڴ�buffer�� */
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
  	fwrite(str, sizeof(char), strlen(str), pFile);	/* ���ַ���д���ļ� */
  	fclose(pFile);		
	}
	
	/* fprintf��fputs���ƣ�ֻ�����ǰ��ո�ʽ������ */
	/* fscanf��fgets���ƣ�ֻ�������ո�ʽ�����ļ��ж�ȡ���� */
	#endif
	
	printf("*********************variable argument******************\n");
	writeFormat("call vprintf with %d variable argument\r\n", 1);
	writeFormat("call vprintf with %d variable argument: %s %s\r\n", 3, "hello", "world");
	
	/* vsprintf��vprintf���ƣ�ֻ��д�뵽�ַ�������������һ������(char*) */
	/* vfprintf��vprintf���ƣ�ֻ��д�뵽�ļ�����������һ������(FILE*) */
	
  return 0;
}
