#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);

static struct etimer hello_timer;
static struct etimer led_timer;
static uint8_t counter;

PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  counter = 0;

  etimer_set(&hello_timer, CLOCK_SECOND * 10);
  etimer_set(&led_timer, CLOCK_SECOND / 2);

  while (1)
  {
    PROCESS_YIELD();

    if (ev == PROCESS_EVENT_TIMER && data == &hello_timer)
    {
      printf("Hello, world and Jawad\n");
      etimer_reset(&hello_timer);
    }

    if (ev == PROCESS_EVENT_TIMER && data == &led_timer)
    {
       if (leds_get() == LEDS_RED)
    {
      leds_set(LEDS_GREEN);
    }
    else if (leds_get() == LEDS_GREEN)
    {
      leds_set(LEDS_YELLOW);
    }
    else
    {
      leds_set(LEDS_RED);
    }

      counter++;
      etimer_reset(&led_timer);
    }
  }

  PROCESS_END();
}
