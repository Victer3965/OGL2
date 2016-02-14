#include "Config.h"
Config config;
Config::Config()
{
    simpleCollision = true;
}

bool Config::getSimpleCollision() const
{
    return simpleCollision;
}
