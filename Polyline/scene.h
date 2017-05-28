#ifndef SCENE_H
#define SCENE_H
#include "mainwindow.h"


class Scene : public QGLWidget
{
public:
    Scene();                         //    Linia przedstawiona jako zbiór wektorów
    virtual void dragMoveEvent();
    virtual void underMouse();
    virtual void mouseMoveEvent();
    bool is_drawing();
    void Update();
    void Draw();
    vector<pair<float,float>> lines;
    void CleanScene();




};

#endif // SCENE_H
