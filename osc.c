#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/mman.h>

#define ARRAY_SIZE(_a)	(sizeof(_a) / sizeof(_a)[0])

static char const	col_normal[] = "\033[0;39m";
static char const	col_info[] = "\033[0;31m";

struct pin {
	char const *fn_name;
	char const *pin_name;
	unsigned int gp_bank;
	unsigned int gp_num;
	unsigned int mux_ctl;
	bool is_ctl;
};

static struct pin pins_cam0[] = {
	{
		.pin_name	= "CSI0_DATA04",
		.gp_bank	= 5,
		.gp_num		= 22,
		.fn_name	= "D04",
		.mux_ctl	= 0x0268,
	}, {
		.pin_name	= "CSI0_DATA05",
		.gp_bank	= 5,
		.gp_num		= 23,
		.fn_name	= "D05",
		.mux_ctl	= 0x026c,
	}, {
		.pin_name	= "CSI0_DATA06",
		.gp_bank	= 5,
		.gp_num		= 24,
		.fn_name	= "D06",
		.mux_ctl	= 0x0270,
	}, {
		.pin_name	= "CSI0_DATA07",
		.gp_bank	= 5,
		.gp_num		= 25,
		.fn_name	= "D07",
		.mux_ctl	= 0x0274
	}, {
		.pin_name	= "CSI0_DATA08",
		.gp_bank	= 5,
		.gp_num		= 26,
		.fn_name	= "D08",
		.mux_ctl	= 0x0278
	}, {
		.pin_name	= "CSI0_DATA09",
		.gp_bank	= 5,
		.gp_num		= 27,
		.fn_name	= "D09",
		.mux_ctl	= 0x027c
	}, {
		.pin_name	= "CSI0_DATA10",
		.gp_bank	= 5,
		.gp_num		= 28,
		.fn_name	= "D10",
		.mux_ctl	= 0x0280,
	}, {
		.pin_name	= "CSI0_DATA11",
		.gp_bank	= 5,
		.gp_num		= 29,
		.fn_name	= "D11",
		.mux_ctl	= 0x0284,
	}, {
		.pin_name	= "CSI0_DATA12",
		.gp_bank	= 5,
		.gp_num		= 30,
		.fn_name	= "D12",
		.mux_ctl	= 0x0288,
	}, {
		.pin_name	= "CSI0_DATA13",
		.gp_bank	= 5,
		.gp_num		= 31,
		.fn_name	= "D13",
		.mux_ctl	= 0x028c,
	}, {
		.pin_name	= "CSI0_DATA14",
		.gp_bank	= 6,
		.gp_num		= 0,
		.fn_name	= "D14",
		.mux_ctl	= 0x0290,
	}, {
		.pin_name	= "CSI0_DATA15",
		.gp_bank	= 6,
		.gp_num		= 1,
		.fn_name	= "D15",
		.mux_ctl	= 0x0294,
	}, {
		.pin_name	= "CSI0_DATA16",
		.gp_bank	= 6,
		.gp_num		= 2,
		.fn_name	= "D16",
		.mux_ctl	= 0x0298,
	}, {
		.pin_name	= "CSI0_DATA17",
		.gp_bank	= 6,
		.gp_num		= 3,
		.fn_name	= "D17",
		.mux_ctl	= 0x029c,
	}, {
		.pin_name	= "CSI0_DATA18",
		.gp_bank	= 6,
		.gp_num		= 4,
		.fn_name	= "D18",
		.mux_ctl	= 0x02a0,
	}, {
		.pin_name	= "CSI0_DATA19",
		.gp_bank	= 6,
		.gp_num		= 5,
		.fn_name	= "D19",
		.mux_ctl	= 0x02a4,
	}, {
		.pin_name	= "CSI0_HSYNC",
		.gp_bank	= 5,
		.gp_num		= 19,
		.fn_name	= "HSYNC",
		.mux_ctl	= 0x025c,
		.is_ctl		= true,
	}, {
		.pin_name	= "CSI0_PIXCLK",
		.gp_bank	= 5,
		.gp_num		= 18,
		.fn_name	= "PIXCLK",
		.mux_ctl	= 0x0258,
		.is_ctl		= true,
	}, {
		.pin_name	= "CSI0_VSYNC",
		.gp_bank	= 5,
		.gp_num		= 21,
		.fn_name	= "VSYNC",
		.mux_ctl	= 0x0264,
		.is_ctl		= true,
	},
};

