#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "TexturedModel.h"

#define SIZE_MAP 64

struct Coords
{
    int x;
    int y;
};

class ChunkManager
{
public:
    ChunkManager();

    TexturedModel *getChunk(int x, int y);

    QList<TexturedModel*> getChunksNearby(float modelx, float modely, float radius);

private:
    TexturedModel *chunks[SIZE_MAP][SIZE_MAP];

    QList<Coords> coords;

    int chunksCreated;

    bool allowChunksCreation;

    void createChunk(int x, int y);

    void addCoords(int x, int y);

};

#endif // CHUNKMANAGER_H
