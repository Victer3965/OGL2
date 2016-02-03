#include "TexturesManager.h"


TexturesManager::TexturesManager()
{

}

QOpenGLTexture *TexturesManager::getTexture(QString name)
{
    if (TableTextures.contains(name))
        return TableTextures.take(name);
    QOpenGLTexture* texture = new QOpenGLTexture(QImage(name).mirrored());
    TableTextures.insert(name, texture);
    return texture;
}

