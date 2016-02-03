#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "TexturedModel.h"

#define SIZE_MAP 64

class ChunkManager
{
public:
    ChunkManager();

    TexturedModel *getChunk(int x, int y);

    QList<TexturedModel*> getChunksNearby(float x, float y, float radius);
private:
    TexturedModel *chunks[SIZE_MAP][SIZE_MAP];
};

#endif // CHUNKMANAGER_H
