/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file pin.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include <pin.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

static struct rt_device_pin _hw_pin;
static rt_size_t _pin_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_device_pin_status *status;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    status = (struct rt_device_pin_status *) buffer;
    if (status == RT_NULL || size != sizeof(*status)) return 0;

    status->status = pin->ops->pin_read(dev, status->pin);
    return size;
}

static rt_size_t _pin_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct rt_device_pin_status *status;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    status = (struct rt_device_pin_status *) buffer;
    if (status == RT_NULL || size != sizeof(*status)) return 0;

    pin->ops->pin_write(dev, (rt_base_t)status->pin, (rt_base_t)status->status);

    return size;
}

static rt_err_t  _pin_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_device_pin_mode *mode;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    mode = (struct rt_device_pin_mode *) args;
    if (mode == RT_NULL) return -RT_ERROR;

    pin->ops->pin_mode(dev, (rt_base_t)mode->pin, (rt_base_t)mode->mode);

    return 0;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pin_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _pin_read,
    _pin_write,
    _pin_control
};
#endif

int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data)
{
    _hw_pin.parent.type         = RT_Device_Class_Miscellaneous;
    _hw_pin.parent.rx_indicate  = RT_NULL;
    _hw_pin.parent.tx_complete  = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    _hw_pin.parent.ops          = &pin_ops;
#else
    _hw_pin.parent.init         = RT_NULL;
    _hw_pin.parent.open         = RT_NULL;
    _hw_pin.parent.close        = RT_NULL;
    _hw_pin.parent.read         = _pin_read;
    _hw_pin.parent.write        = _pin_write;
    _hw_pin.parent.control      = _pin_control;
#endif

    _hw_pin.ops                 = ops;
    _hw_pin.parent.user_data    = user_data;

    /* register a character device */
    rt_device_register(&_hw_pin.parent, name, RT_DEVICE_FLAG_RDWR);

    return 0;
}

rt_err_t rt_pin_attach_irq(rt_int32_t pin, rt_uint32_t mode,
                             void (*hdr)(void *args), void  *args)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if(_hw_pin.ops->pin_attach_irq)
    {
        return _hw_pin.ops->pin_attach_irq(&_hw_pin.parent, pin, mode, hdr, args);
    }
    return RT_ENOSYS;
}
rt_err_t rt_pin_detach_irq(rt_int32_t pin)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if(_hw_pin.ops->pin_detach_irq)
    {
        return _hw_pin.ops->pin_detach_irq(&_hw_pin.parent, pin);
    }
    return RT_ENOSYS;
}

rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint32_t enabled)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if(_hw_pin.ops->pin_irq_enable)
    {
        return _hw_pin.ops->pin_irq_enable(&_hw_pin.parent, pin, enabled);
    }
    return RT_ENOSYS;
}

/* RT-Thread Hardware PIN APIs */
void rt_pin_mode(rt_base_t pin, rt_base_t mode)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    _hw_pin.ops->pin_mode(&_hw_pin.parent, pin, mode);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_pin_mode, pinMode, set hardware pin mode);

void rt_pin_write(rt_base_t pin, rt_base_t value)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    _hw_pin.ops->pin_write(&_hw_pin.parent, pin, value);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_pin_write, pinWrite, write value to hardware pin);

int  rt_pin_read(rt_base_t pin)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    return _hw_pin.ops->pin_read(&_hw_pin.parent, pin);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_pin_read, pinRead, read status from hardware pin);
