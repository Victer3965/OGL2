#include "ModelBase.h"

TexturedModel *ModelBase::loadModel(QString modelName, QString textureName, QVector3D pos, QVector3D rot)
{
    TexturedModel* model = new TexturedModel(getRawModel(modelName), textureName);
    model->RotateModel(rot.x(), rot.y(), rot.z());
    model->MoveModel(pos.x(), pos.y(), pos.z());
    models.append(model);

    return model;
}

RawModel *ModelBase::getRawModel(QString name)
{
    if (tableRawModels.contains(name))
        return tableRawModels.take(name);
    RawModel* rawModel = OBJLoader::Load(name);
    tableRawModels.insert(name, rawModel);
    return rawModel;
}

ModelBase::ModelBase()
{
    loadModel("t-54_wot/T-54", "t-54_wot/T-54.dds", QVector3D(0,0,0.55), QVector3D(0,0,180));
    loadModel("t-54_wot/T-54", "t-54_wot/T-54_crash.dds", QVector3D(50,50,0.55), QVector3D(0,0,90));
    loadModel("box/box", "box/grass.dds", QVector3D(45,25,0), QVector3D(0,0,45));
    loadModel("box/box", "box/grass.dds", QVector3D(45,25,1), QVector3D(0,0,25));


}

void ModelBase::paint(QOpenGLShaderProgram *shader, float radiusNearby)
{
    chanksNearby = chunkManager.getChunksNearby(models[0]->GetPos().x(),
                                                models[0]->GetPos().y(),
                                                radiusNearby);

    for (int i=0; i < chanksNearby.size(); i++)
    {
        chanksNearby[i]->PaintModel(shader);
    }

    for (int i=0; i < models.size(); i++){
        models[i]->PaintModel(shader);
    }
}

bool ModelBase::isColliding(TexturedModel* model)
{
    for (int i = 0; i < models.size(); i++)
    {
        if (model == models[i])
        {
            continue;
        }
        if (model->getBoundingBox()->collision( models[i]->getBoundingBox() ) )
        {
            return true;
        }
    }
    return false;
}
TexturedModel* ModelBase::firstModel()
{
    return models.first();
}
