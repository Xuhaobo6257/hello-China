#include "watch.h"
#include <GL/freeglut.h>
#define MAX_CHAR 128
using namespace std;
Rec::Rec(Vec v0, Vec _p1){
    p1 = _p1;
    anchor = v0;
}

void Rec::draw() {
    //glLineWidth(2.5);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2f(getanchor().getX()+p1.getX(), getanchor().getY()+p1.getY());
 
    glColor3f(1, 1, 1);
    glVertex2f(getanchor().getX()-p1.getX(), getanchor().getY()+p1.getY());

    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(getanchor().getX()-p1.getX(), getanchor().getY()-p1.getY());
 
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(getanchor().getX()+p1.getX(), getanchor().getY()-p1.getY());

    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(getr(), getg(), getb());
    glVertex2f(getanchor().getX()+p1.getX(), getanchor().getY()+p1.getY());
 
    //glColor3f(0.7, 0.7, 0.7);
    glVertex2f(getanchor().getX()-p1.getX(), getanchor().getY()+p1.getY());

    glVertex2f(getanchor().getX()-p1.getX(), getanchor().getY()-p1.getY());
 
    //glColor3f(0.7, 0.7, 0.7);
    glVertex2f(getanchor().getX()+p1.getX(), getanchor().getY()-p1.getY());


    glEnd();

    

}

void Rec::blackcolor() {
    color1={0,0,0};
}
void Rec::bluecolor() {
    color1={0.1,0.1,0.8};
}


 
Timer::Timer()
{
	is_pause = false; //初始化计时器状�? 
	is_refresh = true;
}
 
 
bool Timer::isPause()
{	
	if(is_pause)
	return true;
	else
	return false;
}
 
bool Timer::isrefresh()
{
	if(is_refresh)
		return true;
	return false;
} 
 
void Timer::Start() //开�? 
{
	if(is_refresh)
	{
		start_time = time(0);
		is_refresh = false;
	}
	else if(is_pause)
	{
		is_pause = false;
		start_time += time(0)-pause_time; //更新开始时间：用此时的时间 - 暂停时所用的时间 + 上一次开始的时间 = 此时的开始时�? 
	}
}
 
void Timer::Pause() //暂停 
{
	if(is_refresh||is_pause) //如果处于停止/暂停状�?,此动作不做任何处理，直接返回 
		return; 
	else    //否则调制为暂停状�?
	{
		is_pause = true;
		pause_time = time(0); //获取暂停时间 
	}
}
void Timer::refresh()  //停止 
{
	if(is_refresh) //如果正处于停止状态（不是暂停状态），不做任何处�? 
		return ; 
	else if(is_pause) //改变计时器状�? 
	{
		is_pause = false;
		is_refresh = true;
	}
	else if(!is_refresh)
	{
		is_refresh = true;
	} 
}
 
void Timer::show()
{
    long t;
    if (isrefresh())
    {
        t=0;
    }
    else if (isPause())
    {
        t=pause_time-start_time;
    }
    else
    {
        t=time(0)-start_time;
    }
    
    string str,str1,str2,str3;
    if (t/60/60<10)
    {
        str1="0"+to_string(t/60/60);
    }
    else
    {
        str1=to_string(t/60/60);
    }
    if (t/60-(t/60/60)*60<10)
    {
        str2="0"+to_string(t/60-(t/60/60)*60);
    }
    else
    {
        str2=to_string(t/60-(t/60/60)*60);
    }
    if (t%60<10)
    {
        str3="0"+to_string(t%60);
    }
    else
    {
        str3=to_string(t%60);
    }
    str=str1+":"+str2+":"+str3;
    selectFont(48, ANSI_CHARSET, "");
    glColor3f(0.5451f, 0.137255f, 0.137255f);
    glRasterPos2f(0,-0.01);
    drawString(&str[0]);
}
void selectFont(int size, int charset, const char* face)
{
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
    charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void drawCNString(const char* str) {
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    // 计算字符的个�?
    // 如果是双字节字符的（比如中文字符），两个字节才算一个字�?
    // 否则一个字节算一个字�?
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    // 将混合字符转化为宽字�?
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // 逐个输出字符
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // 回收所有临时资�?
    free(wstring);
    glDeleteLists(list, 1);
}
void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) { // 如果是第一次调用，执行初始�?
                        // 为每一个ASCII字符产生一个显示列�?
        isFirstCall = 0;

        // 申请MAX_CHAR个连续的显示列表编号
        lists = glGenLists(MAX_CHAR);

        // 把每个字符的绘制命令都装到对应的显示列表�?
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    // 调用每个字符对应的显示列表，绘制每个字符
    for(; *str!='\0'; ++str)
        glCallList(lists + *str);
}
