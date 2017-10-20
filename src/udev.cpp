#include "udev.h"

namespace udevpp {

    UDev::UDev() : m_udev_handle(udev_new()) {}

    UDev::UDev(UDev &&other) : m_udev_handle(other.m_udev_handle) { other.m_udev_handle = nullptr; }

    UDev::~UDev() { udev_unref(m_udev_handle); }

    UDev::operator bool() const { return m_udev_handle; }

    udev *UDev::udev_handle() { return m_udev_handle; }

}  // namespace udevpp
