#include <math.h>

#include "ChunkManager.h" 
#include "Terrain.h"

ChunkManager::ChunkManager()
{
    memset(chunks, 0, sizeof(chunks));
    for (int x = 0; x < SIZE_MAP; x++)
        for (int y = 0; y < SIZE_MAP; y++)
            createChunk(x, y);
}

TexturedModel *ChunkManager::getChunk(int x, int y)
{
    if (x<0 || y<0 || x>SIZE_MAP-1 || y>SIZE_MAP-1)
        return 0;

    if (chunks[x][y] != 0)
        return chunks[x][y];


    if (allowChunksCreation)
    {
        chunksCreated++;
        createChunk(x, y);
        return chunks[x][y];
    }
    return 0;
}

QList<TexturedModel*> ChunkManager::getChunksNearby(float modelx, float modely, float radius)
{
    allowChunksCreation = true;
    chunksCreated = 0;
    QList<TexturedModel*> result;

    int x0 = modelx/Terrain::size;
    int y0 = modely/Terrain::size;
    int r = radius/Terrain::size;

    int x = 0;
    int y = r;
    int d = 3-2*y;;

    while(x <= y)
    {
        TexturedModel* chunk;

        if (x == 0)
        {
            chunk = getChunk(x0, y0);
            if (chunk) result.append(chunk);
        }
        else
        {
            chunk = getChunk(x + x0, x + y0);
            if (chunk) result.append(chunk);

            chunk = getChunk(x + x0, -x + y0);
            if (chunk) result.append(chunk);

            chunk = getChunk(-x + x0, x + y0);
            if (chunk) result.append(chunk);

            chunk = getChunk(-x + x0, -x + y0);
            if (chunk) result.append(chunk);
        }

        for (int i = x+1; i <= y ; i++)
        {
            chunk = getChunk(x + x0, i + y0);
            if (chunk) result.append(chunk);

            chunk = getChunk(x + x0, -i + y0);
            if (chunk) result.append(chunk);

            if (x>0)
            {
                chunk = getChunk(-x + x0, -i + y0);
                if (chunk) result.append(chunk);

                chunk = getChunk(-x + x0, i + y0);
                if (chunk) result.append(chunk);
            }

            chunk = getChunk(i + x0, x + y0);
            if (chunk) result.append(chunk);

            chunk = getChunk(-i + x0, x + y0);
            if (chunk) result.append(chunk);

            if (x>0)
            {
                chunk = getChunk(i + x0, -x + y0);
                if (chunk) result.append(chunk);

                chunk = getChunk(-i + x0, -x + y0);
                if (chunk) result.append(chunk);
            }

        }

        if (chunksCreated > 5)
            allowChunksCreation = false;

        if (d < 0)
        {
            d = d + 4*x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            --y;
        }
        ++x;

    }

    return result;
}

void ChunkManager::createChunk(int x, int y)
{
    chunks[x][y] = new TexturedModel(Terrain::generateTerrain(), "terrain/gravel", false);
    chunks[x][y]->MoveModel(x*Terrain::size, y*Terrain::size);
}

//void ChunkManager::addCoords(int x, int y)
//{
//    Coords tempCoords;
//    tempCoords.x = x;
//    tempCoords.y = y;
//    coords.append(tempCoords);
//}

