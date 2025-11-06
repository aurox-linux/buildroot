################################################################################
#
# lua-evdev
#
################################################################################

LUA_EVDEV_VERSION = 2.2.1-1
LUA_EVDEV_NAME_UPSTREAM = evdev
LUA_EVDEV_SUBDIR = lua-evdev
LUA_EVDEV_LICENSE = MIT
LUA_EVDEV_LICENSE_FILES = $(LUA_EVDEV_SUBDIR)/LICENCE

$(eval $(luarocks-package))
