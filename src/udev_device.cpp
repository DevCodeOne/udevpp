#include <utility>

#include "udev_device.h"

namespace udevpp {

    UDevDevice::UDevDevice(udev *udev_handle, udev_device *device_handle)
        : m_udev_handle(udev_ref(udev_handle)), m_udev_device_handle(udev_device_ref(device_handle)) {}

    UDevDevice::UDevDevice(UDevDevice &&other)
        : m_udev_handle(other.m_udev_handle), m_udev_device_handle(other.m_udev_device_handle) {
        other.m_udev_handle = nullptr;
        other.m_udev_device_handle = nullptr;
    }

    UDevDevice::~UDevDevice() {
        udev_unref(m_udev_handle);
        udev_device_unref(m_udev_device_handle);
    }

    UDevDevice &UDevDevice::operator=(UDevDevice &&other) {
        swap(other);

        return *this;
    }

    UDevDevice::operator bool() const {
        return m_udev_handle && m_udev_device_handle;
    }

    std::string_view UDevDevice::get_action() const {
        return udev_device_get_action(m_udev_device_handle);
    }

    std::string_view UDevDevice::get_device_path() const {
        return udev_device_get_devpath(m_udev_device_handle);
    }

    std::string_view UDevDevice::get_device_type() const {
        return udev_device_get_devtype(m_udev_device_handle);
    }

    void UDevDevice::swap(UDevDevice &other) noexcept {
        using std::swap;

        swap(m_udev_handle, other.m_udev_handle);
        swap(m_udev_device_handle, other.m_udev_device_handle);
    }

    void swap(UDevDevice &lhs, UDevDevice &rhs) noexcept {
        lhs.swap(rhs);
    }
}  // namespace udevpp
