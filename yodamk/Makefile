
include $(TOPDIR)/rules.mk

PKG_NAME:=system_state
PKG_VERSION:=
PKG_RELEASE:=1

#PKG_SOURCE_PROTO:=git
#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=https://github.com/aliyun/aliyun-log-c-sdk.git
#PKG_SOURCE_VERSION:=$(PKG_VERSION)

PKG_SOURCE_DIR:=$(ROKID_DIR)/frameworks/native/libs/system_state

PKG_FIXUP:=libtool
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1
PKG_LICENSE:=GPL-2.0+

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk


PRODUCT_NAME=kamino

define Package/system_state
  SECTION:=libs
  CATEGORY:=rokid
  TITLE:=system_state
  DEPENDS:=
  URL:=
endef

#crypto
#define Package/rklog/config
#	source "$(SOURCE)/Config.in"
#endef

define Package/system_state/description
	system system_state lib
endef

TARGET_CFLAGS += $(FPIC)


#CMAKE_OPTIONS += \
	-DBUILD_SHARED_LIBS=ON \
	-DSTAGING_DIR=
define Build/Prepare
	$(CP) $(PKG_SOURCE_DIR)/* $(PKG_BUILD_DIR)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/system_state/
	$(CP) $(PKG_BUILD_DIR)/include/*.h $(1)/usr/include/system_state/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so $(1)/usr/lib/
endef

#define Package/rklog/install
#	$(INSTALL_DIR) $(1)/usr/lib
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so $(1)/usr/lib/
#	$(INSTALL_DIR) $(1)/usr/bin
#	$(CP) $(PKG_INSTALL_DIR)/usr/bin/set_log_level $(1)/usr/bin/
#	$(CP) $(PKG_INSTALL_DIR)/usr/bin/cloudlog $(1)/usr/bin/
#	$(CP) $(PKG_INSTALL_DIR)/usr/bin/rklogger $(1)/usr/bin/
	#$(INSTALL_DIR) $(1)/etc/init.d/
	#$(CP) ./files/cloudlog $(1)/etc/init.d/
#endef

$(eval $(call BuildPackage,system_state))

