#pragma once

#include "IMediaContainer.hpp"
#include <vector>

class ITimerProvider;

class MediaContainer : public IMediaContainer
{
public:
    MediaContainer(int id, int width, int height, int zorder, std::unique_ptr<ITimerProvider>&& timer, std::unique_ptr<IFixedLayoutAdaptor>&& handler);
    ~MediaContainer() override;

    MediaContainer(const MediaContainer& other) = delete;
    MediaContainer& operator=(const MediaContainer& other) = delete;

    int width() const override;
    int height() const override;
    void scale(double scaleX, double scaleY) override;

    void loopMedia() override;
    int id() const override;
    int zorder() const override;
    void show() override;

    void addMedia(std::unique_ptr<IMedia>&& media, int x, int y) override;
    void addMedia(std::unique_ptr<IMedia>&& media) override;
    IFixedLayoutAdaptor& handler() override;

private:
    void initAndAddMediaToList(std::unique_ptr<IMedia>&& media);
    void scaleVisibleMedia(double scaleX, double scaleY);
    void startMedia(size_t mediaIndex);
    void onMediaTimeout();
    bool shouldNextMediaStart();
    size_t getNextMediaIndex();

private:
    std::unique_ptr<IFixedLayoutAdaptor> m_handler;
    std::unique_ptr<ITimerProvider> m_timer;
    int m_id;
    int m_zorder;
    bool m_mediaLooped = false;

    std::vector<IVisibleMedia*> m_visibleMedia;
    std::vector<std::unique_ptr<IMedia>> m_media;
    size_t m_currentMediaIndex = 0;

};
