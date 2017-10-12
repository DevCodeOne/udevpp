#pragma once

#include "common.h"

#include <optional>

#include <libudev.h>

#include "udev.h"
#include "udev_device.h"

namespace udevpp {

    class UDevMonitor final {
       public:
           UDevMonitor(UDev &udev);
           UDevMonitor(const UDevMonitor &other) = delete;
           UDevMonitor(UDevMonitor &&other);
           ~UDevMonitor();

           UDevMonitor &operator=(const UDevMonitor &other) = delete;
           UDevMonitor &operator=(UDevMonitor &&other);
           explicit operator bool() const;
           void swap(UDevMonitor &other) noexcept;

           std::optional<UDevDevice> wait_for_device() const;
       private:
           bool setup_file_descriptor();
           bool enable_receiving();

           udev *m_udev_handle = nullptr;
           udev_monitor *m_udev_monitor_handle = nullptr;
           int m_udev_monitor_file_descriptor = 0;
           bool m_file_descriptor_valid = false;
           bool m_is_receiving = false;
    };

    void swap(UDevDevice &lhs, UDevDevice &rhs) noexcept;
}  // namespace udevpp
