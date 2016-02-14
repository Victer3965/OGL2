#ifndef CONFIG_H
#define CONFIG_H


class Config
{
public:
    Config();
    bool getSimpleCollision() const;

private:
    bool simpleCollision;

};
extern Config config;
#endif // CONFIG_H
