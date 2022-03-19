
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


//static absolute_time_t get_absolute_time(void);





// void gpio_callback_high(uint gpio, uint32_t events) {
//     // Put the GPIO event(s) that just happened into event_str
//     // so we can print it
//     //gpio_event_string(event_str, events);
//     // gpio_set_irq_enabled(2, GPIO_IRQ_EDGE_RISE, false);
//     //  printf("GPIO %d %s\n", gpio, event_str);
//     printf("\nTriggered HIGH");
//     //   memset(event_str,0,sizeof(event_str));
//     // if(event_str==gpio_irq_str[2] || event_str==gpio_irq_str[3])
//     // {
//     //     printf("triggered gpio %d %s\n", gpio, event_str); 
//     // }
//     // else if (event_str=="EDGE_FALL")
//     // {
//     //     printf("GPIO %d %s\n", gpio, event_str); 
//     // }
    
// }

//unsigned long interrupt_time = 0;


// void gpio_callback_job(uint gpio, uint32_t events) {
//     // gpio_set_irq_enabled(2, GPIO_IRQ_EDGE_FALL, false);
//     unsigned long last_interrupt_time = get_absolute_time();
//     unsigned long interrupt_time = get_absolute_time();

//     gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_RISE, false);
//     while (interrupt_time - last_interrupt_time <900)
//     {
//         interrupt_time = get_absolute_time();
//     }
//     printf("\nJOB %ld",interrupt_time - last_interrupt_time);
//          if (gpio_get(gpio)==1)
//     {
//         printf("\nTriggered job high");
//     }
//     gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_RISE, true);

// }

void gpio_callback(uint gpio, uint32_t events) 
{
  unsigned long last_interrupt_time = to_us_since_boot(get_absolute_time());
  unsigned long interrupt_time = to_us_since_boot(get_absolute_time());
   //printf("\n % ld ",interrupt_time );
   //printf("\nBUTTONREAD");
//   printf("\n % ld ",last_interrupt_time );
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if(gpio==4){
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, false);
//   if (interrupt_time - last_interrupt_time > 150) 
//   {
    //  printf("\n % ld ",interrupt_time );
    // for (int i=0; i<600; i++)
    // {
    //     for (int j=0; j<3275; j++)
    //     {}
    // }
    // // interrupt_time = get_absolute_time();
    // interrupt_time = to_us_since_boot(get_absolute_time());
    // printf("\n % ld ",interrupt_time );
    // sleep_ms(300);

    while (interrupt_time - last_interrupt_time <1000)
    {
        interrupt_time = to_us_since_boot(get_absolute_time());
    }
    //printf("\nCYC %ld",interrupt_time - last_interrupt_time);
    if (gpio_get(gpio)==0)
    {
        printf("\nCYCLE Triggered low");
    }
    else{
        printf("\nCYCLE Triggered high %ld",gpio_get(gpio));
    }
    
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, true);

  }
    if(gpio==2){
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_RISE, false);
    while (interrupt_time - last_interrupt_time <1000)
    {
        interrupt_time = to_us_since_boot(get_absolute_time());
    }
    //printf("\nJOB %ld",interrupt_time - last_interrupt_time);
         if (gpio_get(gpio)==1)
    {
        printf("\nTriggered job high");
    }
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_RISE, true);
    }
    // last_interrupt_time = interrupt_time;
  //}
   //last_interrupt_time = interrupt_time;
}


int main() {
    stdio_init_all();
    gpio_set_dir(2, GPIO_IN);
    gpio_set_dir(4, GPIO_IN);
    printf("Hello GPIO IRQ\n");
    gpio_set_irq_enabled_with_callback(4, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, true, &gpio_callback); //CYCLE
    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);  //JOB
    // gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_FALL, true, &gpio_callback_low);
     sleep_ms(1000);
    // Wait forever
    while (1);

    return 0;
}


