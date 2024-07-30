#ifndef __LCD__
#define __LCD__

#include <linux/gpio/consumer.h>
#include <linux/kernel.h>

void lcd_init(struct gpio_desc **);
void write_message(struct gpio_desc **, const char *, int);
void set_enable(struct gpio_desc **);
void write_instruction(struct gpio_desc **);
void write_data(struct gpio_desc **);
void clear_display(struct gpio_desc **);


#endif /* __LCD__ */