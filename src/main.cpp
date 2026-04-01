#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <map>

using namespace geode::prelude;

// El mapa de tiempos (puedes rellenar más luego, te dejo los básicos)
std::map<std::string, int> countryOffsets = {
    {"Venezuela (Caracas)", -4},
    {"España (Madrid)", 1},
    {"Colombia (Bogotá)", -5},
    {"Argentina (Buenos Aires)", -3},
    {"México (CDMX)", -6},
    {"Estados Unidos (Washington D.C.)", -5}
};

class $modify(MySyncTime, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto label = CCLabelBMFont::create("", "chatFont.fnt");
        label->setID("synctime-label"_spr);
        label->setScale(0.40f);
        
        // Posición (esquina inferior izquierda)
        auto winSize = CCDirector::get()->getWinSize();
        label->setPosition({ 10, 10 });
        label->setAnchorPoint({ 0, 0 });
        
        this->addChild(label);

        // Programar la actualización cada segundo
        this->schedule(schedule_selector(MySyncTime::updateTimeLabel), 1.0f);

        return true;
    }

    void updateTimeLabel(float dt) {
        auto label = static_cast<CCLabelBMFont*>(this->getChildByID("synctime-label"_spr));
        if (!label) return;

        auto selectedCountry = Mod::get()->getSettingValue<std::string>("pais-seleccionado");
        int offset = countryOffsets[selectedCountry];

        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        auto utc = *std::gmtime(&time_t_now);

        utc.tm_hour += offset;
        std::mktime(&utc); // Ajustar desbordamiento de horas

        std::stringstream ss;
        ss << selectedCountry << "\n" << std::put_time(&utc, "%H:%M:%S | %d/%m/%Y");
        label->setString(ss.str().c_str());
    }
};
