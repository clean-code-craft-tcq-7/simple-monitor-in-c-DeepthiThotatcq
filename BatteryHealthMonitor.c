#include "BMS.h"

#define TOLERENCEVALUE 5
#define SocBreachMin 20
#define SocBreachMax 81
#define SocWarningMin 24
#define SocWarningMax 76

#define RangeChecker(X,Y,Z) (X<=Y && X>=Z)?1:0

struct 
{
	int DrainRange;
	int PeakRange;
}descharge_range;

static WarningRanges ReturnSocBreach(int soc);
static WarningRanges ReturnSocWarning(int soc);
static int SocRangeCheck(int soc, int MinRange, int MaxRange);
static void CalculateDrianPeakThreshold(int MinThreshold , int MaxThreshold);

static int SocRangeCheck(int soc, int MinRange, int MaxRange)
{
	if(soc <= MinRange)
	{
		return 1;
	}
	else if(soc>=MaxRange)
	{
		return 0;
	}	
}

static void CalculateDrianPeakThreshold(int MinThreshold , int MaxThreshold)
{
    int Value = (int)((TOLERENCEVALUE*MaxThreshold)/100);
    
     descharge_range.DrainRange = MinThreshold + Value;
     descharge_range.PeakRange  = MaxThreshold - Value;
}

WarningWithTolerance PreWarningIndicatorMessage(int input, int MinThreshold , int MaxThreshold )
{   

    CalculateDrianPeakThreshold(MinThreshold , MaxThreshold);
	
    if(input <= descharge_range.DrainRange)	    
    {
        return Approaching_Discharge;
    }
 
    if( input>= descharge_range.PeakRange)
    {
        return Approaching_Peak;
    }
}

WarningRanges BatteryHelathMonitor(int soc)
{  
    if(RangeChecker(soc, SocBreachMax, (SocBreachMin+1)) == 1)
	{
		return ReturnSocWarning(soc);
	}
	else
	{
		return ReturnSocBreach(soc);
	}
}


static WarningRanges ReturnSocBreach(int soc)
{
	 
	if(SocRangeCheck(soc, SocBreachMin, SocBreachMax) == 1)
	{
		return LOW_SOC_BREACH;
	}
	else
	{
		return HIGH_SOC_BREACH;
	}	
}

static WarningRanges ReturnSocWarning(int soc)
{
	
	WarningRanges Returnstaus = SOC_NORMAL;
	
	if(SocRangeCheck(soc, SocWarningMin, SocWarningMax) == 1)
	{
		Returnstaus = LOW_SOC_WARNING;
	}
	else
	{
		Returnstaus = HIGH_SOC_WARNING;
	}
	
	return Returnstaus;	
}
