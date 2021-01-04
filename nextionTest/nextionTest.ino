#include <Nextion.h>
#include <doxygen.h>
#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include <Nextion.h>
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>
#include <NexWaveform.h>


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


// Declare a text object [page id:0,component id:22, component name: "nehuen2"].
NexNumber textNumber = NexNumber(0, 22, "x0");

// Declare a button object [page id:0,component id:9, component name: "nehuen3"].
NexButton buttonPlus = NexButton(0, 8, "b3");

// Declare a button object [page id:0,component id:8, component name: "nehuen1"].
NexButton buttonMinus = NexButton(0, 9, "b2");

int number = 300;
char buffer[10] = {0};


/*
   Register object textNumber, buttonPlus, buttonMinus, to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  &textNumber,
  &buttonPlus,
  &buttonMinus,
  NULL
};



/*
   Button0 component pop callback function.
   In this example,the value of the text component will plus one every time when button0 is released.
*/
void buttonPlusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlusPushCallback");

  if (number < 700) number += 1;

  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number, buffer, 10);
  textNumber.setValue(buffer);
}

/*
   Button1 component push callback function.
   In this example,the value of the text component will minus one every time when button1 is pressed.
*/
void buttonMinusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinusPushCallback");

  if (number > 0) number -= 1;
 
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number, buffer, 10);
  textNumber.setValue(buffer);
}

void setup(void)
{
  Serial.begin(9600);
  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();

  /* Register the pop event callback function of the current button0 component. */
  buttonPlus.attachPush(buttonPlusPushCallback);

  /* Register the pop event callback function of the current button1 component. */
  buttonMinus.attachPush(buttonMinusPushCallback);

  dbSerialPrintln("Setup done");
}

void loop(void)
{
  nexLoop(nex_listen_list);
}
