#ifndef MODELBASE_H
#define MODELBASE_H

#include <QHash>
#include "TexturedModel.h"
#include "objloader.h"
#include "ChunkManager.h"

class ModelBase
{
public:
    ModelBase();
    void paint(QOpenGLShaderProgram *shader, float radiusNearby);
    bool isColliding(TexturedModel *model);
    TexturedModel* firstModel();
    TexturedModel* loadModel(QString name, QVector3D rot, QVector3D pos, float scale = 1, QString expandedName = "");
    RawModel* getRawModel(QString name);

private:
    QList<TexturedModel*> models, chanksNearby;
    ChunkManager chunkManager;
    TexturedModel * loadModel(RawModel *modeltank);
    QHash<QString, RawModel*> tableRawModels;

};

#endif // MODELBASE_H
