#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>

namespace Ui {
class graphic;
}

class graphic : public QWidget
{
    Q_OBJECT

public:
    explicit graphic(QWidget *parent = nullptr);
    ~graphic();

private:
    Ui::graphic *ui;
};

#endif // GRAPHIC_H
