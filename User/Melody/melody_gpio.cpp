//melody_gpio.cpp

#include "melody_gpio.hpp"
#include "melody_library.hpp"
#include "tim.h"
#include "main.h"

extern TIM_HandleTypeDef htim8;
uint32_t MelodyPlayer::noteTimeout = 0;
uint16_t MelodyPlayer::currentNoteIdx = 0;

const Note podmoskovnye[] = {
    {440, 600},  // Не
    {494, 200},  // слыш-
    {523, 400},  // ны
    {494, 400},  // в са-
    {440, 400},  // ду
    {494, 800},  // да-
    {440, 400},  // же
    {392, 400},  // шо-
    {330, 800},  // ро-хи.
    {0, 200},    // Пауза
    {0, 0}       // Конец мелодии
};

void MelodyPlayer::setFrequency(uint16_t frequency) {
    // Если частота 0 — выключаем звук
    if (frequency == 0) {
        HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
        return;
    }

    // Вычисляем период для таймера (базовая частота 1 МГц / нужная частота)
    uint32_t period = 1000000 / frequency;

    // 1. Устанавливаем период (высоту ноты)
    __HAL_TIM_SET_AUTORELOAD(&htim8, period - 1);

    // 2. Устанавливаем скважность 50% (громкость)
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, period / 2);

    // 3. ВКЛЮЧАЕМ ГЛАВНЫЙ ВЫХОД (Обязательно для TIM8)
    __HAL_TIM_MOE_ENABLE(&htim8);

    // 4. Запускаем генерацию ШИМ на PB15
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
}

    void MelodyPlayer::processNextNoteAsync() {
        // 1. Если время текущей ноты еще не вышло — просто выходим
        if (HAL_GetTick() < noteTimeout) {
            return;
        }

        // 2. Берем текущую ноту из массива (массив подмосковные мы создадим в след. шаге)
        // podmoskovnye — это будет наш массив структур {частота, длительность}
        Note currentNote = podmoskovnye[currentNoteIdx];

        // 3. Проверяем, не конец ли это мелодии (маркер конца — длительность 0)
        if (currentNote.duration == 0) {
            setFrequency(0); // Выключаем звук
            return;          // Больше ничего не делаем
        }

        // 4. Включаем частоту текущей ноты
        setFrequency(currentNote.frequency);

        // 5. Рассчитываем время, когда нужно будет переключиться на следующую ноту
        noteTimeout = HAL_GetTick() + currentNote.duration;

        // 6. Переходим к следующему индексу
        currentNoteIdx++;
    }

    void MelodyPlayer::playPodmoskovnye() {
        currentNoteIdx = 0;   // Сбрасываем на начало
        noteTimeout = 0;      // Сбрасываем таймер, чтобы заиграло мгновенно
    }

