#include <Nextion.h>
#include <EEPROM.h>
#define diraccionMemoria1 0
#define diraccionMemoria2 1
#define diraccionMemoria3 2
#define diraccionMemoria4 3
struct Configuracion{
  int TempMax;
  int TempMin;
  int HuMax;
  int HuMin;
  int Thora;
  int Tmin;
};
/**
   @example CompText.ino
   @par How to Use
   This example shows that ,when the "+" component on the Nextion screen is released,
   the value of text component will plus 1,when the "-" component released ,the value of
   text component will minus 1 every time.
   @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
   @date    2015/7/10
   @copyright
   Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.
*/


//PAGINA 1
NexNumber textNumber11 = NexNumber(1, 3, "x0");
NexButton buttonPlus11 = NexButton(1, 4, "b2");
NexButton buttonMinus11 = NexButton(1, 5, "b3");
NexNumber textNumber12 = NexNumber(1, 7, "x1");
NexButton buttonPlus12 = NexButton(1, 8, "b4");
NexButton buttonMinus12 = NexButton(1, 9, "b5");
NexNumber textNumber13 = NexNumber(1, 11, "x2");
NexButton buttonPlus13 = NexButton(1, 12, "b6");
NexButton buttonMinus13 = NexButton(1, 13, "b7");
NexNumber textNumber14 = NexNumber(1, 15, "x3");
NexButton buttonPlus14 = NexButton(1, 16, "b8");
NexButton buttonMinus14 = NexButton(1, 17, "b9");
NexNumber textNumber15 = NexNumber(1, 27, "n0");
NexButton buttonPlus15 = NexButton(1, 22, "b10");
NexButton buttonMinus15 = NexButton(1, 23, "b11");
NexNumber textNumber16 = NexNumber(1, 28, "n1");
NexButton buttonPlus16 = NexButton(1, 25, "b12");
NexButton buttonMinus16 = NexButton(1, 26, "b1");
NexButton buttonGuardar1 = NexButton(1, 19, "b13");

//PAGINA 2
NexNumber textNumber21 = NexNumber(2, 3, "x0");
NexButton buttonPlus21 = NexButton(2, 4, "b2");
NexButton buttonMinus21 = NexButton(2, 5, "b3");
NexNumber textNumber22 = NexNumber(2, 7, "x1");
NexButton buttonPlus22 = NexButton(2, 8, "b4");
NexButton buttonMinus22 = NexButton(2, 9, "b5");
NexNumber textNumber23 = NexNumber(2, 11, "x2");
NexButton buttonPlus23 = NexButton(2, 12, "b6");
NexButton buttonMinus23 = NexButton(2, 13, "b7");
NexNumber textNumber24 = NexNumber(2, 15, "x3");
NexButton buttonPlus24 = NexButton(2, 16, "b8");
NexButton buttonMinus24 = NexButton(2, 17, "b9");
NexNumber textNumber25 = NexNumber(2, 27, "n0");
NexButton buttonPlus25 = NexButton(2, 22, "b10");
NexButton buttonMinus25 = NexButton(2, 23, "b11");
NexNumber textNumber26 = NexNumber(2, 28, "n1");
NexButton buttonPlus26 = NexButton(2, 25, "b12");
NexButton buttonMinus26 = NexButton(2, 26, "b1");
NexButton buttonGuardar2 = NexButton(2, 19, "b13");

