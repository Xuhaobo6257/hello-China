#ifndef WATCH_H
#define WATCH_H
#include <cmath>
#include <GL/freeglut.h>
#include <ctime>
#include <string>
#define PI 3.14159265358979323846
#define MAX_CHAR 128


class Vec {
private:
    float x, y;
public:
    Vec(float _x, float _y) {
        x = _x;
        y = _y;
    }

    float getX() { return x; }

    float getY() { return y; }

    void setX(float a) { x = a; }

    void setY(float a) { y = a; }

    Vec operator+(Vec v) {
        return Vec(x + v.getX(), y + v.getY());
    }

    Vec operator-(Vec v) {
        return Vec(x - v.getX(), y - v.getY());
    }

    Vec operator*(float k) {
        return Vec(x * k, y * k);
    }

    Vec operator<<(double A) {
        return Vec(x * cos(A) - y * sin(A), x * sin(A) + y * cos(A));
    }

    Vec operator>>(double A) {
        return Vec(x * cos(-A) - y * sin(-A), x * sin(-A) + y * cos(-A));
    }
};


typedef struct color_t {
    float r, g, b;
} color;


class Rec {
public:

    Rec(Vec v0, Vec _p1);

    void blackcolor();

    void bluecolor();

    float getr() { return color1.r; }

    float getg() { return color1.g; }

    float getb() { return color1.b; }

    void draw();

    Vec getanchor() { return anchor; }

    //void rotate(double angle) override;

    //void zoom(double k) override;

private:
    Vec p1 = Vec(0, 0);

    Vec anchor = Vec(0, 0);

    color color1 = {0,0,0};
};


class Timer
{
	private:
		long start_time;
		long pause_time;
		//两个bool值标记四种状态 
		bool is_pause; //记录计时器的状态 （是否处于暂停状态）
		bool is_refresh;//是否处于停止状态 
	public:
		Timer();
		bool isPause(); //返回计时器状态 
		bool isrefresh();
		//计时器的三种动作（功能） 
		void Start(); 
		void Pause();
		void refresh();
		inline long getStartTime() {return start_time;}
		void show();
};

void selectFont(int size, int charset, const char* face);
void drawCNString(const char* str);
void drawString(const char* str);
#endif