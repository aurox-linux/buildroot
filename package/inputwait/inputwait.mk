INPUTWAIT_VERSION = 1.0
INPUTWAIT_SITE = $(TOPDIR)/package/inputwait
INPUTWAIT_SITE_METHOD = local
INPUTWAIT_LICENSE = GPL-2.0

define INPUTWAIT_BUILD_CMDS
	$(TARGET_CC) $(TARGET_CFLAGS) -o $(@D)/src/inputwait $(INPUTWAIT_SITE)/src/inputwait.c
endef

define INPUTWAIT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/src/inputwait $(TARGET_DIR)/usr/bin/inputwait
endef

$(eval $(generic-package))