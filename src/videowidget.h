#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
#include <QMainWindow>
#include"QtWidgets/qwidget.h"
#include"QOpenGLWidget"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QPainter>
#include <QInputDialog>
#include <QGridLayout>
#include "protocol.h"
#include "netcom.h"
#include "CGlobalDate.h"

class Videowidget:public QOpenGLWidget,protected QOpenGLFunctions
{
   // Q_OBJECT

public:
    Videowidget(QWidget *p=NULL);
    virtual ~Videowidget();
    static CGlobalDate* m_GlobalDate4;
    float x, x1, y, y1;
    int x2,y2;
    float r_x, r_x1, r_y, r_y1;
    int r_x2,r_y2;

private slots:
    void slotssendprotocol(Protocol::PROTOCOL protocol);
protected:
    void mousePressEvent(QMouseEvent *event);        //单击
    void mouseReleaseEvent(QMouseEvent *event);      //释放
    void wheelEvent(QWheelEvent *event);             //滑轮

protected:

    void paintGL();

    void initializeGL();


    void resizeGL(int width, int height);
public:
    Netcom net;
    void SetOneFrame(QImage img);
private:
    QOpenGLShaderProgram program;
    GLuint unis[3] = {0};
    GLuint texs[3] = { 0 };


    unsigned char *datas[3] = { 0 };
    unsigned pp=0;
    int width = 1920;
    int height = 1080;
};

#endif // VIDEOWIDGET_H