//PAGINA 3
NexNumber textNumber31 = NexNumber(3, 3, "x0");
NexButton buttonPlus31 = NexButton(3, 4, "b2");
NexButton buttonMinus31 = NexButton(3, 5, "b3");
NexNumber textNumber32 = NexNumber(3, 7, "x1");
NexButton buttonPlus32 = NexButton(3, 8, "b4");
NexButton buttonMinus32 = NexButton(3, 9, "b5");
NexNumber textNumber33 = NexNumber(3, 11, "x2");
NexButton buttonPlus33 = NexButton(3, 12, "b6");
NexButton buttonMinus33 = NexButton(3, 13, "b7");
NexNumber textNumber34 = NexNumber(3, 15, "x3");
NexButton buttonPlus34 = NexButton(3, 16, "b8");
NexButton buttonMinus34 = NexButton(3, 17, "b9");
NexNumber textNumber35 = NexNumber(3, 27, "n0");
NexButton buttonPlus35 = NexButton(3, 22, "b10");
NexButton buttonMinus35 = NexButton(3, 23, "b11");
NexNumber textNumber36 = NexNumber(3, 28, "n1");
NexButton buttonPlus36 = NexButton(3, 25, "b12");
NexButton buttonMinus36 = NexButton(3, 26, "b1");
NexButton buttonGuardar3 = NexButton(3, 19, "b13");
//PAGINA 4
NexNumber textNumber41 = NexNumber(4, 3, "x0");
NexButton buttonPlus41 = NexButton(4, 4, "b2");
NexButton buttonMinus41 = NexButton(4, 5, "b3");
NexNumber textNumber42 = NexNumber(4, 7, "x1");
NexButton buttonPlus42 = NexButton(4, 8, "b4");
NexButton buttonMinus42 = NexButton(4, 9, "b5");
NexNumber textNumber43 = NexNumber(4, 11, "x2");
NexButton buttonPlus43 = NexButton(4, 12, "b6");
NexButton buttonMinus43 = NexButton(4, 13, "b7");
NexNumber textNumber44 = NexNumber(4, 15, "x3");
NexButton buttonPlus44 = NexButton(4, 16, "b8");
NexButton buttonMinus44 = NexButton(4, 17, "b9");
NexNumber textNumber45 = NexNumber(4, 27, "n0");
NexButton buttonPlus45 = NexButton(4, 22, "b10");
NexButton buttonMinus45 = NexButton(4, 23, "b11");
NexNumber textNumber46 = NexNumber(4, 28, "n1");
NexButton buttonPlus46 = NexButton(4, 25, "b12");
NexButton buttonMinus46 = NexButton(4, 26, "b1");
NexButton buttonGuardar4 = NexButton(4, 19, "b13");
int number11 = 300;
int number12 = 300;
int number13 = 300;
int number14 = 300;
int number15 = 1;
int number16 = 30;

int number21 = 300;
int number22 = 300;
int number23 = 300;
int number24 = 300;
int number25 = 1;
int number26 = 30;

int number31 = 300;
int number32 = 300;
int number33 = 300;
int number34 = 300;
int number35 = 1;
int number36 = 30;

int number41 = 300;
int number42 = 300;
int number43 = 300;
int number44 = 300;
int number45 = 1;
int number46 = 30;

char buffer[10] = {0};


