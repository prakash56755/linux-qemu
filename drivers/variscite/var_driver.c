/*
 * Simple Platform var int driver
 *
 * Copyright (c) Prakash <prakash56755@gmail.com>
 */

#include <linux/err.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define DRIVER_NAME	"var_int"
#define MAX_CHAR     20
#define VAR_DRIVER_VER  "v1.2"


struct vardev {
    struct device *dev;
    char device_name[20];
    int var_gpio;
};

static int var_int_probe(struct platform_device *pdev)
{
    pr_info("#### %s() ####\n", __func__);
    struct device *dev = &pdev->dev;
    struct device_node *node = dev->of_node;
    struct vardev * var_dev;
    int ret_val;
    const char *var_string;

    var_dev = devm_kzalloc(dev, sizeof(*var_dev), GFP_KERNEL);
	if (!var_dev)
		return -ENOMEM;

    var_dev->dev = &pdev->dev;

    dev_info(var_dev->dev, "Driver version: %s\n", VAR_DRIVER_VER);

    ret_val = of_property_read_string(node, "interview-name", &var_string);
	if (ret_val < 0) {
        dev_err(var_dev->dev, "Interview name string is missing in platform device-tree.\n");
        return -EINVAL;
    }

    dev_info(var_dev->dev, "interview-name string from device tree: %s\n", var_string);

    platform_set_drvdata(pdev, var_dev);

    return 0;
}

static int var_int_remove(struct platform_device *pdev)
{

    dev_info(&pdev->dev, "Var_Driver removed: \n");
    return 0;
}

static const struct of_device_id var_int_dt_ids[] = {
	{ .compatible = "interview,challenge", },
	{ }
};
MODULE_DEVICE_TABLE(of, var_int_dt_ids);

static struct platform_driver var_int_driver = {
	.driver = {
		.name	= DRIVER_NAME,
		.of_match_table = var_int_dt_ids,
	},
	.probe  = var_int_probe,
    .remove = var_int_remove,
};

module_platform_driver(var_int_driver);

MODULE_AUTHOR("Pitchaiah Prakash <prakash56755@gmail.com>");
MODULE_DESCRIPTION("Simple platform var driver");
MODULE_LICENSE("GPL v2");
