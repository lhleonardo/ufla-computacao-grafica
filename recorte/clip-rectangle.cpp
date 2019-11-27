#include "clip-rectangle.h"
#include <iostream>
#include <cmath>

using namespace std;

ClipRectangle::ClipRectangle (double xmin, double xmax, double ymin, double ymax)
    : mXmin(xmin), mXmax(xmax), mYmin(ymin), mYmax(ymax), mInitialized(true)
{}

void ClipRectangle::Set(double xmin, double xmax, double ymin, double ymax)
{
    mXmin = xmin;
    mXmax = xmax;
    mYmin = ymin;
    mYmax = ymax;
    mInitialized = true;
}

// Retorna um ponteiro para uma linha recem alocada inteiramente dentro da area de recorte
// ou NULL se l for completamente descartada.
// A linha alocada aqui será desalocada na função CleanUp().
Line* ClipRectangle::Clip(const Line& l)
{
    cout << "Area P0: " << classificaArea(l.mP0) << endl;
    cout << "Area P1: " << classificaArea(l.mP1) << endl; 
    if((classificaArea(l.mP0)==0) and (classificaArea(l.mP1)==0)) return new Line(l.mP0,l.mP1);
    else if((classificaArea(l.mP0) & classificaArea(l.mP1)) == 1) return nullptr;
    else{
        int areaP0 = classificaArea(l.mP0);
        int areaP1 = classificaArea(l.mP1);
        return new Line(calculaInterseccao(l,l.mP0,areaP0),calculaInterseccao(l,l.mP1,areaP1));
    }
    
}

int ClipRectangle:: classificaArea(Point p){
    int area = 0b0000;
    if(p.mX > mXmax){
        area = area | 0b0010;
    }
    else if(p.mX < mXmin){
        area = area | 0b0001;
    }
    if(p.mY > mYmax){
        area = area | 0b1000;
    }
    else if(p.mY < mYmin){
        area = area | 0b0100;
    }
    return area;
}

Point ClipRectangle:: calculaInterseccao(const Line& l, Point p, int area){
    Point teste = p;
    if((area & 0b1000) == 0b1000){
        teste.mX = l.mP0.mX + ((l.mP1.mX-l.mP0.mX)*(mYmax-l.mP0.mY))/(l.mP1.mY-l.mP0.mY);
        teste.mY = mYmax;
        if(teste.mX >= mXmin and teste.mX <=mXmax){
            cout << "ENTROU" << endl;
            return teste;
        }
    }
    else if((area & 0b0100)==0b0100){
        teste.mX = l.mP0.mX + ((l.mP1.mX-l.mP0.mX)*(mYmin-l.mP0.mY))/(l.mP1.mY-l.mP0.mY);
        teste.mY = mYmin;
        if(teste.mX >= mXmin and teste.mX <=mXmax){
            cout << "ENTROU" << endl;
            return teste;
        }
    }
     if((area & 0b0010) == 0b0010){
        teste.mY = l.mP0.mY + ((l.mP1.mY - l.mP0.mY)*(mXmax - l.mP0.mX))/(l.mP1.mX-l.mP0.mX);
        teste.mX = mXmax;
        if(teste.mY >= mYmin and teste.mY <=mYmax){
            cout << "ENTROU" << endl;
            return teste;
        }
    }
    else if((area & 0b0001) == 0b0001){
        teste.mY = l.mP0.mY + ((l.mP1.mY - l.mP0.mY)*(mXmin - l.mP0.mX))/(l.mP1.mX-l.mP0.mX);
        teste.mX = mXmin;
        if(teste.mY >= mYmin and teste.mY <=mYmax){
            cout << "ENTROU" << endl;
            return teste;
        }
    }
    else{
        return teste;
    }
}



void ClipRectangle::Read(const string& prompt)
{
    cout << prompt;
    cin >> mXmin >> mXmax >> mYmin >> mYmax;
    if (not mInitialized)
        mInitialized = true;
}

ostream& operator << (ostream& os, const ClipRectangle& r)
{
    return os << "(Clipping Rectangle: " << r.mXmin << ", " << r.mXmax << ", " 
              << r.mYmin << ", " << r.mYmax << ")";
}


