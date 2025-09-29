/*
 * Heat.cpp
 *
 *  Created on: Jan 25, 2024
 *      Author: erlbriton
 */

#include "Heat.hpp"
#include "Button.hpp"
#include "Fram.hpp"
#include "Control.hpp"
#include "SetTimer.hpp"
#include "melody_gpio.hpp"

#define safeTemperature 90

//------------------------------Главный метод--------------------------------------------------
void Heat::ajustHeat595(vu8 numberRegimCook) {
	if (!checkProtectionTriggers()) {//Если защиты не сработали
		vu8 differenceTemper = Fram::framRD0byte() - Control::ovenTemper;
		bool hiLowMode = static_cast<bool>(differenceTemper > HysteresisTemp());
		vu8 dataTransmit = modeTable[numberRegimCook][hiLowMode];
		TransmitToTENs(dataTransmit);
	}
	checkAndPlaySound(Fram::framRD0byte());
	SetTimer::TimeCook(Button::dirTime);
}

//----------------------------Передаем на ТЭНЫ через SPI и HC595---------------------------
void Heat::TransmitToTENs(vu8 dataTransmit) {
//Сравниваем свежую посылку(dataMode[0]) с уже включенными выходами HC595,
//если равны - блокируем вывод Latch HC595. Таким образом включенные ТЭНы остаются без изменения
	uint8_t difference = dataModeOld - dataTransmit; //Разность между набором включенных выходов и новой  посылкой
	GPIO_PinState diff = (GPIO_PinState) difference; //true - разность есть, false - разности нет
	LL_SPI_TransmitData8(SPI3, dataTransmit);	//Передаем на тэны через HC595
	while (!LL_SPI_IsActiveFlag_TXE(SPI3)) { }//Ждем освобождения буфера передачи
	HAL_GPIO_WritePin(Latch, diff);	//Latch. Если diff = true - передаем посылку, если diff = false - посылка не передастся
	HAL_GPIO_WritePin(Latch, GPIO_PIN_RESET);	//Latch
	//------ Включаем или выключаем пламя на дисплее в зависимости от включенных тенов ----------------------------
	//--------------------------Информацию берем c выходов HC595---------------------------------------------------
	buf_485[13] = downIn; //Пламя внизу
	buf_485[15] = grillIn; //Пламя вверху
	buf_485[14] = rightIn; //Пламя сбоку
	uint8_t rIn = rightIn << 2;          //Читаем...
	uint8_t gIn = grillIn << 1;          //...включенные...
	uint8_t dIn = downIn << 0;           //...выходы...
	uint8_t fIn = dataTransmit >> 3 << 3;   //...HC595
	dataModeOld = rIn + gIn + dIn + fIn;//Старая посылка
}
//------------------------Гистерезис температур в зависимости от режима---------------------------------------------------
 vu8 Heat::HysteresisTemp() {
	 return Fram::elementFram(1) == 1 ? tempPreOver : tempOtherOver;
}
//--------------------------------Управление внешним кулером---------------------
void Heat::setOutCooler() {
		GPIOA->BSRR = (Control::ovenTemper > safeTemperature && Fram::elementFram(1) != 3)
		              ? GPIO_PIN_11               // включить кулер
		              : GPIO_PIN_11 << 16U;       // выключить кулер
}
//--------------------------------Подача звука при предварительном нагреве-----------
//void Heat::soundMatch() {
//	TIM7->ARR = 12;        // Немного изменяю на ходу
//	TIM7->PSC = 1680;      //частоту звука
//	TIM7->EGR = TIM_EGR_UG;//просто для тренировки
//	//HAL_ADC_Stop (&hadc2);/*Если не остановить ADC режима в момент подачи сигнала конца предварительного нагрева то
//	// при случайном переключении режима звук какое-то время ведет себя неадекватно*/
//	HAL_TIM_Base_Start_IT(&htim7);
//	HAL_TIM_Base_Start_IT(&htim9);
//}
//-------------------------------------------------------Проверка защит----------------------------------------------------
struct ProtectionTrigger {
	std::function<bool()> condition;//Условие, которое проверяется (возвращает true или false)
	std::function<bool()> action;//Что делать, если условие выполнено
};
bool aaa = 0;
bool Heat::checkProtectionTriggers() {
	const ProtectionTrigger triggers[ ] = {
		{
			[]() { return doorRd != 0 && Control::ovenTemper > safeTemperature;},//Открыта дверь и температуры выше безопасной
			[]() { dataMode = 0; TransmitToTENs(dataMode); return true; }
		},
		{
			[]() { return Control::ovenTemper > Fram::framRD0byte(); },//Перегрев
			[]() { dataMode &= 0b1000; TransmitToTENs(dataMode); return true; }//Кулер не изменяем
		},
		{
			[]() { return rightIn && downIn && grillIn; },//Проверка всех включенных тэнов
			[]() { Button::regim1Button(); return true; }
		},
		{
				[]() {//Проверка прошедшего времени при t < 120 град
				return (Fram::framRD0byte() > 70 && Fram::framRD0byte() <= 120) && (SetTimer::totalTime > maxTotalTime);//12 часов
			},
			[]() { Button::regim1Button(); return true; }
		},
		{
			[]() {//Проверка прошедшего времени при t > 120 град
				return Fram::framRD0byte() > 120 && SetTimer::totalTime > minTotalTime;//3 часа
			},
			[]() { Button::regim1Button(); return true; }
		}
	};
	for (const auto& trigger : triggers) {//Проходимся по массиву циклом:
		if (trigger.condition() && trigger.action()) {
			return true;
		}
	}
	return false;
}
//------------------------------Подаем сигнал предварительного нагрева-------------------------------
void Heat::checkAndPlaySound(vu8 setTemp) {
    (Fram::elementFram(1) == 1 && Heat::soundPre == 0 && ((setTemp - Control::ovenTemper) <= HysteresisTemp())) &&
    		(MelodyPlayer::playPodmoskovnye(),//Играет "Подмосковные вечера"
            Heat::soundPre = true);//Флаг "Звук предварительного нанрева подан"
}

