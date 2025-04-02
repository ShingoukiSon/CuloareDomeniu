#include <iostream>
#include "CImg.h"
#include <chrono>
using namespace std;
using namespace cimg_library;
using namespace std::chrono;

struct Pozitie {
    int x, y;
};
typedef Pozitie Atom;
struct Element{
    Atom data;
    Element* succ;
    };
struct Queue {
    Element *head, *tail;
    };

Pozitie directii[4] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };

void initD(Queue &q)
{
    q.head=0;
    q.tail=0;
}

void put(Queue &q, Pozitie init)
{
    Element *p=new Element;
    p->data.x=init.x;
    p->data.y=init.y;
    p->succ=0;
    if(q.tail)
        {
            q.tail->succ=p;
            q.tail=q.tail->succ;
        }
    else
        {
            q.head=p;
            q.tail=p;
        }
}
bool isEmpty(Queue q)
{
    return q.head==0;
}

Atom get(Queue &q)
{
    Element *p=new Element;
    p=q.head;
    q.head=q.head->succ;
    return p->data;
    delete p;
    if(q.head==0)
        q.tail=0;
    
}
CImg<unsigned char> Coloreaza(Pozitie &p) 
{
    p.x;
    p.y;
}

CImg<unsigned char> ColoreazaDomeniu(CImg<unsigned char>& in, Pozitie init, unsigned char color, CImgDisplay& dispOut, Queue c) {
    CImg<unsigned char> imgOut = in; // imgOut este o copie a lui in

    //dimensiunile imaginii
    int width = in.width();
    int height = in.height();

    unsigned char culoareDomeniu = in(init.x, init.y); // obtinem valoarea pixelului de la pozitia initiala
    cout << "Color: " << (unsigned int)culoareDomeniu << "( " << init.x << ", " << init.y << ")" << endl;
    initD(c);
    put(c,init);
    Pozitie p,pi;
    while(!isEmpty(c))
    {
        p:=get(C);

        for (pi := p)
        {
            if(pi=culoareDomeniu && (pi.x >=0 && pi.y>=0) && (pi.x<=in.width() && pi.y<=in.height()))
            {
                put(c,pi);
                Coloreaza(pi);
            }
        }
    }
    cout << "DONE!" << endl;
    return imgOut;
}


int main() {
    CImg<unsigned char> imgIn("C:/Users/SebyP/Desktop/Faculta/Anul 1/Sem2/Structuri de date/Colorare/img.jpg"); // Incarca imaginea, de specificat calea completa

    // Creati o fereastra pentru a vizualiza imaginile
    CImgDisplay dispIn(imgIn, "Input");
    CImgDisplay dispOut;

    Pozitie posInit;
    posInit.x = imgIn.width() / 2;
    posInit.y = imgIn.height() / 2;
    Queue c;

    // imgIn este o imagine grayscale (fiecare pixel este reprezentat de o valoare pe 8 biti, in [0,255])
    CImg<unsigned char> imgOut = ColoreazaDomeniu(imgIn, posInit, (unsigned char)255, dispOut,c);

    // Afisarea imaginilor
    dispOut = CImgDisplay(imgOut, "Output");

    // Asteptam ca utilizatorul sa inchida fereastra
    while (!dispIn.is_closed() && !dispOut.is_closed()) {
        dispIn.wait();
        dispOut.wait();
    }
    return 0;
}
