#ifndef FILTERLIBRARY_H
#define FILTERLIBRARY_H

//#include <QtMath>
#include <cmath>
#include <random>
#include "filter.h"

//точечные фильтры
#include "autolevel.h"      //Растяжение гистограммы
#include "blackwhite.h"     //Черно Белый
#include "brightness.h"     //Яркость
#include "grayword.h"       //Серый мир
#include "inverse.h"        //Инверсия
#include "sepia.h"          //Сепия
#include "transfer.h"       //Перенос
#include "turn.h"           //Поворот
#include "wave1.h"          //Волна1
#include "wave2.h"          //Волна2


//матричные фильтры
#include "blur.h"           //Размытие
#include "emboss.h"         //Тиснение
#include "gaussblur.h"      //Размытие по Гауссу
#include "glowingedges.h"   //Светящиеся края
#include "maximum.h"        //Максимум
#include "median.h"         //Медианный
#include "sharp.h"          //Резкость
#include "sobel.h"          //Оператор Собеля

//Мат морфология
#include "mathmorphology.h"


#endif // FILTERLIBRARY_H
