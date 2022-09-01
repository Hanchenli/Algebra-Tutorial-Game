#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_

//#define SightTemp (2*sight+1)
#define SightTemp 21

//extern int QueryIDs[(SightTemp^3) * 6];
extern CubeID Chunk1Temp[ChunkSize * ChunkSize * maxZ];
extern CubeID MapTemp[SightTemp][SightTemp][maxZ];

//extern void DrawMap(GLfloat Xposition,GLfloat Yposition,GLfloat Zposition);
extern void DrawMapTemp(void);
extern void DrawChunk(CubeID *ChunkTemp,GLint ChunkiPositionX,GLint ChunkPositionY);

#endif //_DRAWMAP_H_