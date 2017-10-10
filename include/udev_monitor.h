#pragma once

#include <libudev.h>

#include "udev_device.h"

namespace udevpp {

    class UDevMonitor {
       public:
           UDevMonitor();
           UDevMonitor(const UDevMonitor &other) = delete;
           UDevMonitor(UDevMonitor &&other);
           ~UDevMonitor();

           UDevMonitor &operator=(const UDevMonitor &other) = delete;
           UDevMonitor &operator=(UDevMonitor &&other) = delete;
           explicit operator bool() const;

           UDevDevice wait_for_device() const;
       private:
           udev_monitor *m_udev_monitor_handle;
           udev *m_udev_handle;
    };
}  // namespace udevpp
