#ifndef CURVESHIFTTOOL_H
#define CURVESHIFTTOOL_H
#include <QWidget>
#include <QVBoxLayout>
#include <QPointer>
#include <QPushButton>
#include <QLabel>
#include <QPoint>


class CurveShiftTool : public QWidget
{
    Q_OBJECT
    QPointer<QVBoxLayout> m_mainVLayout;
    QPushButton *m_btnOk;
    QList<QPointF> m_positions;
    QList<QLabel *> m_labels;
    QLabel m_coeffs;
    QVector<qreal> m_vector;
public:
    CurveShiftTool(QWidget* parent = nullptr);
    ~CurveShiftTool();

    void addPosition(qreal position);
    void changePosition(qreal position,int index);
    void clear();

    void calcCoeffPolinom(const QList<QPointF> points, QVector<qreal> &k);
    void calcCoeffLinePolinom(const QList<QPointF> points, QVector<qreal> &k);
    QVector<qreal> coeffs(){return m_vector;}
private slots:
    void btnOk();
signals:
    void apply();
};

#endif // CURVESHIFTTOOL_H
