/*
 * Control.hpp
 *
 *  Created on: Jan 16, 2024
 *      Author: erlbriton
 */

#ifndef CONTROL_CONTROL_HPP_
#define CONTROL_CONTROL_HPP_
#include "flashdata.hpp"
#include "adc.h"
#include "main.h"
#include "FryMode.hpp"
#include <array>
#include <boost/preprocessor/repetition/repeat.hpp>//Здесь использована сторонняя библиотека  "boost" для короткой записи массива

#define REPEAT(z, n, value) value,//Дефайн для короткой записи массива

class Control {
private:
	static inline const uint16_t VREF = 1500;//Постоянный коффициент референса
	static inline uint32_t tempADC = 0;//Сырые данные АЦП температуры в шкафу
	static inline uint32_t tVref = 0;//Сырые данные АЦП референса
	static inline float kVref = 0;//Поправочный коффициент референса
	static inline uint32_t adcRaw = 0; //Сырые данные ADC задатчика режима

public:
	inline static vu16 ovenTemper = 0;
	inline static vu32 adcTemp[2] = {0, };
	static vu32 bakeTemper();
	static vu16 readAdc(vu8); //Читаем задатчик режима
	static bool backInfo(void);
	bool isEncDone() const;//Геттер EncDone
	void isEncDone(bool newEncDone);//Сеттер EncDone
private:
	static constexpr std::array<vu8, 4096> rawADC = {
			    BOOST_PP_REPEAT(250,   REPEAT, 0)
			    BOOST_PP_REPEAT(60,     REPEAT, 0)
			    BOOST_PP_REPEAT(152, REPEAT, 10)
				BOOST_PP_REPEAT(220,  REPEAT, 9)
				BOOST_PP_REPEAT(250,   REPEAT, 8)
				BOOST_PP_REPEAT(12,     REPEAT, 8)
				BOOST_PP_REPEAT(250,   REPEAT, 7)
				BOOST_PP_REPEAT(9,       REPEAT, 7)
				BOOST_PP_REPEAT(250,   REPEAT, 6)
				BOOST_PP_REPEAT(52,     REPEAT, 6)
				BOOST_PP_REPEAT(250,   REPEAT, 5)
				BOOST_PP_REPEAT(119,   REPEAT, 5)
				BOOST_PP_REPEAT(250,   REPEAT, 4)
				BOOST_PP_REPEAT(166,   REPEAT, 4)
				BOOST_PP_REPEAT(250,   REPEAT, 3)
				BOOST_PP_REPEAT(238,   REPEAT, 3)
				BOOST_PP_REPEAT(250,   REPEAT, 2)
				BOOST_PP_REPEAT(250,   REPEAT, 2)
				BOOST_PP_REPEAT(90  ,   REPEAT, 2)
				BOOST_PP_REPEAT(250,   REPEAT, 1)
				BOOST_PP_REPEAT(250,   REPEAT, 1)
				BOOST_PP_REPEAT(227,   REPEAT, 1)
	};
};
#endif /* CONTROL_CONTROL_HPP_ */
