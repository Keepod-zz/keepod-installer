#include "customitemdelegate.h"

#include <QApplication>

CustomItemDelegate::CustomItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
    _state = QStyle::State_Enabled;
}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //if(index.parent().isValid())
    //{
        QStyleOptionProgressBarV2 progressBarOption;
        QRect rect;
        //QSize size(rect.width()*3/4,rect.height()*3/4);

        rect.setLeft(option.rect.left());
        rect.setRight(option.rect.right());
        rect.setTop(option.rect.top() + option.rect.height()/3);
        rect.setBottom(option.rect.top() + option.rect.height()*2/3);

        //rect.setSize(size);
        progressBarOption.state = QStyle::State_Enabled;
        progressBarOption.direction = QApplication::layoutDirection();
        progressBarOption.rect = rect;
        progressBarOption.fontMetrics = QApplication::fontMetrics();

        QPalette pal = progressBarOption.palette;
        QColor col;

        col.setNamedColor("#05B8CC");
        pal.setColor(QPalette::Highlight,col);
        progressBarOption.palette = pal;
        progressBarOption.type = QStyleOption::SO_ProgressBar;
        progressBarOption.version = 2 ;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.textAlignment = Qt::AlignCenter;
        progressBarOption.textVisible = true;

        int progress = index.data(Qt::DisplayRole).toInt();//TCP client or server must changes this value emitting signal bytesWritten(qint64)
        progressBarOption.progress = progress;
        //progressBarOption.text = QString("%1%").arg(progressBarOption.progress);
        progressBarOption.text = QString("");

        // Draw the progress bar onto the view.
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter,0);

    //}
    //else
    //{
    //    QItemDelegate::paint(painter, option, index);
    //}
}
