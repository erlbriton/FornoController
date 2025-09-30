/*
 * Button.cpp
 *
 *  Created on: Jan 22, 2024
 *      Author: erlbriton
 */
#include "Button.hpp"
#include "Heat.hpp"
#include "FryMode.hpp"
#include <array>
#include <cstdio>
#include "SetTimer.hpp"
#include "flashdata.hpp"
//--------------------------------------------Сканируем нажатие-------------------------------------
uint8_t Button::scanButton() {
	vu8 modeCookAveADC = Fram::elementFram(1);
	    bool isCookingMode = modeCookAveADC != 0;
	    bool isButtonPressed = gettingButton == 1 && flagButton == 0;
	    bool isButtonReleased = gettingButton == 0 && flagButton == 1;
	    buttonRegim += isCookingMode && isButtonPressed;
	    buttonRegim = (buttonRegim > 2) ? 2 : buttonRegim;
	    flagButton = (flagButton || isButtonPressed) && !isButtonReleased;
	    return buttonRegim;
}
//-----------------------------------------1-й режим-------------------------------------------------
void Button::buttonRegimOne() {
	if(flagOneButton == false){
			SetTimer::memTime = 0;
			buf_485[1] = 0;
			buf_485[2] = 0;
			HAL_UART_Transmit_IT(&huart3, buf_485, 20);
		}
	vu8 settedMode = Fram::elementFram(1);
	buf_485[12] = 0;//Точки в часах
	(flagSoundButton[0] == 0) && (Heat::spOn(),//Подаем звук нажатой кнопки
	flagSoundButton[0] = 1,
	flagSoundButton[1] = 0,
	flagSoundButton[2] = 0);
//-------------------------------------------------------------------------------------------------------------------------------------------------
bool isSettedMode = (settedMode == set || settedMode == light);
isSettedMode && (buttonRegim = 2);//Если режим "light" - то buttonRegim  сразу =2(время выставлять не нужно)
	zeroing(); //Обнуляем все необходимые флаги
	GPIOA->BSRR |= GPIO_PIN_12;
	pass3Button = false; //Обнуляем флаг прохода режима 3 кнопки(для режима "PRE")
	HAL_TIM_Base_Stop_IT(&htim10);
	flagOneButton = true;
}
//-----------------------Второй режим кнопки----------------------------
void Button::buttonRegimTwo() {//Проверка выключенного режима Pre
    vu8 settedMode = Fram::elementFram(1);
   ( (settedMode == pre) && (buttonRegim = 2)) || (executeMainRegimLogic(), true);//Если режим "pre", то сразу прыгаем во 2-й режим кнопки(время выставлять не нужно)
}
bool Button::executeMainRegimLogic() {//Метод второго и следующих проходов
    if (firstCall) TIM2->CNT = 0;// Первый проход
    bool isFlagSoundButton = (flagSoundButton[1] != true);
    isFlagSoundButton && (Heat::spOn(), flagSoundButton[1] = 1, flagSoundButton[2] = 0);
    pass3Button = false;
    encCount(); // Устанавливаем время (или не устанавливаем)
    timerCntEncoder = TIM2->CNT;
    buf_485[18] = 1;//Рамка вокруг часов при установки времени приготовления
    HAL_UART_Transmit_IT(&huart3, buf_485, 20); // Передаем на дисплей
    SetTimer::setTime();
    firstCall = false;
    dirTime = (timerCntEncoder != 0);//Задаем направление счета времени
    return dirTime;
}
//--------------3-й режим без if else---------------------------------------------------------
void Button::buttonRegimThree() {
    Fram::elementFram(0, cntEncoder);
    TIM2->CNT = cntEncoder; // Пишем в счетчик энкодера и во FRAM
    Fram::fram_wr_massive(); // то, что было запомнено при установке температуры
    // Проверка флага звука кнопки
    (flagSoundButton[2] == 0) && (Heat::spOn(), flagSoundButton[2] = 1, flagSoundButton[0] = 0);
    // Если первый проход
    (!pass3Button) && ([&]() {
        vu8 settedMode = Fram::elementFram(1);
        HAL_TIM_Base_Start_IT(&htim10);
        Fram::elementFram(0, (settedMode != dry) ? FryModeLambda::firstTemp : FryModeLambda::firstTempDry);
        pass3Button = true;
        pass1Button = 0;} (), true);
    Fram::elementFram(5, 1); // Включен режим регулирования
    Fram::fram_wr_massive();
    //Fram::fram_rd_massive();
    buf_485[12] = 1; // Включаем точки в часах
    HAL_Delay(50);
    Fram::framRD0byte();
//   if(Fram::elementFram(1) != 3 && Fram::elementFram(1) != 10){
//    Heat::ajustHeat595(Fram::elementFram(1)); // Переходим к регулированию в выбранном режиме
//    buf_485[18] = 0; // Выключаем рамку вокруг часов
//   }
  (Fram::elementFram(1) != 3 &&Fram::elementFram(1) != 10) && (Heat::ajustHeat595(Fram::elementFram(1)), (buf_485[18] = 0));
}
//------------------------------------------------------------------------------------------------------------------------------------------------
bool Button::regim1Button(){
	setButtonRegim(0);
	return true;
}
const std::array<std::function<void(Button*)>, 3> Button::arrButtonRegim = {
    [ ](Button* btn) { btn->buttonRegimOne(); },
    [ ](Button* btn) { btn->buttonRegimTwo(); },
    [ ](Button* btn) { btn->buttonRegimThree(); }
};
//-------------------------------------Выбор режима кнопки-------------------------------------------
bool Button::executeButtonRegim(vu8 index)  {
    if (index >= 0 && index < arrButtonRegim.size()) {
        arrButtonRegim[index](this); //Передаём `this` в лямбду
    }
    return true;
}
//--------------------------------------Zeroing------------------------------------------------------
void Button::zeroing() {
	SetTimer::number_Iterator_Increment = false;
	SetTimer::number_Iterator_Decrement = false;
	firstCall = true;
	Heat::soundPre = false;
	cntEncoder = 0;
	SetTimer::hoursSet = 0;
	SetTimer::minutesSet = 0;
	SetTimer::memTime = 0;
	Heat::all_off(); //Выключение всего
	SetTimer::number_Iterator_Increment = false;
	Button::dirTime = false;
	SetTimer::secondCounter = 0;
	SetTimer::minCounterInc = 0;
	SetTimer::minCounterDec = 0;
	SetTimer::totalTime = 0;//Общее время нагрева
	//soundPre = false; //Сбрасываем флаг поданного звука  ДОДЕЛАТЬ
	vu8 isSettedMode = Fram::elementFram(1);
	//--------------------Выводим в дисплей-------------------------------------------
//#################################Для калибровки###################################################
//	buf_485[1] = 0; ////Единицы минут
//	buf_485[2] = 0; //Десятки минут
//	buf_485[3] = 0; //Единицы часов
//	buf_485[4] = 0; //Десятки часов
//###########################Конец  для калибровки###################################################
	buf_485[12] = 0;
	buf_485[12] = 0; //Останавливаем точки в часах
	buf_485[13] = 0; //Стираем огонь
	buf_485[14] = 0; //Стираем огонь
	buf_485[15] = 0; //Стираем огонь
}

