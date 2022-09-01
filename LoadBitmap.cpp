#include "main.h"

#define BMP_Header_Length 54

GLuint CubeTextureNumbers[AmountOfCubes+1][4];	//�±��1��ԭ���*CubeRules[AmountOfCubes+1]��ԭ��һ��,��ϸ���ܲμ�ReadRules.cpp��

/* ����power_of_two
* ���һ�������Ƿ�Ϊ2�������η�������ǣ�����1�����򷵻�0
* �ڡ��鿴�������λ���ж��ٸ���ʱʹ����һ��С����
* ʹ��n &= (n-1)����ʹ��n�еļ���һ��������ԭ���ҿ����Լ�˼����
*/
bool power_of_two(int n)
{
	if( n <= 0 )
		return false;
	return (n & (n-1)) == 0;
}

/* ����load_texture
* ��ȡһ��BMP�ļ���Ϊ����
* ���ʧ�ܣ�����0������ɹ�������������
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID, texture_ID = 0;

	//���ļ���
	FILE* pFile = fopen(file_name, "rb");
	if( pFile == 0 )
		return load_texture("00001.bmp");	//���ʧ��,����һ����ʧ���ʡ�

	//��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶ȡ�
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	//����ÿ��������ռ�ֽ���,�����ݴ����ݼ����������ֽ�����
	{
		GLint line_bytes = width * 3;
		while( line_bytes % 4 != 0 )
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	//�����������ֽ��������ڴ档
	pixels = (GLubyte*)malloc(total_bytes);
	if( pixels == 0 )
	{
		fclose(pFile);
		return 0;
	}

	//��ȡ�������ݡ�
	if( fread(pixels, total_bytes, 1, pFile) <= 0 )
	{
		cout<<"�����ڴ�ʧ��,�������ڴ治����"<<endl;
		free(pixels);
		fclose(pFile);
		return 0;
	}

	//�ھɰ汾��OpenGL��,
	//���ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�,����Ҫ�������š�
	//���ﲢû�м��OpenGL�汾,���ڶ԰汾�����ԵĿ���,���ɰ汾����
	//����,�����Ǿɰ汾�����°汾,
	//��ͼ��Ŀ�Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ,ҲҪ�������š�
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if( !power_of_two(width)
		|| !power_of_two(height)
		|| width > max
		|| height > max )
		{
			const GLint new_width = 256;
			const GLint new_height = 256;	//�涨���ź��µ������α߳��Ĵ�С��
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			//����ÿ����Ҫ���ֽ��������ֽ�����
			new_line_bytes = new_width * 3;
			while( new_line_bytes % 4 != 0 )
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			//�����ڴ档
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if(new_pixels == 0)				//����ʧ�ܡ�
			{
				cout<<"�����ڴ�ʧ��,�������ڴ治����"<<endl;
				free(pixels);
				fclose(pFile);
				return 0;
			}

			//�����������š�
			gluScaleImage(GL_RGB,
			width, height, GL_UNSIGNED_BYTE, pixels,
			new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			//�ͷ�ԭ������������,��pixelsָ���µ���������,����������width��height��
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	//����һ���µ������š�
	glGenTextures(1, &texture_ID);
	if(texture_ID == 0)
	{
		cout<<"���ز���ʧ�ܡ�"<<endl;
		free(pixels);
		fclose(pFile);
		return 0;
	}

	//���µ�����,���������������������
	// �ڰ�ǰ,�Ȼ��ԭ���󶨵�������,�Ա��������лָ���
	glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	//֮ǰΪpixels������ڴ����ʹ��glTexImage2D�Ժ��ͷ�,
	//��Ϊ��ʱ���������Ѿ���OpenGL���б�����һ��(���ܱ����浽ר�ŵ�ͼ��Ӳ����)��
	free(pixels);
	return texture_ID;
}

void LoadAllCubeTextures(void)	//�������з������
{
	char TextureFileName[9] = "0000.bmp";

	for(CubeID CubeNumber = 1;CubeNumber <= AmountOfCubes;CubeNumber++)
	{
		TextureFileName[0] = '0'+CubeNumber/100;	//ȡ��Ű�λ��(�ļ������Ƿ����ʮ���Ʊ��)
		TextureFileName[1] = '0'+(CubeNumber/10)%10;//ȡʮλ��
		TextureFileName[2] = '0'+CubeNumber%10;		//ȡ��λ��
		if((*CubeRules[CubeNumber]).SurfacesAllTheSame = 1)						//��������治��һ��,��ô��Ҫ���ظ������ʡ�
		{
			CubeTextureNumbers[CubeNumber][0] = load_texture(TextureFileName);	//���ض�����ʡ�
			TextureFileName[3] ++;
			CubeTextureNumbers[CubeNumber][1] = load_texture(TextureFileName);	//���ز�����ʡ�
			TextureFileName[3] ++;
			CubeTextureNumbers[CubeNumber][2] = load_texture(TextureFileName);	//������һ������Ĳ��ʡ�
			TextureFileName[3] ++;
			CubeTextureNumbers[CubeNumber][3] = load_texture(TextureFileName);	//���ص�����ʡ�
			TextureFileName[3] = '0';
		}
		else																	//��Ȼֻ��Ҫ����һ���档
			CubeTextureNumbers[CubeNumber][0] = load_texture(TextureFileName);	//���ز��ʡ�
	}

	return;
}