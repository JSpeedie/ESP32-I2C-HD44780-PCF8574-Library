#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "driver/i2c_master.h"

/* Component includes */
#include "esp32-i2c-hd44780-pcf8574.h"


#define I2C_BUS_PORT 0
/* Going off  https://learn.adafruit.com/assets/111179 */
#define I2C_SDA_PIN_NUM 23
#define I2C_SCL_PIN_NUM 22


void app_main(void)
{
	/* I2C Device Configuration {{{ */
	/* 1. Configure the i2c master bus */
	i2c_master_bus_config_t i2c_mst_config = {
		.clk_source = I2C_CLK_SRC_DEFAULT,
		.i2c_port = I2C_BUS_PORT,
		.scl_io_num = I2C_SCL_PIN_NUM,
		.sda_io_num = I2C_SDA_PIN_NUM,
		.glitch_ignore_cnt = 7,
		.flags.enable_internal_pullup = false,
	};

	i2c_master_bus_handle_t bus_handle;
	ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

	/* 2. Configure the i2c LCD peripheral */
	i2c_device_config_t dev_cfg = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = 0x27,
		.scl_speed_hz = 100000,
	};

	i2c_master_dev_handle_t lcd_handle;
	ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &lcd_handle));
	/* }}} */

	/* printf("probing for i2c device..."); */
	/* ESP_ERROR_CHECK(i2c_master_probe(bus_handle, 0x27, -1)); */
	/* printf(" SUCCESS!\n"); */

	/* 3a. Perform device specific initialization */
	struct esp_i2c_hd44780_pcf8574 i2c_lcd = \
		esp_i2c_hd44780_pcf8574_init(16, 2, -1, LCD_BACKLIGHT);
	i2c_lcd.i2c_handle = &lcd_handle;

	/* 3b. Perform the necessary startup instructions for our LCD. */
	esp_i2c_hd44780_pcf8574_begin(&i2c_lcd);

	for (int i = 3; i > 0; i--) {
		printf("Attempting to send chars to LCD in %d seconds...\n", i);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	char s[] = { "YYYYzYYYYz" };
	char t[10];
	t[0] = '\0';

	while (1) {
		for (int i = 0; i < 10; i++) {
			esp_i2c_hd44780_pcf8574_send_char(&i2c_lcd, s[i]);

			t[0] = '\0';
			strncat(&t[0], &s[0], i + 1);
			printf("LCD displaying: \"%s\"\n", &t[0]);

			vTaskDelay(pdMS_TO_TICKS(50));
		}

		vTaskDelay(pdMS_TO_TICKS(500));

		esp_i2c_hd44780_pcf8574_clear_display(&i2c_lcd);
		printf("LCD displaying: \n");

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

