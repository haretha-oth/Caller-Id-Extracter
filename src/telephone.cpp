


#include <Arduino.h>
#include "telephone.h"


//flags 
int  SequenceSteps;
int  new_number;
unsigned long  tele_xtimer;

int incomingByte ;
char incomingBytes [200];
char lastCh ;
char caller_id [100] ;
int id_index ;


void TelephoneSetup()
{
  SequenceSteps = 0;
  new_number = 0;
  lastCh = 0 ;
  id_index = 0 ;
}


void TelephoneLoop()
{

     if (Serial.available() > 0)  
     {
        incomingByte = Serial.read(); 
        extractNumber(incomingByte);
   
     }

}


bool checkSequence (char b, char c1, char c2) 
{
    if(b == c2 && lastCh == c1)
    {
      return true;
    }

  lastCh = b;
  
return false;
}



void extractNumber(char b)
{
  if(SequenceSteps == 0)
    {
      if(checkSequence(b, 2, 10))
      {
        id_index = 0;
        SequenceSteps = 1;
        Serial.println("first match  ");
      }
    }
  else if(SequenceSteps == 1)
    {    
      if(id_index < 25)
      {
        caller_id[id_index++] = b;
        caller_id[id_index] = 0;
      }
      else
      {
        SequenceSteps = 2;
      }

      if(checkSequence(b, 8, 1))
      {
        Serial.println("second match  ");
        caller_id[id_index - 2] = 0;
        caller_id[id_index - 1] = 0;
        SequenceSteps = 2;
        
      }
    }  
  
  if(SequenceSteps == 2)
    {
        SequenceSteps = 0;
        new_number = 1;
        Serial.print("caller_id ");Serial.println(caller_id);
  
    }

}



void setNewNumber(int n)
{
  new_number = n;
}

bool isNewNumber () 
{
    if(new_number>0)
    {
      return true;
    }
    else
    {
      return false;
    }
}

String getNewNumber()
{
    return String(caller_id);
}


