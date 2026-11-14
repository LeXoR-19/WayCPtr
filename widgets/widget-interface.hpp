#pragma once

#include <QWidget>


namespace widget {

class iwidget : public QWidget {
public:
    virtual ~iwidget() = default;
    [[nodiscard]] virtual QWidget* widget() = 0;
    [[nodiscard]] virtual QString name() = 0;
    virtual void init(co)
    virtual void update() = 0;
};

}
