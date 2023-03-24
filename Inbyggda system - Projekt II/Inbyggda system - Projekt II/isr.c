/********************************************************************************
* isr.c: Innehåller avbrottsrutiner.
********************************************************************************/
#include "header.h"

ISR (PCINT0_vect)
{
	disable_pin_change_interrupt(IO_PORTB);
	timer_enable_interrupt(&timer0);              // Sätt på avbrott på timer0.
	
	if (button_is_pressed(&button1))             // Om BUTTON1 är nedtryckt, toggla display count.
	{
		display_toggle_count();
	}
	else if(button_is_pressed(&button2))         // Annars om BUTTON2 är nedtryckt, toggla count direction.
	{
		display_toggle_count_direction();         
	}
	else if(button_is_pressed(&button3))         // Annars om BUTTON3 är nedtryckt, toggla output.
	{
		display_toggle_output();
	}
	return;
}

ISR (TIMER0_OVF_vect)
{
	timer_count(&timer0);
	
	if(timer_elapsed(&timer0))                   // När timer0 har löpt åt, återaktivera PCI-avbrott och stäng av timern.
	{
		timer_disable_interrupt(&timer0);
		enable_pin_change_interrupt(IO_PORTB);
	}
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect): Avbrottsrutin som äger rum vid uppräkning till 256 av
*                          Timer 1 i CTC Mode, vilket sker var 0.128:e
*                          millisekund när timern är aktiverad. En gång per
*                          millisekund togglas talet utskrivet på 
*                          7-segmentsdisplayerna mellan tiotal och ental.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
   display_toggle_digit();
   return;
}

/********************************************************************************
* ISR (TIMER2_OVF_vect): Avbrottsrutin som äger rum vid uppräkning till 256 av
*                        Timer 2 i Normal Mode, vilket sker var 0.128:e
*                        millisekund när timern är aktiverad. En gång per sekund
*                        inkrementeras talet utskrivet på 7-segmentsdisplayerna.
********************************************************************************/
ISR (TIMER2_OVF_vect)
{
   display_count();
   return;
}
