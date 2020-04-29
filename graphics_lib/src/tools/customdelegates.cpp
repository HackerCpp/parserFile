#include "customdelegates.h"
#include <QApplication>
#include <QCheckBox>
#include <QPushButton>
#include <QColorDialog>
#include <QDebug>
#include <QPainter>
#include <QComboBox>

CustomDelegates::CustomDelegates(){

}

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    :QStyledItemDelegate (parent)
{

}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    //Cоздаем checkbox editor
    QCheckBox *editor = new QCheckBox(parent);
    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //Установливаем выбрано/не выбрано
    QCheckBox *cb = qobject_cast<QCheckBox *>(editor);
    cb->setChecked(index.data().toBool());
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //Записываем данные в модель
    QCheckBox *cb = static_cast<QCheckBox *>(editor);
    int value = (cb->checkState()==Qt::Checked)? 1 : 0;
    model->setData(index, value, Qt::EditRole);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QStyleOptionButton checkboxstyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

    //Центрирование
    checkboxstyle.rect = option.rect;
    checkboxstyle.rect.setLeft(option.rect.x() +
                               option.rect.width()/2 - checkbox_rect.width()/2);

    editor->setGeometry(checkboxstyle.rect);
}


void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //Получаем данные
    bool data = index.model()->data(index, Qt::DisplayRole).toBool();

    //Создаем стиль CheckBox
    QStyleOptionButton checkboxstyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

    //Центрирование
    checkboxstyle.rect = option.rect;
    checkboxstyle.rect.setLeft(option.rect.x() +
                               option.rect.width()/2 - checkbox_rect.width()/2);
    //Выбрано или не выбрано
    if(data)
        checkboxstyle.state = QStyle::State_On|QStyle::State_Enabled;
    else
        checkboxstyle.state = QStyle::State_Off|QStyle::State_Enabled;

    //Готово! Отображаем!
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxstyle, painter);
}
/****************************************************************************************************/

ColorDelegate::ColorDelegate(QObject *parent){

}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const{
    QRect f_rect = option.rect;
    f_rect.setX(f_rect.x() + 3);
    f_rect.setY(f_rect.y() + 3);
    f_rect.setWidth(f_rect.width() - 6);
    f_rect.setHeight(f_rect.height() - 6);
    painter->setBrush(QBrush(index.data().value<QColor>()));
    painter->drawRect(f_rect);
}

QWidget *ColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    Q_UNUSED(option)

    //Cоздаем checkbox editor
    QColorDialog *editor = new QColorDialog(parent);

    return editor;
}

void ColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    //Установливаем выбрано/не выбрано
    QColorDialog *cb = qobject_cast<QColorDialog *>(editor);
    cb->setCurrentColor(index.data().value<QColor>());
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    //Записываем данные в модель
    QColorDialog *cb = static_cast<QColorDialog *>(editor);
    QColor value = cb->currentColor();
    model->setData(index, value, Qt::EditRole);
}

void ColorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{

}


/****************************************************************************************************/

ComboBoxDelegate::ComboBoxDelegate(QStringList values,QObject *parent){
    m_values = values;
}

/*void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const{

}*/

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    Q_UNUSED(option)

    //Cоздаем checkbox editor
    QComboBox *editor = new QComboBox(parent);
    editor->insertItems(0,m_values);

    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    //Установливаем выбрано/не выбрано
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    cb->setCurrentText("Track " + index.data().value<QString>());
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    //Записываем данные в модель
    QComboBox *cb = static_cast<QComboBox *>(editor);
    QString value = cb->currentText();
    model->setData(index, value, Qt::EditRole);
}

/*void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{

}*/






