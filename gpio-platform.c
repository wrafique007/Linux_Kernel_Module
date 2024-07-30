#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/of.h>
#include <linux/gpio/consumer.h>
#include <linux/delay.h>
#include "lcd.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Waleed");
MODULE_INFO(description, "This is a LCD driver");

#undef pr_fmt
#define pr_fmt(fmt) "%s :"fmt, __func__

struct class *lcd_class;
struct device *lcd_device;

struct gpio_descriptors{
    struct gpio_desc *gpiod_array[7];
};
struct gpio_descriptors gpiod_s;

ssize_t message_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    write_message(gpiod_s.gpiod_array,buf,count);

    return count;
}

/* Global data start */
DEVICE_ATTR_WO(message);

struct attribute *lcd_attributes[] =
{
    &dev_attr_message.attr,
    NULL
};

struct attribute_group lcd_group_attriute =
{
    .attrs = lcd_attributes,
};

const struct attribute_group *lcd_group_attriute_ptrs[] =
{
    &lcd_group_attriute,
    NULL
};

struct of_device_id of_device_array[] =
{
    {.compatible = "waleed,bone-lcd"},
    {}
};
/* Global data end */

int lcd_probe(struct platform_device *pdev)
{
    int ret,y;
    struct device_node *dev_node = pdev->dev.of_node;
    dev_info(&pdev->dev,"probe enterted\n");

    gpiod_s.gpiod_array[0] = fwnode_get_named_gpiod(&dev_node->fwnode,"rs-gpio",0,GPIOD_ASIS,"rs-gpios");
    gpiod_s.gpiod_array[1] = fwnode_get_named_gpiod(&dev_node->fwnode,"rw-gpio",0,GPIOD_ASIS,"rw-gpios");
    gpiod_s.gpiod_array[2] = fwnode_get_named_gpiod(&dev_node->fwnode,"en-gpio",0,GPIOD_ASIS,"en-gpios");
    gpiod_s.gpiod_array[3] = fwnode_get_named_gpiod(&dev_node->fwnode,"db4-gpio",0,GPIOD_ASIS,"db4-gpios");
    gpiod_s.gpiod_array[4] = fwnode_get_named_gpiod(&dev_node->fwnode,"db5-gpio",0,GPIOD_ASIS,"db5-gpios");
    gpiod_s.gpiod_array[5] = fwnode_get_named_gpiod(&dev_node->fwnode,"db6-gpio",0,GPIOD_ASIS,"db6-gpios");
    gpiod_s.gpiod_array[6] = fwnode_get_named_gpiod(&dev_node->fwnode,"db7-gpio",0,GPIOD_ASIS,"db7-gpios");
    if( IS_ERR(gpiod_s.gpiod_array[0]) ||
        IS_ERR(gpiod_s.gpiod_array[1]) ||
        IS_ERR(gpiod_s.gpiod_array[2]) ||
        IS_ERR(gpiod_s.gpiod_array[3]) ||
        IS_ERR(gpiod_s.gpiod_array[4]) ||
        IS_ERR(gpiod_s.gpiod_array[5]) ||
        IS_ERR(gpiod_s.gpiod_array[6]) )
    {
        dev_info(&pdev->dev,"error found in getting gpio descriptor\n");
        return PTR_ERR(gpiod_s.gpiod_array[0]);
    }

    for (y = 0; y < 7 ;y++)
    {
        ret = gpiod_direction_output_raw(gpiod_s.gpiod_array[y],1);
        if (ret)
        {
            dev_info(&pdev->dev,"error while setting direction\n");
            return ret;
        }
    }

    lcd_init(gpiod_s.gpiod_array);

    lcd_device = device_create_with_groups(lcd_class,NULL,0,NULL,lcd_group_attriute_ptrs,"message_to_be_written");
    
    return 0;
}

int lcd_remove(struct platform_device *pdev)
{
    device_unregister(lcd_device);
    pr_info("LCD device removed\n");
    return 0;
}

struct platform_driver  lcd_platform_driver =
{
    .probe = lcd_probe,
    .remove = lcd_remove,
    .driver =
    {
        .name = "gpio_platform_drv",
        .of_match_table = of_match_ptr(of_device_array)
    },
    .driver.owner = THIS_MODULE
};

int __init lcddrv_init(void)
{
    int err;

    /* Create gpio class */
    lcd_class = class_create(THIS_MODULE, "lcd_class");
    if (IS_ERR(lcd_class))
    {
        pr_err("could not create class\n");
        return PTR_ERR(lcd_class);
    }

    /* Register the platform driver */
    err = platform_driver_register(&lcd_platform_driver);
    if(err < 0)
    {
        pr_err("unable to register gpio platform driver\n");
        class_destroy(lcd_class);
        return err;
    }

    pr_info("LCD platform driver initialized\n");
    return 0;
}

void __exit lcd_cleanup(void)
{
    /* Unregister the platform driver */
    platform_driver_unregister(&lcd_platform_driver);

    /* Destroy the gpio class */
    class_destroy(lcd_class);

    pr_info("LCD platform driver cleaned\n");
}

module_init(lcddrv_init);
module_exit(lcd_cleanup);