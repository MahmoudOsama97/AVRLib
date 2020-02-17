//#include "../micro_config.h"
//#include "../std_types.h"
//#include "../mcal/macros/common_macros.h"
//#include "../mcal/pwm/pwm.h"
//
//int main(){
//	PWM_init();
//
//while(1){
//	unsigned char duty;
//		while(1)
//		{
//			for(duty = 0 ; duty < 255 ; duty++)
//			{
//				/*increase the LED light intensity*/
//				PWM0_set_duty(duty);
//				_delay_ms(10);
//			}
//			_delay_ms(100);
//			for(duty = 255 ; duty > 0 ; duty--)
//			{
//				/*decrease the LED light intensity*/
//				PWM0_set_duty(duty);
//				_delay_ms(10);
//			}
//		}
//	}
//}
