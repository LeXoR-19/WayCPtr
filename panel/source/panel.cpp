// -- my
#include <panel.hpp>
#include <panel-conf.hpp>
// -- Qt
#include <QHBoxLayout>
#include <QWidget>
#include <QMargins>
// -- qt - namespace - macros
#include <qnamespace.h>
// LayerShell
#include <LayerShellQt/Window>

namespace pan {

panel::panel(const config& _conf, QWidget* _parent) :
    QWidget(_parent),
    config_(_conf)
{
    // === Main Layout Create from orientation ===
    if (this->config_.orient == orientation::horizontal) {
        this->main_layout_ = new QHBoxLayout(this);
    } else {
        this->main_layout_ = new QVBoxLayout(this);
    }

    this->main_layout_->setContentsMargins(0, 0, 0, 0);
    this->main_layout_->setSpacing(0);        
    
    // zone create
    this->left_zone_ = new QWidget(this);
    this->center_zone_ = new QWidget(this);
    this->right_zone_ = new QWidget(this);

    // Layout in Main Layout
    if (this->config_.orient == orientation::horizontal) {
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

    this->main_layout_->addWidget(this->left_zone_, 0);
    this->main_layout_->addWidget(this->center_zone_, 1);
    this->main_layout_->addWidget(this->right_zone_, 0);

    this->apply_config(this->config_);
}

void panel::add_widget(QWidget* _widget, const zone& _zone) {
    if (_widget == nullptr) {
        return;
    }

    switch (_zone) {
        case zone::left:
            if (this->left_layout_ != nullptr) {
                this->left_layout_->addWidget(_widget);
            }
            break;
        case zone::center:
            if (this->center_layout_ != nullptr) {
                this->center_layout_->addWidget(_widget);
            }
            break;
        case zone::right:
            if (this->right_layout_ != nullptr) {
                this->right_layout_->addWidget(_widget);
            }
            break;
    }
}

void panel::apply_config(const config& _conf) {
    this->config_ = _conf;

    if (this->config_.orient == orientation::horizontal) {
        setFixedHeight(this->config_.height);
        if (this->config_.width == -1) {
            setMinimumWidth(0);
            setMaximumWidth(QWIDGETSIZE_MAX);
        } else {
            setFixedWidth(this->config_.width);
        }
    } else {
        setFixedWidth(this->config_.width);
        if (this->config_.height == -1) {
            setMinimumHeight(0);
            setMaximumHeight(QWIDGETSIZE_MAX);
        } else {
            setFixedHeight(this->config_.height);
        }
    }

    if (this->left_layout_ != nullptr) {
        this->left_layout_->setContentsMargins(
            this->config_.padding[3],
            this->config_.padding[0],
            0,
            this->config_.padding[2]
        );
    }
    if (this->right_layout_ != nullptr) {
        this->right_layout_->setContentsMargins(
            0,
            this->config_.padding[0],
            this->config_.padding[1],
            this->config_.padding[2]
        );
    }

    if (auto* win { windowHandle() }) {
        if (auto* layer { LayerShellQt::Window::get(win) }) {
            layer->setMargins(QMargins(
                this->config_.margin[3],
                this->config_.margin[0],
                this->config_.margin[1],
                this->config_.margin[2]
            ));
        }
    }
}

void panel::showEvent(QShowEvent* _event) {
    QWidget::showEvent(_event);

    if (auto* win { windowHandle() }) {
        auto* layer { LayerShellQt::Window::get(win) };

        if (layer != nullptr) {
            LayerShellQt::Window::Anchors anchors;

            switch (this->config_.pos) {
                case position::top:
                    anchors = LayerShellQt::Window::Anchors(
                        LayerShellQt::Window::AnchorTop |
                        LayerShellQt::Window::AnchorLeft |
                        LayerShellQt::Window::AnchorRight
                    );
                    layer->setExclusiveZone(this->config_.height);
                    break;
                case position::bottom:
                    anchors = LayerShellQt::Window::Anchors(
                        LayerShellQt::Window::AnchorBottom |
                        LayerShellQt::Window::AnchorLeft |
                        LayerShellQt::Window::AnchorRight
                    );
                    layer->setExclusiveZone(this->config_.height);
                    break;
                case position::left:
                    anchors = LayerShellQt::Window::Anchors(
                        LayerShellQt::Window::AnchorLeft |
                        LayerShellQt::Window::AnchorTop |
                        LayerShellQt::Window::AnchorBottom
                    );
                    layer->setExclusiveZone(this->config_.width);
                    break;
                case position::right:
                    anchors = LayerShellQt::Window::Anchors(
                        LayerShellQt::Window::AnchorRight |
                        LayerShellQt::Window::AnchorTop |
                        LayerShellQt::Window::AnchorBottom
                    );
                    layer->setExclusiveZone(this->config_.width);
                    break;
            }
            layer->setAnchors(anchors);

            layer->setMargins(QMargins(
                this->config_.margin[3],
                this->config_.margin[0],
                this->config_.margin[1],
                this->config_.margin[2]
            ));
        }
    }
}

}