static struct pin pins_cam1[] = {
	{
		.pin_name	= "EIM_AD09",
		.gp_bank	= 3,
		.gp_num		= 9,
		.fn_name	= "D00",
		.mux_ctl	= 0x0114,
	}, {
		.pin_name	= "EIM_AD08",
		.gp_bank	= 3,
		.gp_num		= 8,
		.fn_name	= "D01",
		.mux_ctl	= 0x0134,
	}, {
		.pin_name	= "EIM_AD07",
		.gp_bank	= 3,
		.gp_num		= 7,
		.fn_name	= "D02",
		.mux_ctl	= 0x0130,
	}, {
		.pin_name	= "EIM_AD06",
		.gp_bank	= 3,
		.gp_num		= 6,
		.fn_name	= "D03",
		.mux_ctl	= 0x012c,
	}, {
		.pin_name	= "EIM_AD05",
		.gp_bank	= 3,
		.gp_num		= 5,
		.fn_name	= "D04",
		.mux_ctl	= 0x0128,
	}, {
		.pin_name	= "EIM_AD04",
		.gp_bank	= 3,
		.gp_num		= 4,
		.fn_name	= "D05",
		.mux_ctl	= 0x0124,
	}, {
		.pin_name	= "EIM_AD03",
		.gp_bank	= 3,
		.gp_num		= 3,
		.fn_name	= "D06",
		.mux_ctl	= 0x0120,
	}, {
		.pin_name	= "EIM_AD02",
		.gp_bank	= 3,
		.gp_num		= 2,
		.fn_name	= "D07",
		.mux_ctl	= 0x011c,
	}, {
		.pin_name	= "EIM_AD01",
		.gp_bank	= 3,
		.gp_num		= 1,
		.fn_name	= "D08",
		.mux_ctl	= 0x0118,
	}, {
		.pin_name	= "EIM_AD00",
		.gp_bank	= 3,
		.gp_num		= 0,
		.fn_name	= "D09",
		.mux_ctl	= 0x0114,
	}, {
		.pin_name	= "EIM_EB1",
		.gp_bank	= 2,
		.gp_num		= 29,
		.fn_name	= "D10",
		.mux_ctl	= 0x0110,
	}, {
		.pin_name	= "EIM_EB0",
		.gp_bank	= 2,
		.gp_num		= 28,
		.fn_name	= "D11",
		.mux_ctl	= 0x010c,
	}, {
		.pin_name	= "EIM_ADDR17",
		.gp_bank	= 2,
		.gp_num		= 21,
		.fn_name	= "D12",
		.mux_ctl	= 0x00f0,
	}, {
		.pin_name	= "EIM_ADDR18",
		.gp_bank	= 2,
		.gp_num		= 20,
		.fn_name	= "D13",
		.mux_ctl	= 0x00ec,
	}, {
		.pin_name	= "EIM_ADDR19",
		.gp_bank	= 2,
		.gp_num		= 19,
		.fn_name	= "D14",
		.mux_ctl	= 0x00e8,
	}, {
		.pin_name	= "EIM_ADDR20",
		.gp_bank	= 2,
		.gp_num		= 18,
		.fn_name	= "D15",
		.mux_ctl	= 0x00e4,
	}, {
		.pin_name	= "EIM_ADDR21",
		.gp_bank	= 2,
		.gp_num		= 17,
		.fn_name	= "D16",
		.mux_ctl	= 0x00e0,
	}, {
		.pin_name	= "EIM_ADDR22",
		.gp_bank	= 2,
		.gp_num		= 16,
		.fn_name	= "D17",
		.mux_ctl	= 0x00dc,
	}, {
		.pin_name	= "EIM_ADDR23",
		.gp_bank	= 6,
		.gp_num		= 6,
		.fn_name	= "D18",
		.mux_ctl	= 0x00d8,
	}, {
		.pin_name	= "EIM_ADDR24",
		.gp_bank	= 5,
		.gp_num		= 4,
		.fn_name	= "D19",
		.mux_ctl	= 0x00d4,
	}, {
		.pin_name	= "EIM_AD11",
		.gp_bank	= 3,
		.gp_num		= 11,
		.fn_name	= "HSYNC",
		.mux_ctl	= 0x0140,
		.is_ctl		= true,
	}, {
		.pin_name	= "EIM_AD12",
		.gp_bank	= 3,
		.gp_num		= 12,
		.fn_name	= "VSYNC",
		.mux_ctl	= 0x0144,
		.is_ctl		= true,
	}, {
		.pin_name	= "EIM_ADDR16",
		.gp_bank	= 2,
		.gp_num		= 22,
		.fn_name	= "PIXCLK",
		.mux_ctl	= 0x00f4,
		.is_ctl		= true,
	},
};

