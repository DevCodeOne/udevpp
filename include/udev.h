#pragma once

#include <vector>

#include <libudev.h>

#include "udev_device.h"

namespace udevpp {

    class UDev final {
       public:
        UDev();
        UDev(const UDev &other) = delete;
        UDev(UDev &&other);
        ~UDev();

        UDev &operator=(const UDev &udev) = delete;
        UDev &operator=(UDev &&udev);
        explicit operator bool() const;

        std::vector<UDevDevice> enumerate_devices() const;
       private:
        udev *udev_handle();

        udev *m_udev_handle = nullptr;

        friend class UDevMonitor;
    };

}  // namespace udevpp
