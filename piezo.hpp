#ifndef PIEZO_HPP
#define PIEZO_HPP

#define PIEZO_NOTE_ON 1
#define PIEZO_NOTE_OFF 2

class piezo{
  unsigned int counter;
  unsigned int timeThresh;
  unsigned int levelThresh;
  unsigned int pin;
  bool noteState;
  
  public:
  piezo()
  :counter(0), timeThresh(1000), levelThresh(200)
  {
    
  }

  piezo(unsigned int analogPin)
  :counter(0), timeThresh(1000), levelThresh(300),
  pin(analogPin), noteState(false)
  {
    
  }


  uint8_t next()
  {
    if(counter > timeThresh)
    {
      if((analogRead(pin) > levelThresh) && (noteState == false))
      {
        counter = 0;
        noteState = true;
        return PIEZO_NOTE_ON;
      }
      else if(noteState == true)
      {
        noteState = false;

        return PIEZO_NOTE_OFF;
      }
    }
    else
    {
      counter++;
    }
    return 0;
  }
};

#endif