static int cmp_pin_name(void const *a_, void const *b_)
{
	struct pin const	*a = a_;
	struct pin const	*b = b_;

	return strcmp(a->pin_name, b->pin_name);
}

static int cmp_fn_name(void const *a_, void const *b_)
{
	struct pin const	*a = a_;
	struct pin const	*b = b_;

	return strcmp(a->fn_name, b->fn_name);
}

static void writel(unsigned long v, void *p)
{
	memcpy(p, &v, sizeof v);
}

static unsigned long readl(void const *p)
{
	unsigned long	v;

	memcpy(&v, p, sizeof v);
	return v;
}

int main(int argc, char *argv[]) {
	int	fd;
	void	*io_mux;
	void	*io_gpio[7];
	size_t	i;
	struct pin const	*trig_pin = NULL;
	bool			last_trig = false;

	struct pin		*pins;
	size_t			num_pins;

	fd = open("/dev/mem", O_RDWR);
	assert(fd >= 0);

	io_mux = mmap(NULL, 4096, PROT_READ|PROT_WRITE, 
		      MAP_SHARED, fd, 0x20e0000);
	assert(io_mux != MAP_FAILED);

	switch (atoi(argv[1])) {
	case 0:
		pins = pins_cam0;
		num_pins = ARRAY_SIZE(pins_cam0);
		break;

	case 1:
		pins = pins_cam1;
		num_pins = ARRAY_SIZE(pins_cam1);
		break;

	default:
		abort();
	}

	for (i = 0; i < ARRAY_SIZE(io_gpio); ++i) {
		io_gpio[i] = mmap(NULL, 4096, PROT_READ|PROT_WRITE, 
				  MAP_SHARED, fd, 0x209c000 + i*0x4000);
		assert(io_gpio[i] != MAP_FAILED);
	}

	qsort(pins, num_pins, sizeof pins[0], cmp_fn_name);

	if (argc > 2) {
		for (i = 0; i < num_pins && !trig_pin; ++i) {
			if (strcmp(pins[i].fn_name, argv[2]) == 0)
				trig_pin = &pins[i];
		}

		if (!trig_pin)
			fprintf(stderr, "no such pin '%s'\n", argv[2]);
	}

	for (i = 0; i < num_pins; ++i) {
		void *	gp_base = io_gpio[pins[i].gp_bank - 1];

		writel(readl(gp_base + 4) & ~(1u << pins[i].gp_num), gp_base + 4);
		writel(5, io_mux + pins[i].mux_ctl);
	}

	for (i = 0; i < num_pins; ++i)
		printf(" %s", pins[i].fn_name);

	printf("\n");

	for (;;) {
		unsigned long	gpsr[ARRAY_SIZE(io_gpio)];
		bool		is_data = false;

		for (i = 0; i < ARRAY_SIZE(io_gpio); ++i)
			gpsr[i] = readl(io_gpio[i] + 8);

		if (trig_pin) {
			bool	now_trig = (gpsr[trig_pin->gp_bank - 1] & 
					    (1u << trig_pin->gp_num));
			if (now_trig == last_trig)
				continue;

			last_trig = now_trig;
		}

		for (i = 0; i < num_pins; ++i) {
			unsigned long	lvl = gpsr[pins[i].gp_bank - 1];

			if (!pins[i].is_ctl && !is_data)
				printf(" |");

			if (pins[i].is_ctl && is_data)
				printf(" |");

			is_data = !pins[i].is_ctl;

			if (&pins[i] == trig_pin)
				printf(col_info);

			printf(" %d",
			       lvl & (1u << pins[i].gp_num) ? 1 : 0);

			if (&pins[i] == trig_pin)
				printf(col_normal);
		}

		printf("\n");
	}
	
}