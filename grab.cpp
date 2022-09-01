#include "main.h"

/* ����grab
* ���贰�ڿ���ΪWindowWidth���߶�ΪWindowHeight
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

	// �����������ݵ�ʵ�ʳ���
	i = WindowWidth * 3;	// �õ�ÿһ�е��������ݳ���
	while( i%4 != 0 )		// �������ݣ�ֱ��i�ǵı���
		++i;				// �������и�����㷨��
							// �������׷��ֱ�ۣ����ٶ�û��̫��Ҫ��
	PixelDataLength = i * WindowHeight;

	// �����ڴ�ʹ��ļ�
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if( pPixelData == 0 )
	{
		cout<<"�޷���ͼ�������ڴ�ʧ��,�������ڴ治����"<<endl;
		free(pPixelData);
		return;				//ֻ�������ܽ�ͼ,��ֵ���˳���
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
		cout<<"�޷���ͼ�����ܴ�����ͼ�ļ���"<<endl;
		free(pPixelData);
		fclose(pWritingFile);
		return;
	}

	//pWritingFile2 = fopen("grab.txt", "wb");
	//if( pWritingFile2 == 0 )
	//{
	//	cout<<"�޷���ͼ�����ܴ�����ͼ�ļ���"<<endl;
	//	free(pPixelData);
	//	fclose(pWritingFile);
	//	return;
	//}

	// ��ȡ����
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
	//fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	//fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile2);
	//fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// д����������
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// �ͷ��ڴ�͹ر��ļ�
	//fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}