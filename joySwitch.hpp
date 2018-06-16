#ifndef JOYSWITCH_HPP
#define JOYSWITCH_HPP

// Switch class for joystick
class joySwitch
{
  private:
    unsigned int counter;
    unsigned int thresh;
    unsigned int pin;

  public:

    // Constructor
    joySwitch (unsigned int digitalPin)
      : counter(0), thresh(2000), pin(digitalPin)
    {

    }

    joySwitch (): counter(0), thresh(2000), pin(1)
    {

    }

    // Destructor
    ~joySwitch ()
    {

    }

    bool next()
    {
      if (counter > thresh)
      {
        if (digitalRead(pin) == LOW)
        {
          counter = 0;
          
          return true;
          
        }
      }

      counter++;
      return false;
    }
};

#endif
