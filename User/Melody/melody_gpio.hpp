#ifndef MELODY_GPIO_HPP
#define MELODY_GPIO_HPP

#include <stdint.h>
#include <stddef.h>

class MelodyPlayer {
public:
    static void play(const uint16_t* melody, const uint16_t* durations, size_t length);
    static void stop();
    static void handleTimerInterrupt();
    static void playPodmoskovnye();

private:
    static void nextNote();
    static void setTim11Frequency(uint16_t frequency);

    static bool isPlaying;
    static size_t currentNoteIndex;
    static uint16_t currentNoteTimeLeft;
    static bool pinState;

    static const uint16_t* currentMelody;
    static const uint16_t* currentDurations;
    static size_t melodyLength;
};

#endif // MELODY_GPIO_HPP
