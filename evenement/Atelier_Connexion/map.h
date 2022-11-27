#ifndef MAP_H
#define MAP_H

#include <QDialog>
#include <QVariant>

namespace Ui {
class Map;
}

class Map : public QDialog
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

private:
    Ui::Map *ui;

signals:
    void setCenter(QVariant,QVariant) ;
    void addMarker(QVariant, QVariant);
};

#endif // MAP_H
