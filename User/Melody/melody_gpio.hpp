//melody_gpio.hpp

#ifndef MELODY_GPIO_HPP
#define MELODY_GPIO_HPP

#include <stdint.h>
#include <stddef.h>

struct Note {
    uint16_t frequency; // Частота в Гц
    uint16_t duration;  // Длительность в мс
};

extern const Note podmoskovnye[];

class MelodyPlayer {
public:
//    static void play(const uint16_t* melody, const uint16_t* durations, size_t length);
//    static void stop();
//    static void handleTimerInterrupt();
//    static void playPodmoskovnye();

    static void setFrequency(uint16_t frequency);
    static void processNextNoteAsync(); // Этот метод будет вызываться в main
    static void playPodmoskovnye();

private:
    static uint32_t noteTimeout;     // Время окончания текущей ноты
    static uint16_t currentNoteIdx;  // Индекс текущей ноты в массиве
};

#endif // MELODY_GPIO_HPP
