#include "videowidget.h"
#include<QPainter>

#include <QDebug>
#include <QTimer>
#include <math.h>
#include <stdio.h>

#define GET_STR(x) #x
#define A_VER 3
#define T_VER 4

FILE *fp = NULL;
int value;
CGlobalDate* Videowidget::m_GlobalDate4 = 0;

const char *vString = GET_STR(
    attribute vec4 vertexIn;
    attribute vec2 textureIn;
    varying vec2 textureOut;
    void main(void)
    {
        gl_Position = vertexIn;
        textureOut = textureIn;
    }
);


const char *tStringyuv = GET_STR(
    varying vec2 textureOut;
    uniform sampler2D tex_y;
    uniform sampler2D tex_u;
    uniform sampler2D tex_v;
    void main(void)
    {
        vec3 yuv;
        vec3 rgb;
        yuv.x = texture2D(tex_y, textureOut).r;
        yuv.y = texture2D(tex_u, textureOut).r - 0.5;
        yuv.z = texture2D(tex_v, textureOut).r - 0.5;
        rgb = mat3(1.0, 1.0, 1.0,
            0.0, -0.39465, 2.03211,
            1.13983, -0.58060, 0.0) * yuv;
        gl_FragColor = vec4(rgb, 1.0);
    }

);


const char *tString = GET_STR(
        varying vec2 textureOut;
        uniform sampler2D tex_y;
        void main(void)
        {

            vec4 rgb;
            rgb = texture2D(tex_y, textureOut.st);
            gl_FragColor = rgb;
        }

    );
Videowidget::Videowidget(QWidget*p):QOpenGLWidget (p)
{
    //protocol1=new Protocol;
    m_GlobalDate4 = CGlobalDate::Instance();
}

Videowidget::~Videowidget()
{

}

void Videowidget::slotssendprotocol(Protocol::PROTOCOL protocol)
{
    net.sendprotocol(protocol);
}


void Videowidget::initializeGL()
{
    qDebug() << "initializeGL";


    initializeOpenGLFunctions();



    qDebug()<<program.addShaderFromSourceCode(QOpenGLShader::Fragment, tString);

    qDebug() << program.addShaderFromSourceCode(QOpenGLShader::Vertex, vString);

    program.bindAttributeLocation("vertexIn",A_VER);


    program.bindAttributeLocation("textureIn",T_VER);

    qDebug() << "program.link() = " << program.link();

    qDebug() << "program.bind() = " << program.bind();


    static const GLfloat ver[] = {
        -1.0f,-1.0f,
        1.0f,-1.0f,
        -1.0f, 1.0f,
        1.0f,1.0f
    };


    static const GLfloat tex[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };


    glVertexAttribPointer(A_VER, 2, GL_FLOAT, 0, 0, ver);
    glEnableVertexAttribArray(A_VER);

    glVertexAttribPointer(T_VER, 2, GL_FLOAT, 0, 0, tex);
    glEnableVertexAttribArray(T_VER);



    unis[0] = program.uniformLocation("tex_y");
  //  unis[1] = program.uniformLocation("tex_u");
  //  unis[2] = program.uniformLocation("tex_v");


    glGenTextures(3, texs);


    glBindTexture(GL_TEXTURE_2D, texs[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, 0);


    datas[pp] = new unsigned char[width*height*4];
    datas[pp^1] = new unsigned char[width*height*4];//Y

   memset(datas[0],0x80,width*height);
   memset(datas[0]+width*height,0x55,width*height);
   memset(datas[0]+2*(width*height),0x0,width*height);


    QTimer *ti = new QTimer(this);
    connect(ti, SIGNAL(timeout()), this, SLOT(update()));
    ti->start(40);
}


void Videowidget::paintGL()
{


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texs[0]);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, datas[0]);

    glUniform1i(unis[0], 0);


    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
   // qDebug() << "paintGL";
}



void Videowidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    qDebug() << "resizeGL "<<width<<":"<<height;
}

void Videowidget::SetOneFrame(QImage img)
{

    pp=pp^1;

    memcpy(datas[pp],img.bits(),img.width()*img.height()*4);
   // qDebug() << "slotGetOneFrame";

}

