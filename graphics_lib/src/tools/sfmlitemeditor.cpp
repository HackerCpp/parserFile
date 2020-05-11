#include "sfmlitemeditor.h"
#include <QDebug>
#include <icurve.h>
#include "acuItem.h"

SFMLItemEditor::SFMLItemEditor(QWidget* Parent, const QPoint& Position, const QSize& Size) :
QSFMLCanvas(Parent, Position, Size)
{
    m_graphicItem = nullptr;

}

void SFMLItemEditor::OnInit()
{
    setMinimumSize(200,200);
    float w = static_cast<float>(this->size().width());
    float h = static_cast<float>(this->size().height());
    setView(View(Vector2f(w/2, h/2),Vector2f(w, h)));
    setSize(Vector2u(this->size().width(),this->size().height()));
    m_shape.setRadius(100);
    m_shape.setPosition(60,60);
    m_shape.setFillColor(Color(0xff,0x0,0x0,200));
    m_rectangle = new RectangleShape(Vector2f(20,20));
    m_rectangle->setPosition(0,0);
    m_rectangle->setFillColor(Color(0x1f,0x1f,0x1f,200));
}

void SFMLItemEditor::OnUpdate(){
    clear(Color(255,255,255,255));
    for(int i = 0;i < this->size().width();i += 25){
        RectangleShape shape(Vector2f(1,this->size().height() + 20));
        shape.setPosition(i,-10);
        shape.setFillColor(Color(0,0,0,255));
        shape.setOutlineThickness(1);
        draw(shape);
    }
    for(int i = 0;i < this->size().height();i += 25){
        RectangleShape shape(Vector2f(this->size().width() + 20,1));
        shape.setPosition(-10,i);
        shape.setFillColor(Color(0,0,0,255));
        draw(shape);
    }
    ICurve *f_curve = m_graphicItem->curve();
    QVector<Vertex> *f_vector = new QVector<Vertex>;
    /*int offset = f_curve->sizeOffset();
    AcuItem *f_AcuItemInfo = dynamic_cast<AcuItem*>(m_graphicItem->itemInfo());
    QList<MulticolorItem> *f_multicolor = f_AcuItemInfo->multiColor();
    MulticolorItem f_multicolorFirst = f_multicolor->first();
    MulticolorItem f_multicolorLast = f_multicolor->last();*/
    Color color;
    /*for(int y = 0;y < f_curve->size() / offset ;++y){
        for(int x = 0; x < offset;x++){
                if(f_curve->data(y * x)  >= f_multicolorLast.bound){
                    color = Color(f_multicolorLast.value.toUInt());
                }
                else if(f_curve->data(y * x) <= f_multicolorFirst.bound){
                    color = Color(f_multicolorFirst.value.toUInt());
                }
                else{
                    MulticolorItem prev_mul;
                    prev_mul = *f_multicolor->begin();
                    foreach(auto value,*f_multicolor){
                        if(f_curve->data(y * x) <= value.bound){
                            //color = get_linear_color(m_curve->data(y * x),prev_mul,value);
                            break;
                        }
                        prev_mul = value;
                    }
                }
            f_vector->push_back(Vertex(Vector2f(x,y*10),color));

        }
        f_vector->push_back(Vertex(Vector2f(offset,y*10 + 5),color));
        f_vector->push_back(Vertex(Vector2f(0,y*10 + 5),color));
         draw(f_vector->data(), f_vector->size(), sf::Quads);
    }*/

    f_vector->push_back(Vertex(Vector2f(0,100),Color(0xff0000ff)));
    f_vector->push_back(Vertex(Vector2f(0,200),Color(0x00ff00ff)));
    //f_vector->push_back(Vertex(Vector2f(0,300),Color(0xff00ffff)));
    //f_vector->push_back(Vertex(Vector2f(0,400),Color(0xffff00ff)));
    f_vector->push_back(Vertex(Vector2f(0,500),Color(0x0000ffff)));
    f_vector->push_back(Vertex(Vector2f(100,500),Color(0x0000ffff)));
    //f_vector->push_back(Vertex(Vector2f(100,400),Color(0x00ff00ff)));
    //f_vector->push_back(Vertex(Vector2f(100,300),Color(0xff00ffff)));
    f_vector->push_back(Vertex(Vector2f(100,200),Color(0x00ff00ff)));
    f_vector->push_back(Vertex(Vector2f(100,100),Color(0xff0000ff)));

    draw(f_vector->data(), f_vector->size(), sf::LinesStrip);
    delete f_vector;





    // Draw it
    draw(*m_rectangle);
}
