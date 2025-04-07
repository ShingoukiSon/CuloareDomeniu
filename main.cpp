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

void get(Queue &q)
{
    Element *p=new Element;
    p=q.head;
    q.head=q.head->succ;
    delete p;
    if(q.head==0)
        q.tail=0;
    
}
Atom front(Queue q)
{
        return q.head->data;
}
void Coloreaza(Pozitie pi, CImg<unsigned char> &imgOut) 
{
    imgOut(pi.x,pi.y)=0;
}

CImg<unsigned char> ColoreazaDomeniu(CImg<unsigned char>& in, Pozitie init, unsigned char color, CImgDisplay& dispOut, Queue c) {
    CImg<unsigned char> imgOut = in; // imgOut este o copie a lui in

    //dimensiunile imaginii
    int width = in.width();
    int height = in.height();

    unsigned char culoareDomeniu = in(init.x, init.y); // obtinem valoarea pixelului de la pozitia initiala
    cout << "Color: " << (unsigned int)culoareDomeniu << " (" << init.x << ", " << init.y << ")" << endl;
    initD(c);
    put(c,init);
    Coloreaza(init,imgOut);
    Pozitie p,pi;
    while(!isEmpty(c))
    {
        p=front(c);
        get(c);
        for (int d = 0; d < 4; ++d) 
        {
            pi.x = p.x + directii[d].x;
            pi.y = p.y + directii[d].y;
        
            if (pi.x >= 0 && pi.x < width && pi.y >= 0 && pi.y < height && imgOut(pi.x, pi.y) == culoareDomeniu) 
            {
                put(c, pi);
                Coloreaza(pi, imgOut);
                /*dispOut = CImgDisplay(imgOut, "Output");
                 while (!dispOut.is_closed()) {
                    dispOut.wait();
                        }*/
            }
        }
        
    }
    cout << "DONE!" << endl;
    return imgOut;
}


int main() {
    CImg<unsigned char> imgIn("C:\\Users\\SebyP\\Desktop\\Faculta\\Anul 1\\Sem2\\Structuri de date\\Colorare\\img.bmp"); // Incarca imaginea, de specificat calea completa

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