void Videowidget::mousePressEvent(QMouseEvent *e)
{

    //qDebug() << e->x() << ":" << e->y();
    //qDebug() << ((e->x())/width)*1920 << ":" << ((e->y())/(height))*1080<<endl;
    // 如果是鼠标左键按下
    x = e->x();
    x1 = geometry().width();
    x = x / x1;
    x2 = (int)(x * 1920);
    y = e->y();
    y1 = geometry().height();
    y = y / y1;
    y2 = (int)(y * 1080);
    m_GlobalDate4->x3 = x2;
    m_GlobalDate4->y3 = y2;
    qDebug() << x2 << ":" << y2;

    if ((e->button() == Qt::LeftButton)&&(value == 0)){
        qDebug() << "left click 0";
        emit slotssendprotocol(Protocol::PANORAMAAUTOLEFTBTNPRESSED);
    }
    else if ((e->button() == Qt::RightButton)&&(value == 0)){
        qDebug() << "right click 0";
        emit slotssendprotocol(Protocol::PANORAMAAUTORIGHTBTNPRESSED);
    }
    else if ((e->button() == Qt::LeftButton)&&(value == 1)){
        qDebug() << "left click1";
        emit slotssendprotocol(Protocol::PTZHANDLEFTPRESSED);
    }
    else if ((e->button() == Qt::RightButton)&&(value == 1)){
        qDebug() << "right click 1";
        emit slotssendprotocol(Protocol::PTZHANDRIGHTPRESSED);
    }
    else if ((e->button() == Qt::LeftButton)&&(value == 2)){
        qDebug() << "left click2";
       emit slotssendprotocol(Protocol::PANORAMAHANDLEFTBTNPRESSED);
    }
    else if ((e->button() == Qt::RightButton)&&(value == 2)){
        qDebug() << "right click2";
        emit slotssendprotocol(Protocol::PANORAMAHANDRIGHTBTNPRESSED);
    }

}

void Videowidget::mouseReleaseEvent(QMouseEvent *e)
{
    r_x = e->x();
    r_x1 = geometry().width();
    r_x = r_x / r_x1;
    r_x2 = (int)(r_x * 1920);
    r_y = e->y();
    r_y1 = geometry().height();
    r_y = r_y / r_y1;
    r_y2 = (int)(r_y * 1080);
    m_GlobalDate4->r_x3 = r_x2;
    m_GlobalDate4->r_y3 = r_y2;
    qDebug() << m_GlobalDate4->r_x3 << ":" << m_GlobalDate4->r_y3;

    if ((e->button() == Qt::LeftButton)&&(value == 0)){
        emit slotssendprotocol(Protocol::PANORAMAAUTOLEFTBTNRELEASED);
    }
    else if ((e->button() == Qt::RightButton)&&(value == 0)){
       // qDebug() << "right click 0";
        emit slotssendprotocol(Protocol::PANORAMAAUTORIGHTBTNRELEASED);
    }
    else if ((e->button() == Qt::LeftButton)&&(value == 1)){
        //qDebug() << "left click1";
        emit slotssendprotocol(Protocol::PTZHANDLEFTRELEASED);
    }
    else if ((e->button() == Qt::RightButton)&&(value == 1)){
       // qDebug() << "right click 1";
        emit slotssendprotocol(Protocol::PTZHANDTIGHTRELEASED);
    }
    else if ((e->button() == Qt::LeftButton)&&(value == 2)){
       // qDebug() << "left click2";
       emit slotssendprotocol(Protocol::PANORAMAHANDLEFTBTNRELEASED);
    }
    else if ((e->button() == Qt::RightButton)&&(value == 2)){
        //qDebug() << "right click2";
        emit slotssendprotocol(Protocol::PANORAMAHANDRIGHTBTNRELEASED);
    }
}


void Videowidget::wheelEvent(QWheelEvent *event)
{//滚轮
    int wheel_val = event->delta();

   //  当滚轮远离使用者时
    if ((wheel_val > 0)&&(value = 0)){
      //qDebug() << "wheel forward: " << wheel_val;
        emit slotssendprotocol(Protocol::PANORAMAAUTOMIN);
    }
    else if((wheel_val < 0)&&(value = 0)){//当滚轮向使用者方向旋转时
    //  qDebug() << "wheel backward: " << wheel_val;
        emit slotssendprotocol(Protocol::PANORAMAAUTOPLUS);
    }
    else if((wheel_val > 0)&&(value = 1)){
      //qDebug() << "wheel forward: " << wheel_val;
        emit slotssendprotocol(Protocol::PTZMIN);
    }
    else if((wheel_val < 0)&&(value = 1)){//当滚轮向使用者方向旋转时
    //  qDebug() << "wheel backward: " << wheel_val;
        emit slotssendprotocol(Protocol::PTZPLUS);
    }
    else if((wheel_val > 0)&&(value = 2)){
      //qDebug() << "wheel forward: " << wheel_val;
        emit slotssendprotocol(Protocol::PANORAMAHANDMIN);
    }
    else if((wheel_val < 0)&&(value = 2)){//当滚轮向使用者方向旋转时
    //  qDebug() << "wheel backward: " << wheel_val;
        emit slotssendprotocol(Protocol::PANORAMAHANDPLUS);
    }
}

