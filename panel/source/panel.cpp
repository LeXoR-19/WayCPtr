#include <panel.hpp>

#include <QTimer>
#include <LayerShellQt/Window>
#include <QFile>
#include <QDir>
#include <QPainter>
#include <QStyleOption>

panel::panel(const config& _conf, QWidget* _parent) :
    QWidget(_parent),
    config_(_conf)
{
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setObjectName("panel");

    this->setup_layouts();
    this->apply_config(this->config_);

    auto* timer { new QTimer(this) };

    QObject::connect(timer, &QTimer::timeout, [this]() {
        // FIX: Добавить обновление виджетов
    });
    timer->start(1000);
}

void panel::setup_layouts() {
    if (this->config_.orientation == Orientation::Horizontal)
        this->main_layout_ = new QHBoxLayout(this);
    else
        this->main_layout_ = new QVBoxLayout(this);
    this->main_layout_->setContentsMargins(0, 0, 0, 0);
    this->main_layout_->setSpacing(0);

    this->left_zone_ = new QWidget(this);
    this->center_zone_ = new QWidget(this);
    this->right_zone_ = new QWidget(this);

    if (this->config_.orientation == Orientation::Horizontal) {
        this->left_layout_ = new QHBoxLayout(this->left_zone_);
        this->center_layout_ = new QHBoxLayout(this->center_zone_);
        this->right_layout_ = new QHBoxLayout(this->right_zone_);

        this->left_layout_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->center_layout_->setAlignment(Qt::AlignCenter);
        this->right_layout_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    } else {
        this->left_layout_ = new QVBoxLayout(this->left_zone_);
        this->center_layout_ = new QVBoxLayout(this->center_zone_);
        this->right_layout_ = new QVBoxLayout(this->right_zone_);

        this->left_layout_->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
        this->center_layout_->setAlignment(Qt::AlignCenter);
        this->right_layout_->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    }
    this->left_layout_->setContentsMargins(0, 0, 0, 0);
    this->center_layout_->setContentsMargins(0, 0, 0, 0);
    this->right_layout_->setContentsMargins(0, 0, 0, 0);

    this->main_layout_->addWidget(this->left_zone_, 0);
    this->main_layout_->addWidget(this->center_zone_, 1);
    this->main_layout_->addWidget(this->right_zone_, 0);
}

void panel::apply_config(const config& _conf) {
    this->config_ = _conf;

    if (this->config_.orientation == Orientation::Horizontal)
        this->setHeight(this->config_.height);
    else
        this->setWidth(this->config_.width);

    this->setPadding();
    this->setup_layer_shell();
}

void panel::apply_style(const QString& _path) {
    QFile file(_path);

    if (!file.exists()) {
        QString home_path { QDir::homePath() + "/" + _path };

        if (QFile::exists(home_path))
            file.setFileName(home_path);
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        this->setStyleSheet(in.readAll());
        qDebug() << "[Panel] Стили загружены из:" << file.fileName();
    } else {
        qWarning() << "[Panel] Не удалось открыть файл стилей:" << _path;
    }
}

void panel::setWidth(int _width) {
    if (_width > 0) {
        this->setFixedWidth(_width);
    } else {
        this->setMinimumWidth(0);
        this->setMaximumWidth(QWIDGETSIZE_MAX);
    }
}

void panel::setHeight(int _height) {
    if (_height > 0) {
        this->setFixedHeight(_height);
    } else {
        this->setMinimumHeight(0);
        this->setMaximumHeight(QWIDGETSIZE_MAX);
    }
}

void panel::setPadding() {
    int top { this->config_.padding[0] };
    int right { this->config_.padding[1] };
    int bottom { this->config_.padding[2] };
    int left { this->config_.padding[3] };

    if (this->config_.orientation == Orientation::Horizontal) {
        this->left_layout_->setContentsMargins(left, top, 0, bottom);
        this->right_layout_->setContentsMargins(0, top, right, bottom);
    } else {
        this->left_layout_->setContentsMargins(left, top, right, 0);
        this->right_layout_->setContentsMargins(left, 0, right, bottom);
    }
}

void panel::setMargin() {
    int top { this->config_.margin[0] };
    int right { this->config_.margin[1] };
    int bottom { this->config_.margin[2] };
    int left { this->config_.margin[3] };

    if (auto* win { this->windowHandle() })
        if (auto* layer { LayerShellQt::Window::get(win) }) {
            layer->setMargins(QMargins(
                left, top, right, bottom
            ));
        }
}

void panel::setup_layer_shell() {
    if (auto* win { windowHandle() }) {
        if (auto* layer { LayerShellQt::Window::get(win) }) {
            this->setLayer(this->config_.layer);
            this->setAnchor(this->config_.anchors);
            this->setExclusiveZone(this->config_.exclusive_zone);
            this->setMargin();
        }
    }
}


void panel::setLayer(Layer _layer) {
    if (auto* win { windowHandle() }) {
        if (auto* layer { LayerShellQt::Window::get(win) }) {
            switch (_layer) {
                case Layer::Background:
                    layer->setLayer(LayerShellQt::Window::LayerBackground);
                    break;
                case Layer::Bottom:
                    layer->setLayer(LayerShellQt::Window::LayerBottom);
                    break;
                case Layer::Top:
                    layer->setLayer(LayerShellQt::Window::LayerTop);
                    break;
                case Layer::Overlay:
                    layer->setLayer(LayerShellQt::Window::LayerOverlay);
                    break;
                    
            }
        }
    }
}

void panel::setAnchor(Anchor _anchor) {
    if (auto* win { windowHandle() }) {
        if (auto* layer { LayerShellQt::Window::get(win) }) {
            LayerShellQt::Window::Anchors qt_anchors;
            if (has_anchor(_anchor, Anchor::Left))
                qt_anchors |= LayerShellQt::Window::AnchorLeft;
            if (has_anchor(_anchor, Anchor::Bottom))
                qt_anchors |= LayerShellQt::Window::AnchorBottom;
            if (has_anchor(_anchor, Anchor::Top))
                qt_anchors |= LayerShellQt::Window::AnchorTop;
            if (has_anchor(_anchor, Anchor::Right))
                qt_anchors |= LayerShellQt::Window::AnchorRight;
            layer->setAnchors(qt_anchors);
        }
    }
}

void panel::setExclusiveZone(bool _exzone) {
    if (auto* win { windowHandle() }) {
        if (auto* layer { LayerShellQt::Window::get(win) }) {
            if (_exzone) {
                int size { this->config_.orientation == Orientation::Horizontal
                           ? this->config_.height
                           : this->config_.width
                };
                layer->setExclusiveZone(size);
            } else {
                layer->setExclusiveZone(0);
            }
        }
    }
}

void panel::showEvent(QShowEvent* _event) {
    QWidget::showEvent(_event);

    this->setup_layer_shell();
}

void panel::paintEvent(QPaintEvent* _event) {
    Q_UNUSED(_event);
    
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
