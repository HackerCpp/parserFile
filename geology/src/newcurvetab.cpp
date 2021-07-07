#include "newcurvetab.h"

PairWidget::PairWidget(QString name,QWidget *widget){
    m_mainLayuot = new QHBoxLayout(this);
    m_label = new QLabel(name);
    m_label->setMinimumWidth(150);
    m_mainLayuot->addWidget(m_label);
    m_mainLayuot->addWidget(widget);
    //m_mainLayuot->addStretch(100);
    m_mainLayuot->setMargin(0);

}

PairWidget::~PairWidget(){

}




NewCurveTab::NewCurveTab(DataBlock *dataBlock)
{
    m_curve = nullptr;
    m_dataBlock = dataBlock;
    m_comboMnemonicks = new QComboBox;
    m_boxLayout = new QVBoxLayout();

    QStringList f_stringList;
    //f_stringList << "LINE" << "ACU" << "SPECTR" << "MARK";

    for(auto curve : *m_dataBlock->curves()){
        QString f_drawType = curve->desc()->param("draw_type");
        if(f_drawType == "LINE" || f_drawType == "ACOUSTIC" || f_drawType == "SPECTRUM")
            f_stringList << curve->mnemonic();
    }

    m_comboMnemonicks->addItems(f_stringList);
    m_listWidgetPair = new QList<PairWidget *>;
    m_listWidgetPair->push_back( new PairWidget(tr("Curve for copy :"),m_comboMnemonicks));

    /*m_lineSize = new QLineEdit();
    m_lineSize->setText(QString::number(dataBlock->numberOfVectors()));
    m_lineSize->setEnabled(false);
    //m_listWidgetPair->push_back( new PairWidget(tr("Number of vectors :"),m_lineSize));

    m_lineOffset = new QLineEdit();
    m_lineOffset->setText("1");
    //m_listWidgetPair->push_back( new PairWidget(tr("Number elements :"),m_lineOffset));*/

    m_lineMnemonic = new QLineEdit();
    m_lineMnemonic->setText("");
    m_listWidgetPair->push_back( new PairWidget(tr("Mnemonic :"),m_lineMnemonic));

    m_comboShortCuts = new  QComboBox();
    foreach(auto shortCut, *m_dataBlock->shortCuts()){
        m_comboShortCuts->addItem(shortCut.name(),shortCut.ref());
    }

    m_listWidgetPair->push_back( new PairWidget(tr("Name :"),m_comboShortCuts));

    foreach(auto value, *m_listWidgetPair){
        m_boxLayout->addWidget(value);
    }
    m_boxLayout->addStretch(100);
    m_scroll->setLayout(m_boxLayout);
    connect(m_comboMnemonicks,&QComboBox::currentTextChanged,this,&NewCurveTab::changeMnemonic);

}

NewCurveTab::~NewCurveTab(){

}

void NewCurveTab::apply(){
    m_curve = nullptr;
    QString f_currentMnemonic = m_comboMnemonicks->currentText();

    for(auto curve : *m_dataBlock->curves()){
        if (curve->mnemonic() == f_currentMnemonic){
            m_curve = ICurve::curveCreater(*curve);
        }
    }
    if(!m_curve)
        return;
    /*if(!m_curve){
        m_curve = new Curve<double>(m_dataBlock->numberOfVectors(),m_lineOffset->text().toInt());
        Desc *f_desc = new Desc();
        m_curve->setDesc(f_desc);
    }
    m_curve->desc()->setParam("draw_type",m_comboDrawType->currentText());
    ShortCut f_shortCut;
    f_shortCut.setName(m_comboShortCuts->currentText());
    QDateTime f_dateTime;
    QString f_dt = f_dateTime.currentDateTime().toString("dd.MM.yyyy_hh:mm:ss.z").replace(":","-").replace(".","-");
    f_shortCut.setRef(m_comboShortCuts->currentData().toString());
    m_curve->setShortCut(f_shortCut);*/
    //m_curve->setTime(m_dataBlock->time());
    //m_curve->setDepth(m_dataBlock->depth());
    m_curve->setMnemonic(m_lineMnemonic->text());
    m_dataBlock->setcurve(m_curve);
}


void NewCurveTab::changeMnemonic(){
    m_lineMnemonic->setText(m_comboMnemonicks->currentText() + "_COPY");
}
