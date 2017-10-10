#include <gpio.h>
#include <ssp.h>

void sleep(uint16_t ms){
  volatile uint32_t i;
  for (i = 0 ; i < ms * 50000 ; i++) { ; }
}

int main() {
    //Initialize the pin_t structure with the pin port and number
    //On this board there is a LED on PG13
    pin_t as1 = make_pin(gpio_port_a, 0);

    //configure the pin for output.
    gpio_config (as1, pin_dir_write, pull_none);

    //set the pin to HIGH
    gpio_set (as1, 1);


    //On this board there is a LED on PG13
    pin_t as2 = make_pin(gpio_port_a, 1);

    //configure the pin for output.
    gpio_config(as2, pin_dir_write, pull_none);

    //set the pin to HIGH
    gpio_set(as2, 0);
    //On this board there is a LED on PG13
    pin_t as3 = make_pin(gpio_port_a, 2);

    //configure the pin for output.
    gpio_config(as3, pin_dir_write, pull_none);

    //set the pin to HIGH
    gpio_set(as3, 1);

    //On this board there is a clock on PA5
    pin_t clk = make_pin(gpio_port_b, 10);

    //configure the pin for output.
    gpio_config(clk, pin_dir_write, pull_down);

    //set the pin to HIGH
    //gpio_set(clk, 1);

    pin_t oe = make_pin(gpio_port_a, 5);

    //configure the pin for output.
    gpio_config (oe, pin_dir_write, pull_none);

    //set the pin to HIGH
    gpio_set (oe, 1);

    //On this board there is a LED on PG13
    pin_t data = make_pin(gpio_port_c, 3);

    //configure the pin for output.
    gpio_config (data, pin_dir_write, pull_down);

    //set the pin to HIGH
    gpio_set (data, 1);

    //On this board there is a LED on PG13
    pin_t str = make_pin(gpio_port_f, 6);

    //configure the pin for output.
    gpio_config(str, pin_dir_write, pull_down);

    //set the pin to HIGH
    gpio_set(str, 1);

    ssp_port_t ssp = { .mode = ssp_master, .ssp = ssp_2, .sclk = clk, .mosi = data, .miso = PIN_NULL, .ss = PIN_NULL};

    uint8_t carac[10];
    carac[0] = 0b10000001;
    carac[1] = 0b11101101;
    carac[2] = 0b01000011;
    carac[3] = 0b01001001;
    carac[4] = 0b00101101;
    carac[5] = 0b00011001;
    carac[6] = 0b00010001;
    carac[7] = 0b11001101;
    carac[8] = 0b00000001;
    carac[9] = 0b00001001;

    ssp_config(ssp, 8000000);

    for (int i = 0; i < 1000; i++) {
      for (int j = 0; j <333; j++){
        gpio_set (as1, 0);
        gpio_set (as2, 1);
        gpio_set (as3, 1);
        gpio_set (oe, 0);
        gpio_set (str, 0);
        ssp_write(ssp_2, carac[i%10]);
        gpio_set (oe, 1);
        gpio_set (str, 1);
        sleep(1);

        gpio_set (as1, 1);
        gpio_set (as2, 0);
        gpio_set (as3, 1);
        gpio_set (oe, 0);
        gpio_set (str, 0);
        ssp_write(ssp_2, carac[(i/10) % 10]);
        gpio_set (oe, 1);
        gpio_set (str, 1);

        sleep(1);

        gpio_set (as1, 1);
        gpio_set (as2, 1);
        gpio_set (as3, 0);
        gpio_set (oe, 0);
        gpio_set (str, 0);
        ssp_write(ssp_2, carac[i/100]);
        gpio_set (oe, 1);
        gpio_set (str, 1);

        sleep(1);
      }
      //sleep(1000);
    }

      //sleep(1000);
    //}




    return 0;
}
