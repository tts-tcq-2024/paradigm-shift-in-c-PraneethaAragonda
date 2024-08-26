#include <stdio.h>
#include <assert.h>
 // declaring the fucntions 
int checkingtemp(float temp);
int checkingsoc(float soc);
int checkingcharge(float chrgRte);
int batteryIsOk(float temperature, float soc, float chargeRate) 
{
 return checkingtemp(temperature) && checkingsoc(soc) && checkingcharge(chargeRate);
}
 int checkingtemp(float temp)
{
   if (temp < 0 || temp > 45) 
   {
      printf("Temperature out of range!\n");
         return 0; 
   }

    return 1;

}
 int checkingsoc(float soc)

{
 if (soc < 20 || soc > 80) 

    {
       printf("State of Charge out of range!\n");
       return 0; 

    }
     return 1; 

}
 
int checkingcharge(float chrgRte)

{

    if (chrgRte > 0.8) 

    {

        printf("Charge Rate out of range!\n");

        return 0; 

    }

    return 1;

}
 
int main() {

    assert(batteryIsOk(25, 70, 0.7)); 

    assert(!batteryIsOk(50, 85, 0)); 

}

 
