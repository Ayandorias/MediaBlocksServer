#ifndef MEDIABLOCKS_HPP
#define MEDIABLOCKS_HPP

#include <QString>

namespace MediaBlocks {
	const QString MEDIA_BLOCKS ("/mnt/sdcard/data/config/device_type_information.json");
	const QString MEDIA_BLOCKS_DEVICE ("/mnt/sdcard/data/config/device.json");

	const QString MBSERVER_DEVICE_GET ("mbserver.device.get");
	const QString MBSERVER_DEVICE_RESET ("mbserver.device.reset");
	const QString MBSERVER_DEVICE_UPDATE ("mbserver.device.update");
	const QString MBSERVER_DEVICE_SERVICE_REBOOT_SET ("mbserver.device.service.reboot.set");
	const QString MBSERVER_DEVICE_SERVICE_UPDATE_GET ("mbserver.device.service.update.get");
	const QString MBSERVER_DEVICE_SERVICE_UPDATE_SET ("mbserver.device.service.update.set");
	const QString MBSERVER_DEVICE_SETTINGS_NETWORK_GET ("mbserver.device.settings.network.get");
	const QString MBSERVER_DEVICE_SETTINGS_NETWORK_UPDATE ("mbserver.device.settings.network.update");
	const QString MBSERVER_DEVICE_SETTINGS_WLAN_GET ("mbserver.device.settings.wlan.get");
	const QString MBSERVER_DEVICE_SETTINGS_WLAN_UPDATE ("mbserver.device.settings.wlan.update");
	const QString MBSERVER_FLOOR_CREATE ("mbserver.floor.create");
	const QString MBSERVER_FLOOR_DELETE ("mbserver.floor.delete");
	const QString MBSERVER_FLOOR_GET ("mbserver.floor.get");
	const QString MBSERVER_FLOOR_GET_ALL ("mbserver.floor.get_all");
	const QString MBSERVER_FLOOR_UPDATE ("mbserver.floor.update");
	const QString MBSERVER_ROOM_CREATE ("mbserver.room.create");
	const QString MBSERVER_ROOM_DELETE ("mbserver.room.delete");
	const QString MBSERVER_ROOM_GET ("mbserver.room.get");
	const QString MBSERVER_ROOM_GET_ALL ("mbserver.room.get_all");
	const QString MBSERVER_ROOM_UPDATE ("mbserver.room.update");

	const QString ROOMLIST ("rooms");
	const int32_t ERROR_400 = 400;
	const int32_t ERROR_404 = 404;
	const int32_t ERROR_461 = 461;
}

#endif // MEDIABLOCKS_HPP