/*
   Register object textNumber, buttonPlus, buttonMinus, to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  &textNumber11,
  &buttonPlus11,
  &buttonMinus11,
  &textNumber12,
  &buttonPlus12,
  &buttonMinus12,
  &textNumber13,
  &buttonPlus13,
  &buttonMinus13,
  &textNumber14,
  &buttonPlus14,
  &buttonMinus14,
  &textNumber15,
  &buttonPlus15,
  &buttonMinus15,
  &textNumber16,
  &buttonPlus16,
  &buttonMinus16,
  &buttonGuardar1,
  
  &textNumber21,
  &buttonPlus21,
  &buttonMinus21,
  &textNumber22,
  &buttonPlus22,
  &buttonMinus22,
  &textNumber23,
  &buttonPlus23,
  &buttonMinus23,
  &textNumber24,
  &buttonPlus24,
  &buttonMinus24,
  &textNumber25,
  &buttonPlus25,
  &buttonMinus25,
  &textNumber26,
  &buttonPlus26,
  &buttonMinus26,
  &buttonGuardar2,
  
  &textNumber31,
  &buttonPlus31,
  &buttonMinus31,
  &textNumber32,
  &buttonPlus32,
  &buttonMinus32,
  &textNumber33,
  &buttonPlus33,
  &buttonMinus33,
  &textNumber34,
  &buttonPlus34,
  &buttonMinus34,
  &textNumber35,
  &buttonPlus35,
  &buttonMinus35,
  &textNumber36,
  &buttonPlus36,
  &buttonMinus36,
  &buttonGuardar3,

  &textNumber41,
  &buttonPlus41,
  &buttonMinus41,
  &textNumber42,
  &buttonPlus42,
  &buttonMinus42,
  &textNumber43,
  &buttonPlus43,
  &buttonMinus43,
  &textNumber44,
  &buttonPlus44,
  &buttonMinus44,
  &textNumber45,
  &buttonPlus45,
  &buttonMinus45,
  &textNumber46,
  &buttonPlus46,
  &buttonMinus46,
  &buttonGuardar4,
  NULL
};



/*
   Button0 component pop callback function.
   In this example,the value of the text component will plus one every time when button0 is released.
*/
//PAGINA 1
void buttonGuardarPushCallback1(void *ptr)
{
  Configuracion CustomV;
  inicializarConfig(CustomV);
  int number1 = 0;
  int number2 = 0;
  int number3 = 0;
  int number4 = 0;
  int number5 = 0;
  int number6 = 0;
  textNumber11.getValue(number1);
  textNumber12.getValue(number2);
  textNumber13.getValue(number3);
  textNumber14.getValue(number4);
  textNumber15.getValue(number5);
  textNumber16.getValue(number6);
  Serial.println( "Estructura leida: " );
  Serial.println( number1 );
  Serial.println( number2 );
  SetConfig(CustomV,diraccionMemoria1,number1,number2,number3,number4,number5,number6);
}
void buttonPlusPushCallback11(void *ptr)
{
  if (number11 < 700) number11 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number11, buffer, 10);
  textNumber11.setValue(number11);
}

void buttonMinusPushCallback11(void *ptr)
{
  if (number11 > 0) number11 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number11, buffer, 10);
  textNumber11.setValue(number11);
}

void buttonPlusPushCallback12(void *ptr)
{
  if (number12 < 700) number12 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number12, buffer, 10);
  textNumber12.setValue(number12);
}

void buttonMinusPushCallback12(void *ptr)
{
  if (number12 > 0) number12 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number12, buffer, 10);
  textNumber12.setValue(number12);
}

void buttonPlusPushCallback13(void *ptr)
{
  if (number13 < 700) number13 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number13, buffer, 10);
  textNumber13.setValue(number13);
}

void buttonMinusPushCallback13(void *ptr)
{
  if (number13 > 0) number13 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number13, buffer, 10);
  textNumber13.setValue(number13);
}

void buttonPlusPushCallback14(void *ptr)
{
  if (number14 < 700) number14 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number14, buffer, 10);
  textNumber14.setValue(number14);
}

void buttonMinusPushCallback14(void *ptr)
{
  if (number14 > 0) number14 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number14, buffer, 10);
  textNumber14.setValue(number14);
}

void buttonPlusPushCallback15(void *ptr)
{
  if (number15 < 700) number15 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number15, buffer, 10);
  textNumber15.setValue(number15);
}

void buttonMinusPushCallback15(void *ptr)
{
  if (number15 > 0) number15 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number15, buffer, 10);
  textNumber15.setValue(number15);
}

void buttonPlusPushCallback16(void *ptr)
{
  if (number16 < 700) number16 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number16, buffer, 10);
  textNumber16.setValue(number16);
}

void buttonMinusPushCallback16(void *ptr)
{
  if (number16 > 0) number16 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number16, buffer, 10);
  textNumber16.setValue(number16);
}

//PAGINA 2
void buttonGuardarPushCallback2(void *ptr)
{
  Configuracion CustomV;
  inicializarConfig(CustomV);
  int number1 = 0;
  int number2 = 0;
  int number3 = 0;
  int number4 = 0;
  int number5 = 0;
  int number6 = 0;
  textNumber21.getValue(number1);
  textNumber22.getValue(number2);
  textNumber23.getValue(number3);
  textNumber24.getValue(number4);
  textNumber25.getValue(number5);
  textNumber26.getValue(number6);
  SetConfig(CustomV,diraccionMemoria2,number1,number2,number3,number4,number5,number6);
}
void buttonPlusPushCallback21(void *ptr)
{
  if (number21 < 700) number21 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number21, buffer, 10);
  textNumber21.setValue(number21);
}

