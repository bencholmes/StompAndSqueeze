#ifndef FSR_HPP
#define FSR_HPP

#define FSR_NOTE_ON 1
#define FSR_NOTE_OFF 2

class fsr {
    bool state;
    uint8_t output;
    unsigned int counter;
    unsigned int pin;
    unsigned int levelThresh;
    unsigned int timeThresh;

  public:
    fsr()
    : state(false), counter(0), levelThresh(200),
    timeThresh(50)
    {
      ;
    }

    fsr(unsigned int analogPin)
      : state(false), counter(0), pin(analogPin), levelThresh(200),
    timeThresh(50)
    {
      ;
    }

    ~fsr()
    {
      ;
    }

    uint8_t next()
    {
      if (counter > timeThresh)
      {
        if ( (analogRead(pin) > levelThresh) && (!state) )
        {
          state = true;
          counter = 0;
          
          return FSR_NOTE_ON;
        }
        else if ( (analogRead(pin) < levelThresh) && state )
        {
          state = false;
          counter = 0;
          
          return FSR_NOTE_OFF;
        }
      }

      counter++;
      return 0;
    }
};

#endif
