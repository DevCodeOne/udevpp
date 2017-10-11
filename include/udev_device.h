#pragma once

#include <string_view>

#include <libudev.h>

namespace udevpp {

    class UDevDevice final {
       public:
        UDevDevice(const UDevDevice &other) = delete;
        UDevDevice(UDevDevice &&other);
        ~UDevDevice();

        UDevDevice &operator=(const UDevDevice &other) = delete;
        UDevDevice &operator=(UDevDevice &&other);
        explicit operator bool() const;
        void swap(UDevDevice &other) noexcept;

        std::string_view get_action() const;
        std::string_view get_device_path() const;
        std::string_view get_device_type() const;
       private:
        UDevDevice(udev *udev_handle, udev_device *device_handle);

        udev *m_udev_handle = nullptr;
        udev_device *m_udev_device_handle = nullptr;

        friend class UDevMonitor;
        friend class UDev;
    };

    void swap(UDevDevice &lhs, UDevDevice &rhs) noexcept;

}  // namespace udevpp
