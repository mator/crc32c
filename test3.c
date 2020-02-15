#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/crc32c.h>

#define CRC_SEED    (~(u32)0)

static int __init mymodule_init (void)
{
	char data[512];
	u32 oldcrc = 0xd00dface, crc = 0xdeadbeef;
	int i;
        u64 nsec;

	memset(data, 0, 512);

        nsec = ktime_get_ns();
	for (i = 0; i < 1000000; i++) {
	        crc = crc32c(CRC_SEED, data, 512);

		if (i > 0 && crc != oldcrc)
			printk("i: %d: oldcrc: 0x%x, crc: 0x%x\n", i, oldcrc, crc);
		oldcrc = crc;
	}
        nsec = ktime_get_ns() - nsec;	

	printk("Loop done in %lld nsec\n", nsec);
	return 0;
}

static void __exit mymodule_exit (void)
{
	printk ("Module uninitialized successfully \n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
MODULE_LICENSE("GPL");
