#pragma once

#include <vector>

#include <libudev.h>

#include "udev_device.h"
#include "udev_monitor.h"

namespace udevpp {
    class UDev final {
       public:
        UDev();
        UDev(const UDev &other) = delete;
        UDev(UDev &&other);
        ~UDev();

        UDev &operator=(const UDev &udev) = delete;
        UDev &operator=(UDev &&udev) = delete;
        explicit operator bool() const;

        std::vector<UDevDevice> enumerate_device() const;
        UDevMonitor create_monitor() const;

       private:
        udev *m_udev_handle = nullptr;
    };
}  // namespace udevpp
