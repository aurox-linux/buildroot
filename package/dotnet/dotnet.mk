################################################################################
#
# dotnet
#
################################################################################

ifeq ($(BR2_aarch64),y)
	DOTNET_ARCH=arm64
endif

ifeq ($(BR2_arm),y)
	DOTNET_ARCH=arm
endif

ifeq ($(BR2_x86_64),y)
	DOTNET_ARCH=x64
endif

DOTNET_VERSION = 10.0.0-rc.2.25502.107
DOTNET_SOURCE = dotnet-runtime-$(DOTNET_VERSION)-linux-$(DOTNET_ARCH).tar.gz
DOTNET_SITE = https://builds.dotnet.microsoft.com/dotnet/Runtime/$(DOTNET_VERSION)
DOTNET_INSTALL_TARGET = YES

define DOTNET_INSTALL_TARGET_CMDS
	$(INSTALL) -d $(TARGET_DIR)/usr/share/dotnet
	cp -a $(@D)/host $(TARGET_DIR)/usr/share/dotnet/host
	cp -a $(@D)/shared $(TARGET_DIR)/usr/share/dotnet/shared
	$(INSTALL) -D -m 0755 $(@D)/dotnet $(TARGET_DIR)/usr/share/dotnet/dotnet

	$(INSTALL) -d $(TARGET_DIR)/usr/bin
	ln -sf /usr/share/dotnet/dotnet $(TARGET_DIR)/usr/bin/dotnet
endef

$(eval $(generic-package))