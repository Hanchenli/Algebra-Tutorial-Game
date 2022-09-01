#ifndef _LOADBITMAP_H_
#define _LOADBITMAP_H_

extern GLuint CubeTextureNumbers[AmountOfCubes+1][4];

extern bool power_of_two(int n);
extern GLuint load_texture(const char* file_name);
extern void LoadCubeTexture(CubeID CubeNumber);
extern void LoadAllCubeTextures(void);

#endif //_LOADBITMAP_H_