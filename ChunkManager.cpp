#include <math.h>

#include "ChunkManager.h" 
#include "terrain.h"

ChunkManager::ChunkManager()
{
    memset(chunks, 0, sizeof(chunks));
//    ChunksThread = new CreateChunksThread(this);
//    ChunksThread->start();
}

TexturedModel *ChunkManager::getChunk(int x, int y)
{
    if (x<0 || y<0 || x>SIZE_MAP-1 || y>SIZE_MAP-1)
        return 0;

    if (chunks[x][y] != 0)
        return chunks[x][y];

//    for (int i = 0; i < coords.size(); i++)
//    {
//        chunkManager->createChunk(coords[i].x, coords[i].y);
//    }
    if (allowChunksCreation)
    {
        chunksCreated++;
        createChunk(x, y);
        return chunks[x][y];
    }
//    addCoords(x, y);
    return 0;
}

QList<TexturedModel*> ChunkManager::getChunksNearby(float x, float y, float radius)
{
    allowChunksCreation = true;
    chunksCreated = 0;
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
            if (chunksCreated > 5)
            {
                allowChunksCreation = false;
            }
        }
    }

    return result;
}

void ChunkManager::createChunk(int x, int y)
{
    chunks[x][y] = new TexturedModel(Terrain::generateTerrain(), ":/res/terrain/gravel.dds");
    chunks[x][y]->MoveModel(x*Terrain::sizeX, y*Terrain::sizeY);
}

void ChunkManager::addCoords(int x, int y)
{
    Coords tempCoords;
    tempCoords.x = x;
    tempCoords.y = y;
    coords.append(tempCoords);
}

