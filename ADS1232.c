#include <ADS1232.h>
#include <io.h>
#include <delay.h>

float gain;

void ads1232_init(void)
{
    // io pin configuration
    PORTB.DIR |= 0x0F;
    PORTD.DIR |= 0X02;

    ADS_GAIN_128;
    gain = 128;
    ADS_SPEED_10SPS;
}

unsigned long int ads1232_read_raw(int ch)
{
    unsigned long int raw;
    int i, j;
    // Select channel
    if (ch == ADS_CH1)
    {
        ADS_SEL_CH1;
        delay_us(50);
    }
    if (ch == ADS_CH2)
    {
        ADS_SEL_CH2;
        delay_us(50);
    }

    // start reading data
    ADS_SCK_Low;
    raw = 0;
    j = ADS_Dout_Read;

    // wait untile data ready
    while (j)
    {
        j = ADS_Dout_Read;
    }

    i = j = 0;
    for (i = 0; i < 24; i++)
    {
        ADS_SCK_High;
        delay_us(1);
        raw = raw << 1;
        ADS_SCK_Low;
        delay_us(1);
        j = ADS_Dout_Read;
        if (j)
            raw++;
    }
    ADS_SCK_High;
    delay_us(1);
    ADS_SCK_Low;
    if (raw & 0x800000)
    {

        raw = ~raw;
        raw = raw & 0x007FFFFF;
        raw *= -1;
        // volt = (float)(raw) * (-0.000298);
    }
    // else
    // {
    //     volt = (float)(raw) * (0.000298);
    // }
    // volt = (float)(volt / (float)(Gain));
    return raw;
}

float ads1232_read_mv(int ch)
{
    float mv = 0;
    mv = 0.000298 * ads1232_read_raw(ch);
    mv = (float)(mv/(float)(gain));
    return mv;
}