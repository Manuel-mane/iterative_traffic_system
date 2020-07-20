//Function that takes care of the two LCDs rotation message

void UpdateLCDDisplay()
{
  int iLenOfLargeText = strlen(LargeText);                                            // Calculate length of string.
  if (iCursor == (iLenOfLargeText - 1) )                                              // Reset variable for rollover effect.
  {
    iCursor = 0;
  }
  lcd1.setCursor(0,iLineNumber);
  lcd2.setCursor(0,iLineNumber);
  if(iCursor < iLenOfLargeText - 32)                                                  // This loop executed for normal 16 characters.
  {
    for (int iChar = iCursor; iChar < iCursor + 16 ; iChar++)
    {
      lcd1.print(LargeText[iChar]);
    }
    for (int iChar = iCursor + 16 ; iChar < iCursor + 32 ; iChar++)
    {
      lcd2.print(LargeText[iChar]);
    }
  }
  else
  {
      for (int iChar = iCursor; iChar < (iLenOfLargeText - 1) ; iChar++)                //  This code takes care of printing characters of current string.
      {
        if(16 > (iChar - iCursor))
        {
          lcd1.print(LargeText[iChar]);
        }
        else
        {
          lcd2.print(LargeText[iChar]);
        }
      }
      for (int iChar = 0; iChar <= 32 - (iLenOfLargeText - iCursor); iChar++)           //  Remaining characters will be printed by this loop.
      {
        
        if(16 > (32 - (iLenOfLargeText - iCursor)))
        {
          lcd2.print(LargeText[iChar]);
        }
        else
        {
          if( ((32 - (iLenOfLargeText - iCursor)) - 16) >=  iChar)
          {
            lcd1.print(LargeText[iChar]);
          }
          else
          {
            lcd2.print(LargeText[iChar]);
          }
          
        }  
      }
  }
  iCursor++;
}
