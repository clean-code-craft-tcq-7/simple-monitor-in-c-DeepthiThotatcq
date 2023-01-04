#include "BMS.h"

const char* Store_WarningMessage[MESSAGE_MAX];

const char* WarningMessageTable[MAX_LANG][MESSAGE_MAX] = {
		{/*Language : DEFAULT */
			"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"},
		{/*Language : ENGLISH */
			"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"},
		{/*Language : GERMAN */
			"LOW_SOC_BREACH","LOW_SOC_WARNUNG","SOC_NORMAL","HIGH_SOC_WARNUNG","HIGH_SOC_BREACH","SOC_UNDEFINED"}
	};

void SelectLanguageandWarnigMessage(Select_Language Language)
{   
   if(Language < MAX_LANG)
   {
      for(int i =0;i<MESSAGE_MAX;i++)
      {
      	Store_WarningMessage[i] = WarningMessageTable[Language][i];
      }
    } 
}

const char* ReturnWarningMessage(int soc)
{
   return Store_WarningMessage[(BatteryHelathMonitor(soc))];
}
