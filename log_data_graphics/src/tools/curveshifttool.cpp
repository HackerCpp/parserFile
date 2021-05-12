#include "curveshifttool.h"
#include <QDebug>

CurveShiftTool::CurveShiftTool(QWidget* parent )
    : QWidget(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setMinimumSize(200,200);
    m_mainVLayout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_btnOk = new QPushButton(tr("ok"),this);
    m_mainVLayout->addWidget(m_btnOk);
    m_mainVLayout->addWidget(&m_coeffs);
    this->setLayout(m_mainVLayout);
    m_vector.resize(3);

    connect(m_btnOk,&QPushButton::released,this,&CurveShiftTool::btnOk);
}

CurveShiftTool::~CurveShiftTool(){}

void CurveShiftTool::addPosition(qreal position){
    m_positions.push_back(QPointF(position,position));
    QLabel *f_label = new QLabel(QString::number(position) + " : " + QString::number(position));
    m_labels.push_back(f_label);
    m_mainVLayout->addWidget(f_label);
}

void CurveShiftTool::changePosition(qreal position,int index){
    m_positions[index].setY(position);
    qreal f_appr;
    qreal f_x = m_positions[index].x();
    if(m_positions.size() == 1){
        m_vector.resize(1);
        m_vector[0] = m_positions[index].y() - m_positions[index].x();
        f_appr = f_x + m_vector[0];
    }
    else if(m_positions.size() == 2){
        calcCoeffLinePolinom(m_positions,m_vector);
        f_appr = f_x * m_vector[1] + m_vector[0];
    }
    else{
        calcCoeffPolinom(m_positions,m_vector);
        f_appr = (f_x * f_x) * m_vector[2] +
                m_vector[1] * f_x + m_vector[0];
    }
    m_labels[index]->setText(QString::number(m_positions[index].x()) +
                             " : " + QString::number(m_positions[index].y()) +
                             " : " + QString::number(f_appr) +
                             " : " + QString::number(f_appr - m_positions[index].y()));
}

void CurveShiftTool::clear(){
    foreach(auto label,m_labels){
        if(label){delete label;label = nullptr;}
    }
    m_labels.clear();
    m_positions.clear();
}

void CurveShiftTool::calcCoeffPolinom(const QList<QPointF> points, QVector<qreal> &k){
    if(points.size() < 3){
        qDebug() << "Не возможно посчитать коэффициенты, количество точек ниже допустимого.";
        return;
    }
    k.resize(3);
    //' X - измеренное, Y - заданное значение
    uint n = points.size() ;
    qreal A1 = 0, A2 = 0, A3 = 0, A4 = 0, B = 0, C = 0, D = 0;
    foreach(auto point,points){
        A1 += point.x();
        A2 += pow(point.x(),2);
        A3 += pow(point.x(),3);
        A4 += pow(point.x(),4);

        B += point.y();
        C += point.y() * point.x();
        D += point.y() * pow(point.x(), 2);
    }
    double G = 0, E = 0, F = 0, K = 0, M = 0;
    G = A3 - A1 * A2 / n;
    if (G == 0.0000000000000)
        return;
    E = A2 - A1 * A1 / n;
    F = C - A1 * B / n;
    K = (B - A2 * F / G) / n;
    M = (A2 * E / G - A1) / n;
    double k_a = 0, k_b = 0, k_c = 0;

    k_b = (D - A4 * F / G - A2 * K) /( A3 - A4 * E / G + A2 * M);
    k_c = K + M * k_b;
    k_a = (F - E * k_b) / G;

    k[0] = k_c;
    k[1] = k_b;
    k[2] = k_a;
}

void CurveShiftTool::calcCoeffLinePolinom(const QList<QPointF> points, QVector<qreal> &k){
    if(points.size() < 2)
        return;
    k.resize(2);
    qreal k_a = (points[1].y() - points[0].y()) / (points[1].x() - points[0].x());
    qreal k_b = points[0].y() - points[0].x() * k_a;
    k[0] = k_b;
    k[1] = k_a;
}

void CurveShiftTool::btnOk(){
    emit apply();
    this->hide();
}
