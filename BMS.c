#include <stdio.h>
#include <assert.h>
#include "BMS.h"

#define RangeCheck(Input,MinValue,MaxValue) ((Input<=MinValue || Input>=MaxValue)?0:1)

#define TEMPMIN	0
#define TEMPMAX 45
#define SOCMIN 20
#define SOCMAX 80
#define CHARGERATEMAX 0.8

const char* PreWarningMessageTable[Warning_max] = {"Approaching_discharge","Approaching_charge_peak"};

int Check_ChargeRate(float chargeRate);

int batteryIsOk(float temperature, float soc, float chargeRate)
{
  int batterystate = 1;
  batterystate = RangeCheck(temperature,TEMPMIN,TEMPMAX);
  batterystate *= RangeCheck(soc,SOCMIN,SOCMAX);
  batterystate *= Check_ChargeRate(chargeRate);

  return batterystate;
}
 
int Check_ChargeRate(float chargeRate)
{
   if(chargeRate > CHARGERATEMAX)
   return 0;
   else
   return 1;
}

int main()
{
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
  assert(batteryIsOk(44, 79, 0.7));
  assert(!batteryIsOk(46, 81, 0.8));
  assert(!batteryIsOk(0, 0, 0.7));
  SelectLanguageandWarnigMessage(DEFAULT);
  printf("%s\n",ReturnWarningMessage(13));
  SelectLanguageandWarnigMessage(GERMAN);
  printf("%s",ReturnWarningMessage(77));
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(23,SOCMIN,SOCMAX)] == "Approaching_discharge");
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(77,SOCMIN,SOCMAX)] == "Approaching_charge_peak");
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(1,TEMPMIN,TEMPMAX)] == "Approaching_discharge"); 
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(44,TEMPMIN,TEMPMAX)] == "Approaching_charge_peak");
}