vu8 Button::encCount() {
	vu8 settedMode = Fram::elementFram(1); // Читаем устaновленный режим
	vu8 byte0Fram = 0;
	(buttonRegim != 1) && (cntEncoder = TIM2->CNT, // Количество импульсов, посчитанных энкодером
	(encMemory != cntEncoder && encDone == true) && ( // Если данные изменились — пишем в индикатор и FRAM
			encMemory = cntEncoder, // Запоминаем значение, посчитанное энкодером, чтобы было с чем сравнивать
			Fram::elementFram(0, cntEncoder), // Записываем в массив для FRAM значение счётчика энкодера
			Fram::fram_wr_massive(), // Записываем массив во FRAM
			Fram::fram_rd_massive(), // Читаем массив обратно (если нужно)
			(settedMode != set) && ( // Выводим, если не режим "Set"
					byte0Fram = Fram::framRD0byte(), buf_485[0] = buf_485[18] =151, // Записываем в массив для передачи в дисплей по RS-485
					buf_485[8] = byte0Fram % 100 % 10, // Единицы
					buf_485[9] = byte0Fram % 100 / 10,    // Десятки
					(buf_485[10] = byte0Fram / 100)          // Сотни
					)), __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2), // Очищаем бит EXTI_PR
	NVIC_ClearPendingIRQ(EXTI2_IRQn),      // Очищаем бит NVIC_ICPRx
	HAL_NVIC_EnableIRQ(EXTI2_IRQn),        // Включаем внешнее прерывание
	encDone = false               // Обнуляем флаг прокрутки
			);
	return cntEncoder; //Если нет - ничего не делаем, чтобы не было мерцаний и ошибок индикатора
}

//------------------------------------Геттеры и сеттеры----------------------------------------------
//vu8 Button::getCntEncoder() const{//Геттер CntEncoder
//	return cntEncoder;
//}
//void Button::setCntEncoder(vu8 newCntEncoder){//Сеттер CntEncoder
//	cntEncoder = newCntEncoder;
//}
vu8 Button::getEncMemory() const{//Геттер EncMemory
	return encMemory;
}
void Button::setEncMemory(vu8 newEncMemory){//Сеттер EncMemory
	encMemory = newEncMemory;
}
//bool Button::isEncDone() const{//Геттер EncDone
//	return encDone;
//}
void Button::isEncDone(bool newEncDone){//Сеттер EncDone
	encDone = newEncDone;
 }
//vu8 Button::getButtonRegim() const{//Геттер ButtonRegim
//	return buttonRegim;
//}
bool Button::setButtonRegim(vu8 newButtonRegim){//Сеттер buttonRegim
	buttonRegim = newButtonRegim;
	return true;
}


