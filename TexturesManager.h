#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H

#include <QHash>
#include <QOpenGLTexture>

class TexturesManager
{
public:
    TexturesManager();
    static QOpenGLTexture* getTexture(QString name);

private:

};

static QHash<QString, QOpenGLTexture*> TableTextures;

#endif // TEXTURESMANAGER_H
