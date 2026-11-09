#pragma once

// -- my
#include <panel-conf.hpp>
// -- qt
#include <QWidget>
#include <QHBoxLayout>
// -- qt -- namespace -- macros
#include <qtmetamacros.h>
// -- stl
#include <cstdint>

namespace pan {

enum class zone : int8_t {
    left,
    center,
    right,
};

class panel : public QWidget {
    Q_OBJECT
private:
    // Config
    config config_;

    // main layout 
    QBoxLayout* main_layout_ { nullptr };

    // Zone
    QWidget* left_zone_ { nullptr };
    QWidget* center_zone_ { nullptr };
    QWidget* right_zone_ { nullptr };

    // Layout
    QBoxLayout* left_layout_ { nullptr };
    QBoxLayout* center_layout_ { nullptr };
    QBoxLayout* right_layout_ { nullptr };
public:
    explicit panel(const config& _conf, QWidget* _parent = nullptr);
    ~panel() override = default;
    
    void add_widget(QWidget* _widget, const zone& _zone = zone::left);
    void apply_config(const config& _conf);
protected:
    void showEvent(QShowEvent* _event) override;
};

}