void buttonMinusPushCallback21(void *ptr)
{
  if (number21 > 0) number22 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number21, buffer, 10);
  textNumber21.setValue(number21);
}

void buttonPlusPushCallback22(void *ptr)
{
  if (number22 < 700) number22 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number22, buffer, 10);
  textNumber22.setValue(number22);
}

void buttonMinusPushCallback22(void *ptr)
{
  if (number22 > 0) number22 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number22, buffer, 10);
  textNumber22.setValue(number22);
}

void buttonPlusPushCallback23(void *ptr)
{
  if (number23 < 700) number23 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number23, buffer, 10);
  textNumber23.setValue(number23);
}

void buttonMinusPushCallback23(void *ptr)
{
  if (number23 > 0) number23 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number23, buffer, 10);
  textNumber23.setValue(number23);
}

void buttonPlusPushCallback24(void *ptr)
{
  if (number24 < 700) number24 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number24, buffer, 10);
  textNumber24.setValue(number24);
}

void buttonMinusPushCallback24(void *ptr)
{
  if (number24 > 0) number24 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number24, buffer, 10);
  textNumber24.setValue(number24);
}

void buttonPlusPushCallback25(void *ptr)
{
  if (number25 < 700) number25 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number25, buffer, 10);
  textNumber25.setValue(number25);
}

void buttonMinusPushCallback25(void *ptr)
{
  if (number25 > 0) number25 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number25, buffer, 10);
  textNumber25.setValue(number25);
}

void buttonPlusPushCallback26(void *ptr)
{
  if (number26 < 700) number26 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number26, buffer, 10);
  textNumber26.setValue(number26);
}

void buttonMinusPushCallback26(void *ptr)
{
  if (number26 > 0) number26 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number26, buffer, 10);
  textNumber26.setValue(number26);
}

//PAGINA 3
void buttonGuardarPushCallback3(void *ptr)
{
  Configuracion CustomV;
  inicializarConfig(CustomV);
  int number1 = 0;
  int number2 = 0;
  int number3 = 0;
  int number4 = 0;
  int number5 = 0;
  int number6 = 0;
  textNumber31.getValue(number1);
  textNumber32.getValue(number2);
  textNumber33.getValue(number3);
  textNumber34.getValue(number4);
  textNumber35.getValue(number5);
  textNumber36.getValue(number6);
  SetConfig(CustomV,diraccionMemoria3,number1,number2,number3,number4,number5,number6);
}
void buttonPlusPushCallback31(void *ptr)
{
  if (number31 < 700) number31 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number31, buffer, 10);
  textNumber31.setValue(number31);
}

void buttonMinusPushCallback31(void *ptr)
{
  if (number31 > 0) number33 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number31, buffer, 10);
  textNumber31.setValue(number31);
}

void buttonPlusPushCallback32(void *ptr)
{
  if (number32 < 700) number32 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number32, buffer, 10);
  textNumber32.setValue(number32);
}

void buttonMinusPushCallback32(void *ptr)
{
  if (number32 > 0) number32 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number32, buffer, 10);
  textNumber32.setValue(number32);
}

void buttonPlusPushCallback33(void *ptr)
{
  if (number33 < 700) number33 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number33, buffer, 10);
  textNumber33.setValue(number33);
}

void buttonMinusPushCallback33(void *ptr)
{
  if (number33 > 0) number33 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number33, buffer, 10);
  textNumber33.setValue(number33);
}

void buttonPlusPushCallback34(void *ptr)
{
  if (number34 < 700) number34 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number34, buffer, 10);
  textNumber34.setValue(number34);
}

