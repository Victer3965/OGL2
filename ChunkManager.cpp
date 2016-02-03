#include <math.h>

#include "ChunkManager.h" 
#include "terrain.h"

ChunkManager::ChunkManager()
{
    memset(chunks, 0, sizeof(chunks));
}

TexturedModel *ChunkManager::getChunk(int x, int y)
{
    if (x<0 || y<0 || x>SIZE_MAP-1 || y>SIZE_MAP-1)
        return 0;

    if (chunks[x][y] != 0)
        return chunks[x][y];
    chunks[x][y] = new TexturedModel(Terrain::generateTerrain(), ":/res/terrain/gravel.dds");
    chunks[x][y]->MoveModel(x*Terrain::sizeX, y*Terrain::sizeY);
    return chunks[x][y];
}

QList<TexturedModel*> ChunkManager::getChunksNearby(float x, float y, float radius)
{
    QList<TexturedModel*> result;
    for (float i = -radius; i<=radius; i+=Terrain::sizeX)
    {
        float a = acosf(i/radius);
        float t = radius * sinf(a);
        for (float j = t; j>=-t; j-=Terrain::sizeY )
        {
            float posChunkX = (x+i)/Terrain::sizeX;
            float posChunkY = (y+j)/Terrain::sizeY;
            TexturedModel* chunk = getChunk(posChunkX, posChunkY);
            if (chunk)
            {
                result.append(chunk);
            }
        }
    }

    return result;
}


