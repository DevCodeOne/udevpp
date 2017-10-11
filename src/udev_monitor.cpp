#include "udev_monitor.h"

namespace udevpp {

    UDevMonitor::UDevMonitor(UDev &udev) : m_udev_handle(udev_ref(udev.udev_handle())) {
        m_udev_monitor_handle = udev_monitor_new_from_netlink(m_udev_handle, "udev");
        m_file_descriptor_valid = setup_file_descriptor();
        m_is_receiving = enable_receiving();
    }

    UDevMonitor::UDevMonitor(UDevMonitor &&other)
        : m_udev_handle(other.m_udev_handle), m_udev_monitor_handle(other.m_udev_monitor_handle) {
        other.m_udev_handle = nullptr;
        other.m_udev_monitor_handle = nullptr;
    }

    UDevMonitor::~UDevMonitor() {
        if (m_udev_handle) {
            udev_unref(m_udev_handle);
        }

        if (m_udev_monitor_handle) {
            udev_monitor_unref(m_udev_monitor_handle);
        }
    }

    UDevMonitor::operator bool() const {
        return m_udev_handle && m_udev_monitor_handle && m_file_descriptor_valid && m_is_receiving;
    }

    bool UDevMonitor::setup_file_descriptor() {
        if (m_udev_handle && m_udev_monitor_handle) {
            m_udev_monitor_file_descriptor = udev_monitor_get_fd(m_udev_monitor_handle);

            if (m_udev_monitor_file_descriptor < 0) {
                // error couldn't get file descriptor
            }

            int file_descriptor_flags = fcntl(m_udev_monitor_file_descriptor, F_GETFL, 0);

            if (file_descriptor_flags < 0) {
                // error couldn't get file descriptor flags
                // check errno and react accordingly
            }

            if (file_descriptor_flags & O_NONBLOCK) {
                file_descriptor_flags &= ~O_NONBLOCK;

                if (fcntl(m_udev_monitor_file_descriptor, F_SETFL, file_descriptor_flags) < 0) {
                    // error couldn't set file descriptor to blocking
                }
            }

            return true;
        }

        return false;
    }

    bool UDevMonitor::enable_receiving() {
        if (udev_monitor_enable_receiving(m_udev_monitor_handle) < 0) {
            // error coulnd't enable receiving
            return false;
        }

        return true;
    }

    std::optional<UDevDevice> UDevMonitor::wait_for_device() const {
        if (!(*this)) {
            return std::optional<UDevDevice>{};
        }

        return UDevDevice(m_udev_handle, udev_monitor_receive_device(m_udev_monitor_handle));
    }

}  // namespace udevpp
