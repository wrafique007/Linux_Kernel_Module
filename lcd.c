#include <linux/delay.h>
#include <linux/module.h>
#include "lcd.h"

void lcd_init(struct gpio_desc **gpio_ptr)
{
    char message[15]={'K','i','n','g',' ','i','s',' ','b','a','c','k','.','.','.'};

    mdelay(55);

    write_instruction(gpio_ptr);
    /* set db4 to 1*/
    gpiod_set_value(gpio_ptr[3],1);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(10);

    write_instruction(gpio_ptr);
    /* set db4 to 1*/
    gpiod_set_value(gpio_ptr[3],1);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(2);

    write_instruction(gpio_ptr);
    /* set db4 to 1*/
    gpiod_set_value(gpio_ptr[3],1);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(2);

    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    /* highest instruction execution time is 1.37ms so making delay to 5ms just to make sure that instruction would have been completed */
    mdelay(5);


/*function set command*/
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(5);
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 1*/
    gpiod_set_value(gpio_ptr[6],1);
    set_enable(gpio_ptr);
    mdelay(5);

/*set DDRAM address*/
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 0*/
    gpiod_set_value(gpio_ptr[4],0);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(5);
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 0*/
    gpiod_set_value(gpio_ptr[4],0);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 1*/
    gpiod_set_value(gpio_ptr[6],1);
    set_enable(gpio_ptr);
    mdelay(5);

/*clear display*/
    clear_display(gpio_ptr);

/*set entry mode*/
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 0*/
    gpiod_set_value(gpio_ptr[4],0);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(5);
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 1*/
    gpiod_set_value(gpio_ptr[5],1);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(5);

/*display on/off*/
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 0*/
    gpiod_set_value(gpio_ptr[4],0);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(5);
    write_instruction(gpio_ptr);
    /* set db4 to 1*/
    gpiod_set_value(gpio_ptr[3],1);
    /* set db5 to 1*/
    gpiod_set_value(gpio_ptr[4],1);
    /* set db6 to 1*/
    gpiod_set_value(gpio_ptr[5],1);
    /* set db7 to 1*/
    gpiod_set_value(gpio_ptr[6],1);
    set_enable(gpio_ptr);
    mdelay(5);
    pr_info("LCD initialization completed\n");

    write_message(gpio_ptr, &message[0], 15);
}

void write_message(struct gpio_desc **gpio_ptr, const char *buffer, int size)
{
    int i;

    clear_display(gpio_ptr);
    for (i=0;i < size-1 /* -1 is being done to avoid printing New line character*/; i++)
    {
        pr_info("buffer is %u\n", buffer[i]);
        write_data(gpio_ptr);
        gpiod_set_value(gpio_ptr[3], (buffer[i] >> 4)&(1u));
        gpiod_set_value(gpio_ptr[4], (buffer[i] >> 5)&(1u));
        gpiod_set_value(gpio_ptr[5], (buffer[i] >> 6)&(1u));
        gpiod_set_value(gpio_ptr[6], (buffer[i] >> 7)&(1u));
        set_enable(gpio_ptr);
        write_data(gpio_ptr);
        gpiod_set_value(gpio_ptr[3], (buffer[i] >> 0)&(1u));
        gpiod_set_value(gpio_ptr[4], (buffer[i] >> 1)&(1u));
        gpiod_set_value(gpio_ptr[5], (buffer[i] >> 2)&(1u));
        gpiod_set_value(gpio_ptr[6], (buffer[i] >> 3)&(1u));
        set_enable(gpio_ptr);
    }
}

void set_enable(struct gpio_desc **gpio_ptr)
{
    /* set en to 1*/
    gpiod_set_value(gpio_ptr[2],1);
    udelay(500);
    /* set en to 0*/
    gpiod_set_value(gpio_ptr[2],0);
}

void write_instruction(struct gpio_desc **gpio_ptr)
{
    /* set rs to 0*/
    gpiod_set_value(gpio_ptr[0],0);
    /* set rw to 0*/
    gpiod_set_value(gpio_ptr[1],0);
}

void write_data(struct gpio_desc **gpio_ptr)
{
    /* set rs to 1*/
    gpiod_set_value(gpio_ptr[0],1);
    /* set rw to 0*/
    gpiod_set_value(gpio_ptr[1],0);
}

void clear_display(struct gpio_desc **gpio_ptr)
{
    /*clear display*/
    write_instruction(gpio_ptr);
    /* set db4 to 0*/
    gpiod_set_value(gpio_ptr[3],0);
    /* set db5 to 0*/
    gpiod_set_value(gpio_ptr[4],0);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(5);
    write_instruction(gpio_ptr);
    /* set db4 to 1*/
    gpiod_set_value(gpio_ptr[3],1);
    /* set db5 to 0*/
    gpiod_set_value(gpio_ptr[4],0);
    /* set db6 to 0*/
    gpiod_set_value(gpio_ptr[5],0);
    /* set db7 to 0*/
    gpiod_set_value(gpio_ptr[6],0);
    set_enable(gpio_ptr);
    mdelay(5);
}