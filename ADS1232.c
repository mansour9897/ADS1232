#include <ADS1232.h>
#include <io.h>
#include <delay.h>
#include "debug.h"

float gain;

void ads1232_init(void)
{
    debug_print("ads1232_initialize...\r\n");
    // io pin configuration
    PORTB.DIR |= 0x0F;
    PORTD.DIR |= 0X02;

    // PWDN configuration
    PORTA.DIR |= 0x20;

    ADS_GAIN_128;
    gain = 128;
    ADS_SPEED_80SPS;

    ads1232_power_reset();
}

void ads1232_power_reset(void)
{
    debug_print("ads1232_power_reset...\r\n");
    CLRBIT(PORTA.OUT, 5);
    delay_ms(1500);
    SETBIT(PORTA.OUT, 5);
}

int32_t ads1232_read_raw(int ch)
{
    int32_t raw;
    uint32_t reg=0;
    reg = ads1232_read_converted_register(ch);

    if (reg & 0x800000)
    {

        reg = ~raw;
        raw = reg & 0x007FFFFF;
        raw *= -1;
    }
    return raw;
}

uint32_t ads1232_read_converted_register(int ch)
{
    uint32_t ch_raw = 0;
    int i, j;
    ads1232_select_channel(ch);
    ads1232_wait_for_data();

    i = j = 0;
    for (i = 0; i < 24; i++)
    {
        ch_raw = ch_raw << 1;
        ads1232_one_clock();
        j = ADS_Dout_Read;
        if (j)
            ch_raw++;
    }

    ads1232_one_clock();

    return ch_raw;
}

void ads1232_select_channel(int ch)
{
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
}

void ads1232_wait_for_data()
{
    int j = 0;
    ADS_SCK_Low;
    j = ADS_Dout_Read;

    // wait untile data ready
    while (j)
    {
        j = ADS_Dout_Read;
    }
}

void ads1232_one_clock(void)
{
    ADS_SCK_High;
    delay_us(1);
    ADS_SCK_Low;
    delay_us(1);
}

float ads1232_read_mv(int ch)
{
    float mv = 0;
    mv = 0.000298 * ads1232_read_raw(ch);
    mv = (float)(mv / (float)(gain));
    return mv;
}