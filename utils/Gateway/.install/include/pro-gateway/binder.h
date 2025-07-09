#pragma once

#include "reg_server.h"

#include <vector>
#include <memory>

class IRegClient;

class Binder {
private:
    static std::unique_ptr<Binder> _instance;

    struct Binding {
        Address  addr{};
        void*    pvar{};
        VAR_TYPE type{};
    };

    std::vector<Binding>        binds;

    std::shared_ptr<IRegClient> _regClient;

public:
    static Binder& instance();

    Binder(const Binder&) = delete;
    Binder& operator=(const Binder&) = delete;

    void bind(const std::string& regNotation, void* iecVar, VAR_TYPE type);
    void updateToIec();
    void updateFromIec();

private:
    Binder(); //= default;
};

// Глобальные ссылки на proxy-объекты
inline Registry::IX& IX = RegServer::instance().IX();
inline Registry::QX& QX = RegServer::instance().QX();
inline Registry::MX& MX = RegServer::instance().MX();
inline Registry::SX& SX = RegServer::instance().SX();

inline Registry::IB& IB = RegServer::instance().IB();
inline Registry::QB& QB = RegServer::instance().QB();
inline Registry::MB& MB = RegServer::instance().MB();
inline Registry::SB& SB = RegServer::instance().SB();

inline Registry::IW& IW = RegServer::instance().IW();
inline Registry::QW& QW = RegServer::instance().QW();
inline Registry::MW& MW = RegServer::instance().MW();
inline Registry::SW& SW = RegServer::instance().SW();

inline Registry::ID& ID = RegServer::instance().ID();
inline Registry::QD& QD = RegServer::instance().QD();
inline Registry::MD& MD = RegServer::instance().MD();
inline Registry::SD& SD = RegServer::instance().SD();

inline Registry::IL& IL = RegServer::instance().IL();
inline Registry::QL& QL = RegServer::instance().QL();
inline Registry::ML& ML = RegServer::instance().ML();
inline Registry::SL& SL = RegServer::instance().SL();

inline Registry::IF& IF = RegServer::instance().IF();
inline Registry::QF& QF = RegServer::instance().QF();
inline Registry::MF& MF = RegServer::instance().MF();
inline Registry::SF& SF = RegServer::instance().SF();

inline Registry::IE& IE = RegServer::instance().IE();
inline Registry::QE& QE = RegServer::instance().QE();
inline Registry::ME& ME = RegServer::instance().ME();
inline Registry::SE& SE = RegServer::instance().SE();

