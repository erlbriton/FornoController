#include "melody_gpio.hpp"
#include "melody_library.hpp"
#include "tim.h"
#include "main.h"

bool MelodyPlayer::isPlaying = false;
size_t MelodyPlayer::currentNoteIndex = 0;
uint16_t MelodyPlayer::currentNoteTimeLeft = 0;
bool MelodyPlayer::pinState = false;

const uint16_t* MelodyPlayer::currentMelody = nullptr;
const uint16_t* MelodyPlayer::currentDurations = nullptr;
size_t MelodyPlayer::melodyLength = 0;

void MelodyPlayer::setTim11Frequency(uint16_t frequency) {
    if (frequency == 0) return;

    uint32_t timerClock = 84000000; // APB2 = 84 MHz
    uint32_t prescaler = 83;        // Делим на 84 → 1 МГц
    uint32_t period = (1000000 / (frequency * 2)) - 1; // в полупериодах

    __HAL_TIM_DISABLE(&htim11);
    htim11.Instance->PSC = prescaler;
    htim11.Instance->ARR = period;
    __HAL_TIM_SET_COUNTER(&htim11, 0);
    __HAL_TIM_ENABLE(&htim11);
}

void MelodyPlayer::play(const uint16_t* melody, const uint16_t* durations, size_t length) {
    currentMelody = melody;
    currentDurations = durations;
    melodyLength = length;
    currentNoteIndex = 0;
    isPlaying = true;
    currentNoteTimeLeft = durations[0];

    setTim11Frequency(melody[0]);
    HAL_TIM_Base_Start_IT(&htim11);
}

void MelodyPlayer::stop() {
    HAL_TIM_Base_Stop_IT(&htim11);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
    isPlaying = false;
}

void MelodyPlayer::handleTimerInterrupt() {
    if (!isPlaying || !currentMelody || !currentDurations) return;

    uint16_t note = currentMelody[currentNoteIndex];
    if (note == 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
    } else {
        pinState = !pinState;
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, pinState ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    if (--currentNoteTimeLeft == 0) {
        nextNote();
    }
}

void MelodyPlayer::nextNote() {
    currentNoteIndex++;
    if (currentNoteIndex >= melodyLength) {
        stop();
        return;
    }

    currentNoteTimeLeft = currentDurations[currentNoteIndex];
    setTim11Frequency(currentMelody[currentNoteIndex]);
}

void MelodyPlayer::playPodmoskovnye() {
    play(MelodyLibrary::PodmoskovnyeVechera,
         MelodyLibrary::PodmoskovnyeVecheraDurations,
         MelodyLibrary::PodmoskovnyeVecheraLength);
}
