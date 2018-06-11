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
        if (m_udev_handle) {
            udev_unref(m_udev_handle);
        }

        if (m_udev_device_handle) {
            udev_device_unref(m_udev_device_handle);
        }
    }

    UDevDevice &UDevDevice::operator=(UDevDevice &&other) {
        swap(other);

        return *this;
    }

    UDevDevice::operator bool() const { return m_udev_handle && m_udev_device_handle; }

    std::string_view UDevDevice::get_action() const { return udev_device_get_action(m_udev_device_handle); }

    std::string_view UDevDevice::get_device_path() const { return udev_device_get_devpath(m_udev_device_handle); }

    std::string_view UDevDevice::get_device_type() const { return udev_device_get_devtype(m_udev_device_handle); }

    std::map<std::string, std::string> UDevDevice::get_device_attributes() const {
        udev_list_entry *entry = udev_device_get_properties_list_entry(m_udev_device_handle);
        std::map<std::string, std::string> result;

        while (entry != nullptr) {
            const char *attribute_name = udev_list_entry_get_name(entry);
            const char *attribute_value = udev_list_entry_get_value(entry);

            if (attribute_name && attribute_value) {
                result[attribute_name] = attribute_value;
            }

            entry = udev_list_entry_get_next(entry);
        }

        return result;
    }

    void UDevDevice::swap(UDevDevice &other) noexcept {
        using std::swap;

        swap(m_udev_handle, other.m_udev_handle);
        swap(m_udev_device_handle, other.m_udev_device_handle);
    }

    void swap(UDevDevice &lhs, UDevDevice &rhs) noexcept { lhs.swap(rhs); }
}  // namespace udevpp
