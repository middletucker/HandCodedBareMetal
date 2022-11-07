/*
 * Driver.c
 *
 *  Created on: Nov 28, 2021
 *      Author: kcastlet
 */

#include "Driver.h"

int LED0Used=0;
int LED1Used=0;

void setMode(LEDCONFIG *ledHandle)
{
   if (ledHandle->mode==DIM)
     {
       GPIO_PinModeSet(ledHandle->port, ledHandle->pin, gpioModeDisabled, 0);
     }
   else if (ledHandle->mode==BRIGHT)
     {
       GPIO_PinModeSet(ledHandle->port, ledHandle->pin, gpioModePushPull, 0);
     }
   else
     {
       //dimmable
     }
}

LEDERROR LED0Config_open(LEDCONFIG *ledHandle) {
  if (!LED0Used)
    {
      ledHandle->mode=DIM;
      ledHandle->port=gpioPortF;
      ledHandle->pin=4;
      ledHandle->state=HIGH;
      ledHandle->ready=1;

      return OK;

    }
  return ERROR;
}
LEDMODE  LED0Config_read(LEDCONFIG *ledHandle) {
  if (ledHandle->ready && LED0Used)
    {
      return ledHandle->mode;
    }
  return ERROR;
}
LEDERROR LED0Config_write(LEDCONFIG *ledHandle,LEDMODE value){
  if(ledHandle->ready && LED0Used)
    {
      setMode(ledHandle, value);
      return OK;
    }
  return ERROR;
}
LEDERROR LED0Config_close(LEDCONFIG *ledHandle) {
  if (LED0Used)
    {
      LED0Used=0;
      ledHandle->ready=0;
      return OK;
    }
  return ERROR;
}

LEDERROR LED0_open(LED *ledHandle)
{
  return LED0Config_open(ledHandle->config);
}
LEDSTATE LED0_read(LED *ledHandle)
{
  if (ledHandle->config.ready && LED0Used)
    {
      unsigned v=GPIO_PinOutGet(ledHandle->config.port, ledHandle->config.pin);
      if (v==0) ledHandle->config.state = LOW;
      else ledHandle->config.state = HIGH;
      return ledHandle->config.state;
    }
  return STATEERROR;
}
LEDERROR LED0_write(LED *ledHandle,LEDSTATE value){
  if (ledHandle->config.ready && LED0Used)
    {
      ledHandle->config.state = value;

      if (ledHandle->config.state == LOW)
        GPIO_PinOutClear(ledHandle->config.port, ledHandle->config.pin);
      else
        GPIO_PinOutSet(ledHandle->config.port, ledHandle->config.pin);
      return OK;
    }
return ERROR;
}
LEDERROR LED0_close(LED *ledHandle)
{
  return LED0Config_close(ledHandle->config);
}

/* Implement this set using the device hardware directly */
LEDERROR LED1Config_open(LEDCONFIG *ledHandle) {
  if (!LED1Used)
    {
      ledHandle->mode=DIM;
      ledHandle->port=gpioPortF;
      ledHandle->pin=5;
      ledHandle->state=HIGH;
      ledHandle->ready=1;

      return OK;

    }
  return ERROR;
}
LEDMODE  LED1Config_read(LEDCONFIG *ledHandle) {
  if (ledHandle->ready && LED1Used)
    {
      return ledHandle->mode;
    }
  return ERROR;
}
LEDERROR LED1Config_write(LEDCONFIG *ledHandle,LEDMODE value){
  if(ledHandle->ready && LED1Used)
    {
      setMode(ledHandle, value);
      return OK;
    }
  return ERROR;
}
LEDERROR LED1Config_close(LEDCONFIG *ledHandle) {
  if (LED1Used)
    {
      LED1Used=0;
      ledHandle->ready=0;
      return OK;
    }
  return ERROR;
}

LEDERROR LED1_open(LED *ledHandle)
{
  return LED1Config_open(ledHandle->config);
}
LEDSTATE LED1_read(LED *ledHandle)
{
  if (ledHandle->config.ready && LED1Used)
    {
      unsigned v=GPIO_PinOutGet(ledHandle->config.port, ledHandle->config.pin);
      if (v==0) ledHandle->config.state = LOW;
      else ledHandle->config.state = HIGH;
      return ledHandle->config.state;
    }
  return STATEERROR;
}
LEDERROR LED1_write(LED *ledHandle,LEDSTATE value){
  if (ledHandle->config.ready && LED1Used)
    {
      ledHandle->config.state = value;

      if (ledHandle->config.state == LOW)
        GPIO_PinOutClear(ledHandle->config.port, ledHandle->config.pin);
      else
        GPIO_PinOutSet(ledHandle->config.port, ledHandle->config.pin);
      return OK;
    }
return ERROR;
}
LEDERROR LED1_close(LED *ledHandle)
{
  return LED1Config_close(ledHandle->config);
}
