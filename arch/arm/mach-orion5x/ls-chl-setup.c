/*
 * arch/arm/mach-orion5x/ls-chl-setup.c
 *
 * Maintainer: Ash Hughes <ashley.hughes@blueyonder.co.uk>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mtd/physmap.h>
#include <linux/mv643xx_eth.h>
#include <linux/leds.h>
#include <linux/gpio_keys.h>
#include <linux/gpio-fan.h>
#include <linux/input.h>
#include <linux/i2c.h>
#include <linux/ata_platform.h>
#include <linux/gpio.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/orion5x.h>
#include "common.h"
#include "mpp.h"



#define LSCHL_NOR_BOOT_BASE	0xf4000000
#define LSCHL_NOR_BOOT_SIZE	SZ_256K


static struct physmap_flash_data lschl_nor_flash_data = {
	.width = 1,
};

static struct resource lschl_nor_flash_resource = {
	.flags	= IORESOURCE_MEM,
	.start	= LSCHL_NOR_BOOT_BASE,
	.end	= LSCHL_NOR_BOOT_BASE + LSCHL_NOR_BOOT_SIZE - 1,
};

static struct platform_device lschl_nor_flash = {
	.name = "physmap-flash",
	.id = 0,
	.dev = {
		.platform_data	= &lschl_nor_flash_data,
	},
	.num_resources = 1,
	.resource = &lschl_nor_flash_resource,
};


static struct mv643xx_eth_platform_data lschl_eth_data = {
	.phy_addr = MV643XX_ETH_PHY_ADDR(8),
};


static struct i2c_board_info __initdata lschl_i2c_rtc = {
	I2C_BOARD_INFO("rs5c372a", 0x32),
};


#define LSCHL_GPIO_LED_ALARM	2
#define LSCHL_GPIO_LED_INFO	3
#define LSCHL_GPIO_LED_FUNC	17
#define LSCHL_GPIO_LED_PWR	0

static struct gpio_led lschl_led_pins[] = {
	{
		.name = "alarm:red",
		.gpio = LSCHL_GPIO_LED_ALARM,
		.active_low = 1,
	}, {
		.name = "info:amber",
		.gpio = LSCHL_GPIO_LED_INFO,
		.active_low = 1,
	}, {
		.name = "func:blue:top",
		.gpio = LSCHL_GPIO_LED_FUNC,
		.active_low = 1,
	}, {
		.name = "power:blue:bottom",
		.gpio = LSCHL_GPIO_LED_PWR,
	},
};

static struct gpio_led_platform_data lschl_led_data = {
	.leds = lschl_led_pins,
	.num_leds = ARRAY_SIZE(lschl_led_pins),
};

static struct platform_device lschl_leds = {
	.name = "leds-gpio",
	.id = -1,
	.dev = {
		.platform_data = &lschl_led_data,
	},
};

static struct mv_sata_platform_data lschl_sata_data = {
	.n_ports = 2,
};


static void lschl_power_off(void)
{
	orion5x_restart('h', NULL);
}

#define LSCHL_GPIO_USB_POWER	9
#define LSCHL_GPIO_AUTO_POWER	17
#define LSCHL_GPIO_POWER	18

#define LSCHL_GPIO_KEY_FUNC		15
#define LSCHL_GPIO_KEY_POWER		8
#define LSCHL_GPIO_KEY_AUTOPOWER	10
#define LSCHL_SW_POWER		0x00
#define LSCHL_SW_AUTOPOWER	0x01
#define LSCHL_SW_FUNC		0x02

static struct gpio_keys_button lschl_buttons[] = {
	{
		.type = EV_SW,
		.code = LSCHL_SW_POWER,
		.gpio = LSCHL_GPIO_KEY_POWER,
		.desc = "Power-on Switch",
		.active_low = 1,
	}, {
		.type = EV_SW,
		.code = LSCHL_SW_AUTOPOWER,
		.gpio = LSCHL_GPIO_KEY_AUTOPOWER,
		.desc = "Power-auto Switch",
		.active_low = 1,
	}, {
		.type = EV_SW,
		.code = LSCHL_SW_FUNC,
		.gpio = LSCHL_GPIO_KEY_FUNC,
		.desc = "Function Switch",
		.active_low = 1,
	},
};

static struct gpio_keys_platform_data lschl_button_data = {
	.buttons = lschl_buttons,
	.nbuttons = ARRAY_SIZE(lschl_buttons),
};

static struct platform_device lschl_button_device = {
	.name = "gpio-keys",
	.id = -1,
	.num_resources = 0,
	.dev = {
		.platform_data = &lschl_button_data,
	},
};

#define LSCHL_GPIO_HDD_POWER	1


#define LSCHL_GPIO_FAN_LOW	16
#define LSCHL_GPIO_FAN_HIGH	14
#define LSCHL_GPIO_FAN_LOCK	6

static struct gpio_fan_alarm lschl_alarm = {
	.gpio = LSCHL_GPIO_FAN_LOCK,
};

static struct gpio_fan_speed lschl_speeds[] = {
	{
		.rpm = 0,
		.ctrl_val = 3,
	}, {
		.rpm = 1500,
		.ctrl_val = 2,
	}, {
		.rpm = 3250,
		.ctrl_val = 1,
	}, {
		.rpm = 5000,
		.ctrl_val = 0,
	},
};

static int lschl_gpio_list[] = {
	LSCHL_GPIO_FAN_HIGH, LSCHL_GPIO_FAN_LOW,
};

static struct gpio_fan_platform_data lschl_fan_data = {
	.num_ctrl = ARRAY_SIZE(lschl_gpio_list),
	.ctrl = lschl_gpio_list,
	.alarm = &lschl_alarm,
	.num_speed = ARRAY_SIZE(lschl_speeds),
	.speed = lschl_speeds,
};

static struct platform_device lschl_fan_device = {
	.name = "gpio-fan",
	.id = -1,
	.num_resources = 0,
	.dev = {
		.platform_data = &lschl_fan_data,
	},
};


static unsigned int lschl_mpp_modes[] __initdata = {
	MPP0_GPIO, 
	MPP1_GPIO, 
	MPP2_GPIO, 
	MPP3_GPIO, 
	MPP4_UNUSED,
	MPP5_UNUSED,
	MPP6_GPIO, 
	MPP7_GPIO, 
	MPP8_GPIO, 
	MPP9_GPIO, 
	MPP10_GPIO, 
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_GPIO, 
	MPP15_GPIO, 
	MPP16_GPIO, 
	MPP17_GPIO, 
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
};

static void __init lschl_init(void)
{
	orion5x_init();

	orion5x_mpp_conf(lschl_mpp_modes);

	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&lschl_eth_data);
	orion5x_i2c_init();
	orion5x_sata_init(&lschl_sata_data);
	orion5x_uart0_init();
	orion5x_xor_init();

	orion5x_setup_dev_boot_win(LSCHL_NOR_BOOT_BASE,
				   LSCHL_NOR_BOOT_SIZE);
	platform_device_register(&lschl_nor_flash);

	platform_device_register(&lschl_leds);

	platform_device_register(&lschl_button_device);

	platform_device_register(&lschl_fan_device);

	i2c_register_board_info(0, &lschl_i2c_rtc, 1);

	
	gpio_set_value(LSCHL_GPIO_USB_POWER, 1);

	
	pm_power_off = lschl_power_off;

	pr_info("%s: finished\n", __func__);
}

MACHINE_START(LINKSTATION_LSCHL, "Buffalo Linkstation LiveV3 (LS-CHL)")
	
	.atag_offset	= 0x100,
	.init_machine	= lschl_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.timer		= &orion5x_timer,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
