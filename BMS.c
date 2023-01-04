#include <stdio.h>
#include <assert.h>
#include "BatteryManagmentSystem.h"

/*Macro to check the minimum and maximum value of given input*/
#define RangeCheck(Input,MinValue,MaxValue) ((Input<=MinValue || Input>=MaxValue)?0:1)

/*Minimum and Maximum Ranges*/
#define TEMPMIN	0
#define TEMPMAX 45
#define SOCMIN 20
#define SOCMAX 80
#define CHARGERATEMAX 0.8

const char* PreWarningMessageTable[Warning_max] = {"Approaching_discharge","Approaching_charge_peak"};

/*Function Delceration for BMS*/
int Check_ChargeRate(float chargeRate);

/*Function Returns True if the Battery is OK else return false*/
int batteryIsOk(float temperature, float soc, float chargeRate)
{
  int batterystate = 1;
  /*Macro returns flase if the Temperature is out of range and true if Temperature is in range*/ 
  batterystate = RangeCheck(temperature,TEMPMIN,TEMPMAX);
  /*Macro returns flase if the SOC is out of range and true if its in range*/
  batterystate *= RangeCheck(soc,SOCMIN,SOCMAX);
  batterystate *= Check_ChargeRate(chargeRate);

  return batterystate;
}
 
/*Function returns flase if the chargeRate is out of range and true if its in range*/ 
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
  //assert(ReturnWarningMessage(13) == "LOW_SOC_BREACH");
  printf("%s\n",ReturnWarningMessage(13));
  SelectLanguageandWarnigMessage(GERMAN);
  //assert(ReturnWarningMessage(77) == "HIGH_SOC_WARNUNG");
  printf("%s",ReturnWarningMessage(77));
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(23,SOCMIN,SOCMAX)] == "Approaching_discharge"); /* 5% of 80 is 4 , [20-24],[76-80] */
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(77,SOCMIN,SOCMAX)] == "Approaching_charge_peak");
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(1,TEMPMIN,TEMPMAX)] == "Approaching_discharge"); /* 5% of 45 is 2 , [0-2],[43-45] */
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(44,TEMPMIN,TEMPMAX)] == "Approaching_charge_peak");

}
