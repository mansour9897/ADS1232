#ifndef _ads1232_included_

#include <iobits.h>

#define ADS_SCK_Low     CLRBIT(PORTD.OUT,1);
#define ADS_SCK_High    SETBIT(PORTD.OUT,1);
#define ADS_Dout_Read   TSTBIT(PORTD.IN,0);
#define ADS_SEL_CH1     CLRBIT(PORTB.OUT,0);
#define ADS_SEL_CH2     SETBIT(PORTB.OUT,0);
#define ADS_GAIN_1      CLRBIT(PORTB.OUT,2);CLRBIT(PORTB.OUT,3); 
#define ADS_GAIN_2      SETBIT(PORTB.OUT,2);CLRBIT(PORTB.OUT,3);
#define ADS_GAIN_64     CLRBIT(PORTB.OUT,2);SETBIT(PORTB.OUT,3);
#define ADS_GAIN_128    SETBIT(PORTB.OUT,2);SETBIT(PORTB.OUT,3);
#define ADS_SPEED_10SPS CLRBIT(PORTB.OUT,1);
#define ADS_SPEED_80SPS SETBIT(PORTB.OUT,1);

#define ADS_CH1 1
#define ADS_CH2 2

void ads1232_init(void);
unsigned long int ads1232_read_raw(int ch);
float ads1232_read_mv(int ch);
void ads1232_power_reset(void);
void ads1232_select_channel(int ch);
#endif