void buttonMinusPushCallback34(void *ptr)
{
  if (number34 > 0) number34 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number34, buffer, 10);
  textNumber34.setValue(number34);
}

void buttonPlusPushCallback35(void *ptr)
{
  if (number35 < 700) number35 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number35, buffer, 10);
  textNumber35.setValue(number35);
}

void buttonMinusPushCallback35(void *ptr)
{
  if (number35 > 0) number35 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number35, buffer, 10);
  textNumber35.setValue(number35);
}

void buttonPlusPushCallback36(void *ptr)
{
  if (number36 < 700) number36 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number36, buffer, 10);
  textNumber36.setValue(number36);
}

void buttonMinusPushCallback36(void *ptr)
{
  if (number36 > 0) number36 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number36, buffer, 10);
  textNumber36.setValue(number36);
}

//PAGINA 4
void buttonGuardarPushCallback4(void *ptr)
{
  Configuracion CustomV;
  inicializarConfig(CustomV);
  int number1 = 0;
  int number2 = 0;
  int number3 = 0;
  int number4 = 0;
  int number5 = 0;
  int number6 = 0;
  textNumber41.getValue(number1);
  textNumber42.getValue(number2);
  textNumber43.getValue(number3);
  textNumber44.getValue(number4);
  textNumber45.getValue(number5);
  textNumber46.getValue(number6);
  SetConfig(CustomV,diraccionMemoria4,number1,number2,number3,number4,number5,number6);
}
void buttonPlusPushCallback41(void *ptr)
{
  if (number41 < 700) number41 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number41, buffer, 10);
  textNumber41.setValue(number41);
}

void buttonMinusPushCallback41(void *ptr)
{
  if (number41 > 0) number44 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number41, buffer, 10);
  textNumber41.setValue(number41);
}

void buttonPlusPushCallback42(void *ptr)
{
  if (number42 < 700) number42 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number42, buffer, 10);
  textNumber42.setValue(number42);
}

void buttonMinusPushCallback42(void *ptr)
{
  if (number42 > 0) number42 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number42, buffer, 10);
  textNumber42.setValue(number42);
}

void buttonPlusPushCallback43(void *ptr)
{
  if (number43 < 700) number43 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number43, buffer, 10);
  textNumber43.setValue(number43);
}

void buttonMinusPushCallback43(void *ptr)
{
  if (number43 > 0) number43 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number43, buffer, 10);
  textNumber43.setValue(number43);
}

void buttonPlusPushCallback44(void *ptr)
{
  if (number44 < 700) number44 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number44, buffer, 10);
  textNumber44.setValue(number44);
}

void buttonMinusPushCallback44(void *ptr)
{
  if (number44 > 0) number44 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number44, buffer, 10);
  textNumber44.setValue(number44);
}

void buttonPlusPushCallback45(void *ptr)
{
  if (number45 < 700) number45 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number45, buffer, 10);
  textNumber45.setValue(number45);
}

void buttonMinusPushCallback45(void *ptr)
{
  if (number45 > 0) number45 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number45, buffer, 10);
  textNumber45.setValue(number45);
}

void buttonPlusPushCallback46(void *ptr)
{
  if (number46 < 700) number46 += 1;
  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number46, buffer, 10);
  textNumber46.setValue(number46);
}

void buttonMinusPushCallback46(void *ptr)
{
  if (number46 > 0) number46 -= 1;
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number46, buffer, 10);
  textNumber46.setValue(number46);
}


