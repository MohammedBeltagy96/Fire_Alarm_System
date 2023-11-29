

#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_

/*Return temp= c*10 */
u16 TEMP_Read(void);

u16 PRESSURE_Read(void);

u16 Interpolation(u16 x_adc ,u16 x1 ,u16 x2 ,u16 y1 ,u16 y2);
//u16 NTC_Temp (void);



#endif /* SENSORS_INTERFACE_H_ */