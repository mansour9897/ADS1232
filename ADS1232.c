#include <ADS1232.h>
#include <io.h>
void ads1232_init(void)
{
    //io pin configuration
    PORTB.DIR |= 0x0F;
    PORTD.DIR |= 0X02;

    ADS_GAIN_128;
    ADS_SPEED_10SPS;
}