void setup(void)
{
  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();
  
  Serial.begin(9600);
  //PAGINA 1
  buttonGuardar1.attachPush(buttonGuardarPushCallback1);
  buttonPlus11.attachPush(buttonPlusPushCallback11);
  buttonMinus11.attachPush(buttonMinusPushCallback11);
  buttonPlus12.attachPush(buttonPlusPushCallback12);
  buttonMinus12.attachPush(buttonMinusPushCallback12);
  buttonPlus13.attachPush(buttonPlusPushCallback13);
  buttonMinus13.attachPush(buttonMinusPushCallback13);
  buttonPlus14.attachPush(buttonPlusPushCallback14);
  buttonMinus14.attachPush(buttonMinusPushCallback14);
  buttonPlus15.attachPush(buttonPlusPushCallback15);
  buttonMinus15.attachPush(buttonMinusPushCallback15);
  buttonPlus16.attachPush(buttonPlusPushCallback16);
  buttonMinus16.attachPush(buttonMinusPushCallback16);
  //PAGINA2
  buttonGuardar2.attachPush(buttonGuardarPushCallback2);
  buttonPlus21.attachPush(buttonPlusPushCallback21);
  buttonMinus21.attachPush(buttonMinusPushCallback21);
  buttonPlus22.attachPush(buttonPlusPushCallback22);
  buttonMinus22.attachPush(buttonMinusPushCallback22);
  buttonPlus23.attachPush(buttonPlusPushCallback23);
  buttonMinus23.attachPush(buttonMinusPushCallback23);
  buttonPlus24.attachPush(buttonPlusPushCallback24);
  buttonMinus24.attachPush(buttonMinusPushCallback24);
  buttonPlus25.attachPush(buttonPlusPushCallback25);
  buttonMinus25.attachPush(buttonMinusPushCallback25);
  buttonPlus26.attachPush(buttonPlusPushCallback26);
  buttonMinus26.attachPush(buttonMinusPushCallback26);
  //PAGINA3
  buttonGuardar3.attachPush(buttonGuardarPushCallback3);
  buttonPlus31.attachPush(buttonPlusPushCallback31);
  buttonMinus31.attachPush(buttonMinusPushCallback31);
  buttonPlus32.attachPush(buttonPlusPushCallback32);
  buttonMinus32.attachPush(buttonMinusPushCallback32);
  buttonPlus33.attachPush(buttonPlusPushCallback33);
  buttonMinus33.attachPush(buttonMinusPushCallback33);
  buttonPlus34.attachPush(buttonPlusPushCallback34);
  buttonMinus34.attachPush(buttonMinusPushCallback34);
  buttonPlus35.attachPush(buttonPlusPushCallback35);
  buttonMinus35.attachPush(buttonMinusPushCallback35);
  buttonPlus36.attachPush(buttonPlusPushCallback36);
  buttonMinus36.attachPush(buttonMinusPushCallback36);
  //PAGINA4
  buttonGuardar4.attachPush(buttonGuardarPushCallback4);
  buttonPlus41.attachPush(buttonPlusPushCallback41);
  buttonMinus41.attachPush(buttonMinusPushCallback41);
  buttonPlus42.attachPush(buttonPlusPushCallback42);
  buttonMinus42.attachPush(buttonMinusPushCallback42);
  buttonPlus43.attachPush(buttonPlusPushCallback43);
  buttonMinus43.attachPush(buttonMinusPushCallback43);
  buttonPlus44.attachPush(buttonPlusPushCallback44);
  buttonMinus44.attachPush(buttonMinusPushCallback44);
  buttonPlus45.attachPush(buttonPlusPushCallback45);
  buttonMinus45.attachPush(buttonMinusPushCallback45);
  buttonPlus46.attachPush(buttonPlusPushCallback46);
  buttonMinus46.attachPush(buttonMinusPushCallback46);


  ///Seteta configuracion si ya hay una guardada
  Configuracion ConfiguracionP1;
  Configuracion ConfiguracionP2;
  Configuracion ConfiguracionP3;
  Configuracion ConfiguracionP4;
  ConfiguracionP1 = GetConfiguracion(diraccionMemoria1);
  ConfiguracionP2 = GetConfiguracion(diraccionMemoria2);
  ConfiguracionP3 = GetConfiguracion(diraccionMemoria3);
  ConfiguracionP4 = GetConfiguracion(diraccionMemoria4);
  if(ConfiguracionP1.TempMax != 0){
    textNumber11.setValue(ConfiguracionP1.TempMax);
    textNumber12.setValue(ConfiguracionP1.TempMin);
    textNumber13.setValue(ConfiguracionP1.HuMax);
    textNumber14.setValue(ConfiguracionP1.HuMin);
    textNumber15.setValue(ConfiguracionP1.Thora);
    textNumber16.setValue(ConfiguracionP1.Tmin);
    number11 = ConfiguracionP1.TempMax;
    number12 = ConfiguracionP1.TempMin;
    number13 = ConfiguracionP1.HuMax;
    number14 = ConfiguracionP1.HuMin;
    number15 = ConfiguracionP1.Thora;
    number16 = ConfiguracionP1.Tmin;
  }
  if(ConfiguracionP2.TempMax != 0){
    textNumber21.setValue(ConfiguracionP2.TempMax);
    textNumber22.setValue(ConfiguracionP2.TempMin);
    textNumber23.setValue(ConfiguracionP2.HuMax);
    textNumber24.setValue(ConfiguracionP2.HuMin);
    textNumber25.setValue(ConfiguracionP2.Thora);
    textNumber26.setValue(ConfiguracionP2.Tmin);
    number21 = ConfiguracionP1.TempMax;
    number22 = ConfiguracionP1.TempMin;
    number23 = ConfiguracionP1.HuMax;
    number24 = ConfiguracionP1.HuMin;
    number25 = ConfiguracionP1.Thora;
    number26 = ConfiguracionP1.Tmin;
  }
  if(ConfiguracionP3.TempMax != 0){
    textNumber31.setValue(ConfiguracionP3.TempMax);
    textNumber32.setValue(ConfiguracionP3.TempMin);
    textNumber33.setValue(ConfiguracionP3.HuMax);
    textNumber34.setValue(ConfiguracionP3.HuMin);
    textNumber35.setValue(ConfiguracionP3.Thora);
    textNumber36.setValue(ConfiguracionP3.Tmin);
    number31 = ConfiguracionP1.TempMax;
    number32 = ConfiguracionP1.TempMin;
    number33 = ConfiguracionP1.HuMax;
    number34 = ConfiguracionP1.HuMin;
    number35 = ConfiguracionP1.Thora;
    number36 = ConfiguracionP1.Tmin;
  }
  if(ConfiguracionP4.TempMax != 0){
    textNumber41.setValue(ConfiguracionP4.TempMax);
    textNumber42.setValue(ConfiguracionP4.TempMin);
    textNumber43.setValue(ConfiguracionP4.HuMax);
    textNumber44.setValue(ConfiguracionP4.HuMin);
    textNumber45.setValue(ConfiguracionP4.Thora);
    textNumber46.setValue(ConfiguracionP4.Tmin);
    number41 = ConfiguracionP1.TempMax;
    number42 = ConfiguracionP1.TempMin;
    number43 = ConfiguracionP1.HuMax;
    number44 = ConfiguracionP1.HuMin;
    number45 = ConfiguracionP1.Thora;
    number46 = ConfiguracionP1.Tmin;
  }
}

void loop(void)
{
  nexLoop(nex_listen_list);
}

void SetConfig(Configuracion vDat,int addres,int TempMaxS,int TempMinS,int HuMaxS,int HuMinS,int ThoraS,int TminS){
    int eeAddress = addres * sizeof(Configuracion);
    vDat.TempMax = TempMaxS;
    vDat.TempMin = TempMinS;
    vDat.HuMax = HuMaxS;
    vDat.HuMin = HuMinS;
    vDat.Thora = ThoraS;
    vDat.Tmin = TminS;
    EEPROM.put( eeAddress, vDat );   
}

Configuracion GetConfiguracion(int addres){
    Configuracion customVar;
    int eeAddress = addres * sizeof(Configuracion);
    EEPROM.get( eeAddress, customVar );  
    return customVar;
}
void inicializarConfig(Configuracion vDat){
    vDat.TempMax = 0;
    vDat.TempMin = 0;
    vDat.HuMax = 0;
    vDat.HuMin = 0;
    vDat.Thora = 0;
    vDat.Tmin = 0;
}
