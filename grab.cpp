#include "main.h"

/* 函数grab
* 假设窗口宽度为WindowWidth，高度为WindowHeight
*/
#define BMP_Header_Length 54
void grab(void)
{
	//FILE*	pDummyFile;
	FILE*	pWritingFile;
	//FILE*	pWritingFile2;
	GLubyte* pPixelData;
	char   BMP_Header[BMP_Header_Length] = "BM6S     6   (   ?  ?         S                 ";
	GLint	i, j;
	GLint	PixelDataLength;

	// 计算像素数据的实际长度
	i = WindowWidth * 3;	// 得到每一行的像素数据长度
	while( i%4 != 0 )		// 补充数据，直到i是的倍数
		++i;				// 本来还有更快的算法，
							// 但这里仅追求直观，对速度没有太高要求
	PixelDataLength = i * WindowHeight;

	// 分配内存和打开文件
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if( pPixelData == 0 )
	{
		cout<<"无法截图。分配内存失败,可能是内存不够。"<<endl;
		free(pPixelData);
		return;				//只不过不能截图,不值得退出。
	}

	//pDummyFile = fopen("dummy.bmp", "rb");
	//if( pDummyFile == 0 )
	//{
	//	free(pPixelData);
	//	fclose(pDummyFile);
	//	return;

	pWritingFile = fopen("grab.bmp", "wb");
	if( pWritingFile == 0 )
	{
		cout<<"无法截图。不能创建截图文件。"<<endl;
		free(pPixelData);
		fclose(pWritingFile);
		return;
	}

	//pWritingFile2 = fopen("grab.txt", "wb");
	//if( pWritingFile2 == 0 )
	//{
	//	cout<<"无法截图。不能创建截图文件。"<<endl;
	//	free(pPixelData);
	//	fclose(pWritingFile);
	//	return;
	//}

	// 读取像素
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把dummy.bmp的文件头复制为新文件的文件头
	//fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	//fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile2);
	//fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 写入像素数据
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件
	//fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}