#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QItemDelegate>

class CustomItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CustomItemDelegate(QObject *parent = 0);

    QStyle::StateFlag  _state;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
signals:
    
public slots:
    
};

#endif // CUSTOMITEMDELEGATE_H
