#include "melody_gpio.hpp"

extern TIM_HandleTypeDef htim12;

uint32_t MelodyPlayer::noteTimeout = 0;
uint16_t MelodyPlayer::currentNoteIdx = 0;
static bool isPlaying = true;

// Оставляем ваши ноты
#define NOTE_RE   294
#define NOTE_MI   330
#define NOTE_FA   349
#define NOTE_SOL  392
#define NOTE_LA   440
#define NOTE_CS   277 // До-диез (C#)

void MelodyPlayer::setFrequency(uint16_t frequency) {
    if (frequency == 0) {
        __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, 0);
        HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
        return;
    }

    // УМЕНЬШАЕМ базу, чтобы ПОВЫСИТЬ тон.
    // Попробуем 200 000 (в 10 раз меньше, чем когда звук был просто "низким")
    uint32_t timer_base_freq = 2000000;

    // Если 2 000 000 был низким, а 10 000 000 стал ЕЩЕ ниже,
    // попробуем пойти вниз: 500 000
    uint32_t target_base = 500000;

    uint32_t period = target_base / frequency;

    if (period < 2) period = 2;
    if (period > 65535) period = 65535;

    __HAL_TIM_SET_AUTORELOAD(&htim12, (uint32_t)(period - 1));
    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, (uint32_t)(period / 2));

    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
}

void MelodyPlayer::playPodmoskovnye() {
	if (isPlaying) return;
    currentNoteIdx = 0;
    noteTimeout = 0;
    isPlaying = true;
}

void MelodyPlayer::processNextNoteAsync() {
    if (!isPlaying) return;

    if (HAL_GetTick() < noteTimeout) return;
    static const uint16_t tempo = 400;
   // static const uint16_t long_note = 450;

        static const Note song[] = {

            {NOTE_RE,  tempo}, {NOTE_FA,  tempo}, {NOTE_LA,  tempo}, {NOTE_FA,  tempo},
            {NOTE_SOL, tempo}, {NOTE_SOL, tempo}, {NOTE_FA,  tempo}, {NOTE_MI,  tempo},
            {NOTE_LA,  tempo}, {NOTE_LA,  tempo}, {NOTE_SOL, tempo}, {NOTE_SOL, tempo},
            {NOTE_RE,  tempo}, {NOTE_RE,  tempo}, {NOTE_RE,  tempo}, {NOTE_RE,  1},

    };

    if (currentNoteIdx >= 16) {
        setFrequency(0);
        isPlaying = false;
        return;
    }

    setFrequency(song[currentNoteIdx].frequency);
    noteTimeout = HAL_GetTick() + song[currentNoteIdx].duration;

    currentNoteIdx++;
}
