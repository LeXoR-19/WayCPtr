#include <QApplication>
#include <panel.hpp>
#include <engine.hpp>

constexpr std::string CONFIG { "config.lua" };

int main(int argc, char** argv) {
    qputenv("QT_LOGGING_RULES", "qt.qpa.wayland.textinput=false");

    QApplication app(argc, argv);
    
    config conf;
    panel p(conf);
    p.show();

    lua::engine engine;

    engine.set_panel_callback([&p](const config& conf) {
        p.apply_config(conf);
    });
    
    engine.set_style_callback([&p](const std::string _path) {
        p.apply_style(QString::fromStdString(_path));
    });

    engine.init();
    (void)engine.load_config(QString::fromStdString(CONFIG));

    return app.exec();
}
