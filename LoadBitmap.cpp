#include "main.h"

#define BMP_Header_Length 54

GLuint CubeTextureNumbers[AmountOfCubes+1][4];	//下标加1的原因和*CubeRules[AmountOfCubes+1]的原因一样,详细介绍参见ReadRules.cpp。

/* 函数power_of_two
* 检查一个整数是否为2的整数次方，如果是，返回1，否则返回0
* 在“查看其二进制位中有多少个”时使用了一个小技巧
* 使用n &= (n-1)可以使得n中的减少一个（具体原理大家可以自己思考）
*/
bool power_of_two(int n)
{
	if( n <= 0 )
		return false;
	return (n & (n-1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID, texture_ID = 0;

	//打开文件。
	FILE* pFile = fopen(file_name, "rb");
	if( pFile == 0 )
		return load_texture("00001.bmp");	//如果失败,加载一个丢失材质。

	//读取文件中图象的宽度和高度。
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	//计算每行像素所占字节数,并根据此数据计算总像素字节数。
	{
		GLint line_bytes = width * 3;
		while( line_bytes % 4 != 0 )
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	//根据总像素字节数分配内存。
	pixels = (GLubyte*)malloc(total_bytes);
	if( pixels == 0 )
	{
		fclose(pFile);
		return 0;
	}

	//读取像素数据。
	if( fread(pixels, total_bytes, 1, pFile) <= 0 )
	{
		cout<<"分配内存失败,可能是内存不够。"<<endl;
		free(pixels);
		fclose(pFile);
		return 0;
	}

	//在旧版本的OpenGL中,
	//如果图象的宽度和高度不是的整数次方,则需要进行缩放。
	//这里并没有检查OpenGL版本,出于对版本兼容性的考虑,按旧版本处理。
	//另外,无论是旧版本还是新版本,
	//当图象的宽度和高度超过当前OpenGL实现所支持的最大值时,也要进行缩放。
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if( !power_of_two(width)
		|| !power_of_two(height)
		|| width > max
		|| height > max )
		{
			const GLint new_width = 256;
			const GLint new_height = 256;	//规定缩放后新的正方形边长的大小。
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			//计算每行需要的字节数和总字节数。
			new_line_bytes = new_width * 3;
			while( new_line_bytes % 4 != 0 )
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			//分配内存。
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if(new_pixels == 0)				//分配失败。
			{
				cout<<"分配内存失败,可能是内存不够。"<<endl;
				free(pixels);
				fclose(pFile);
				return 0;
			}

			//进行像素缩放。
			gluScaleImage(GL_RGB,
			width, height, GL_UNSIGNED_BYTE, pixels,
			new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			//释放原来的像素数据,把pixels指向新的像素数据,并重新设置width和height。
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	//分配一个新的纹理编号。
	glGenTextures(1, &texture_ID);
	if(texture_ID == 0)
	{
		cout<<"加载材质失败。"<<endl;
		free(pixels);
		fclose(pFile);
		return 0;
	}

	//绑定新的纹理,载入纹理并设置纹理参数。
	// 在绑定前,先获得原来绑定的纹理编号,以便在最后进行恢复。
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

	//之前为pixels分配的内存可在使用glTexImage2D以后释放,
	//因为此时像素数据已经被OpenGL另行保存了一份(可能被保存到专门的图形硬件中)。
	free(pixels);
	return texture_ID;
}

void LoadAllCubeTextures(void)	//加载所有方块材质
{
	char TextureFileName[9] = "0000.bmp";

	for(CubeID CubeNumber = 1;CubeNumber <= AmountOfCubes;CubeNumber++)
	{
		TextureFileName[0] = '0'+CubeNumber/100;	//取编号百位。(文件名都是方块的十进制编号)
		TextureFileName[1] = '0'+(CubeNumber/10)%10;//取十位。
		TextureFileName[2] = '0'+CubeNumber%10;		//取个位。
		if((*CubeRules[CubeNumber]).SurfacesAllTheSame = 1)						//如果六个面不都一样,那么需要加载各个材质。
		{
			CubeTextureNumbers[CubeNumber][0] = load_texture(TextureFileName);	//加载顶面材质。
			TextureFileName[3] ++;
			CubeTextureNumbers[CubeNumber][1] = load_texture(TextureFileName);	//加载侧面材质。
			TextureFileName[3] ++;
			CubeTextureNumbers[CubeNumber][2] = load_texture(TextureFileName);	//加载另一个侧面的材质。
			TextureFileName[3] ++;
			CubeTextureNumbers[CubeNumber][3] = load_texture(TextureFileName);	//加载底面材质。
			TextureFileName[3] = '0';
		}
		else																	//不然只需要加载一个面。
			CubeTextureNumbers[CubeNumber][0] = load_texture(TextureFileName);	//加载材质。
	}

	return;
}