#include "contiki.h"
#include "dev/leds.h"
#include "sys/etimer.h"

#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
PROCESS(led_blink_process, "LED Blink process");
AUTOSTART_PROCESSES(&hello_world_process, &led_blink_process);
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(hello_world_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 10);

  while (1)
  {
    printf("Hello, world and jawad \n");

    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(led_blink_process, ev, data)
{
  static struct etimer led_timer;

  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 2 seconds for LED blinking. */
  etimer_set(&led_timer, CLOCK_SECOND * 2);

  while (1)
  {
    /* Wait for the LED blinking timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&led_timer));

    /* Toggle between red, green, and blue LEDs. */
    if (leds_get() == LEDS_RED)
    {
      leds_set(LEDS_GREEN);
    }
    else if (leds_get() == LEDS_GREEN)
    {
      leds_set(LEDS_BLUE);
    }
    else
    {
      leds_set(LEDS_RED);
    }

    /* Restart the LED blinking timer. */
    etimer_reset(&led_timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
