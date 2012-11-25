#include "linux/init.h"
#include "linux/module.h"

#include "linux/err.h"
#include "linux/kernel.h"
#include "linux/platform_device.h"
#include "mach/gpio.h"
#include "plat/gpio-cfg.h"
#include "mach/board-gps.h"
#include "linux/sysfs.h"


MODULE_LICENSE("Dual BSD/GPL");

#define GPIO_GPS_PWR_EN_NTT            EXYNOS4210_GPE2(3)
#define GPIO_GPS_PWR_EN   EXYNOS4210_GPE0(3)
static struct device *gps_dev;

static void gps_ntt_exit(void)
{
    printk(KERN_ALERT "NTT gps fix module exit\n");
}

int gps_ntt_init(void)
{

    struct class_dev_iter iter;
    class_dev_iter_init(&iter, sec_class, NULL, NULL);
    while ((gps_dev = class_dev_iter_next(&iter)))
    {
       if(strcmp(gps_dev->kobj.name,"gps")==0)
         break;
    }
    class_dev_iter_exit(&iter);
    if(gps_dev==NULL)
      return 0;

    s3c_gpio_cfgpin(GPIO_GPS_PWR_EN, S3C_GPIO_SLP_INPUT);
    s3c_gpio_setpull(GPIO_GPS_PWR_EN, S3C_GPIO_PULL_DOWN);
    gpio_unexport(GPIO_GPS_PWR_EN);
    gpio_free(GPIO_GPS_PWR_EN);
    
    if (gpio_request(GPIO_GPS_PWR_EN_NTT, "GPS_PWR_EN"))
          WARN(1, "fail to request gpio (GPS_PWR_EN)\n");
    s3c_gpio_setpull(GPIO_GPS_PWR_EN_NTT, S3C_GPIO_PULL_NONE);
    s3c_gpio_cfgpin(GPIO_GPS_PWR_EN_NTT, S3C_GPIO_OUTPUT);
    gpio_direction_output(GPIO_GPS_PWR_EN_NTT, 0);
    gpio_export(GPIO_GPS_PWR_EN_NTT, 1);
    sysfs_remove_link(&gps_dev->kobj,"GPS_PWR_EN");
    gpio_export_link(gps_dev, "GPS_PWR_EN", GPIO_GPS_PWR_EN_NTT);

    return 0;

}

module_init(gps_ntt_init);
module_exit(gps_ntt_exit);
