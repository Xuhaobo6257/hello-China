#include <fstream>
#include <iostream>
#include "watch.h"
#define MAX_CHAR 128
using namespace std;
typedef struct _time{
    int y;int mon;int d;
    int h;int m;int s;
}clocktime;
clocktime gettime();

Rec* rec1= new Rec(Vec(-0.25,-0.5),Vec(0.1,0.08));
Rec* rec2= new Rec(Vec(0.25,-0.5),Vec(0.1,0.08));
Rec* rec3= new Rec(Vec(0,-0.5),Vec(0.1,0.08));

int mousex, mousey;
static int num1=0;
static int num2=0;
static int num3=0;
Timer t;
void mousecallback(int a, int b, int c, int d) {
	
    if (mousex<340 && mousex>260 && mousey>568 && mousey<632)
    {
        num1++;
        t.Start();
    }
    if (mousex<540 && mousex>460 && mousey>568 && mousey<632)
    {
        num2++;
        t.Pause();
    }
    if (mousex<440 && mousex>360 && mousey>568 && mousey<632)
    {
        num3++;
        t.refresh();
    }
    //
    if (num1%2==1)
    {
        num1=1;
        rec1->bluecolor();
    }
    else if(num1%2==0)
    {
        num1=0;
        rec1->blackcolor();
    }
    //
    if (num2%2==1)
    {
        num2=1;
        rec2->bluecolor();
    }
    else if(num2%2==0)
    {
        num2=0;
        rec2->blackcolor();
    }
    //
    if (num3%2==1)
    {
        num3=1;
        rec3->bluecolor();
    }
    else if(num3%2==0)
    {
        num3=0;
        rec3->blackcolor();
    }
    
}
void mousemotion(int x, int y) {
	mousex = x;
	mousey = y;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //rec1->bluecolor();
    rec1->draw();
    rec2->draw();
    rec3->draw();

    selectFont(25, GB2312_CHARSET, "楷体_GB2312");
    glColor3f(rec1->getr(), rec1->getg(), rec1->getb());
    glRasterPos2f(-0.31,-0.525);
    drawCNString("开始");

    selectFont(25, GB2312_CHARSET, "楷体_GB2312");
    glColor3f(rec2->getr(), rec2->getg(), rec2->getb());
    glRasterPos2f(0.19,-0.525);
    drawCNString("停止");

    selectFont(25, GB2312_CHARSET, "楷体_GB2312");
    glColor3f(rec3->getr(), rec3->getg(), rec3->getb());
    glRasterPos2f(-0.06,-0.525);
    drawCNString("重置");
    

    selectFont(40, GB2312_CHARSET, "楷体_GB2312");
    glColor3f(0.6f, 0.6f, 0.0f);
    glRasterPos2f(-0.5,0.5);
    drawCNString("现在时间：");   

    selectFont(48, ANSI_CHARSET, "");
    glColor3f(0.5451f, 0.137255f, 0.137255f);
    glRasterPos2f(0,0.495);
    clocktime t0= gettime();

    string str,str1,str2,str3;
    if (t0.h<10)
    {
        str1="0"+to_string(t0.h);
    }
    else
    {
        str1=to_string(t0.h);
    }
    if (t0.m<10)
    {
        str2="0"+to_string(t0.m);
    }
    else
    {
        str2=to_string(t0.m);
    }
    if (t0.s<10)
    {
        str3="0"+to_string(t0.s);
    }
    else
    {
        str3=to_string(t0.s);
    }
    str=str1+":"+str2+":"+str3;
    drawString(&str[0]);

    selectFont(48, ANSI_CHARSET, "");
    glColor3f(0.5451f, 0.137255f, 0.137255f);
    glRasterPos2f(0.2,0.8);
    string str0;
    str0=to_string(t0.y+1900)+"年"+to_string(t0.mon+1)+"月"+to_string(t0.d)+"日";
    drawCNString(&str0[0]);

    selectFont(40, GB2312_CHARSET, "楷体_GB2312");
    glColor3f(0.2784f, 0.2353f, 0.5451f);
    glRasterPos2f(-0.5,0);
    drawCNString("射线时长：");   

	t.show();
    glutSwapBuffers();
    glFlush();
}

void TimeStep(int n) {
    glutTimerFunc(n, TimeStep, n);
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("hello, parkinglot!");
    glutMouseFunc(&mousecallback);
	glutPassiveMotionFunc(&mousemotion);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(&display);
    glutTimerFunc(5, TimeStep,5);
    glutMainLoop();
}

clocktime gettime(){
    clocktime clock;
    struct tm * timeinfo;
    time_t nowtime;
    time(&nowtime);
    timeinfo=localtime(&nowtime);
    clock.y=timeinfo->tm_year;
    clock.mon=timeinfo->tm_mon;
    clock.d=timeinfo->tm_mday;
    clock.h=timeinfo->tm_hour;
    clock.m=timeinfo->tm_min;
    clock.s=timeinfo->tm_sec;
    return clock;
}