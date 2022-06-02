#ifndef CONFIG_H
#define CONFIG_H
#include <QList>

// Konfiguration Server
const quint16 PORT = 1234;


// Konfiguration GPIO Zusatzboard
const QList<int> LEDS = {25, 24, 23, 18};
const int LFLAGS = 0;
const int CHIP = 0;

#endif // CONFIG_H
