#pragma once

#include <panel-conf.hpp>

#include <QWidget>
#include <QBoxLayout>

class panel : public QWidget {
    Q_OBJECT
private:
    QBoxLayout* main_layout_ { nullptr };

    QWidget* left_zone_ { nullptr };
    QWidget* center_zone_ { nullptr };
    QWidget* right_zone_ { nullptr };

    QBoxLayout* left_layout_ { nullptr };
    QBoxLayout* center_layout_ { nullptr };
    QBoxLayout* right_layout_ { nullptr };

    config config_;
public:
    explicit panel(const config& _conf, QWidget* _parent = nullptr);
    ~panel() override = default;

    void apply_config(const config& _conf);
    void apply_style(const QString& _path);
protected:
    void showEvent(QShowEvent* _event) override;
    void paintEvent(QPaintEvent* _event) override;
private:
    void setup_layouts();
    void setup_layer_shell();

    void setPadding();
    void setMargin();
    void setWidth(int _width);
    void setHeight(int _height);
    void setLayer(Layer _layer);
    void setAnchor(Anchor _anchor);
    void setExclusiveZone(bool _exzone);

};
