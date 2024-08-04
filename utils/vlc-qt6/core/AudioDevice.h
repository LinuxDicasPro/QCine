//
// Created by Andry on 2/11/21.
//
// LGPL if won't BSD write me.

#ifndef VLC_QT_AUDIODEVICE_H
#define VLC_QT_AUDIODEVICE_H

class VlcMediaPlayer;
class VlcInstance;

#include <vector>
#include <string>

struct DeviceInfo{
    std::string deviceName;
    std::string description;
};

class AudioDevice {

public:
    explicit AudioDevice(VlcMediaPlayer *vlcMediaPlayer);
    ~AudioDevice();
    std::vector<DeviceInfo> GetListDevice();
    void SetOutputDevice(const std::string& name);
    std::string GetCurrentDevice();

    static std::vector<DeviceInfo> GetWtfList(VlcInstance *instance);
    void SetOutputWtf(const std::string& name);

private:
    VlcMediaPlayer *_vlcMediaPlayer;
};

#endif //VLC_QT_AUDIODEVICE_H
