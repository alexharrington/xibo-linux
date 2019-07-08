#pragma once

#include "IMedia.hpp"
#include "MediaOptions.hpp"

#include "utils/ITimerProvider.hpp"

#include "control/common/transitions/TransitionExecutor.hpp"
#include "control/common/IWidget.hpp"

class Media : public IMedia
{
public:
    Media(const MediaOptions& options, const std::shared_ptr<IWidget>& view);

    void attachMedia(std::unique_ptr<IMedia>&& attachedMedia) override;
    void start() override;
    void stop() override;

    void setInTransition(std::unique_ptr<TransitionExecutor>&& transition) override;
    void setOutTransition(std::unique_ptr<TransitionExecutor>&& transition) override;

    SignalMediaFinished mediaFinished() override;
    SignalMediaRemoved mediaRemoved() override;

    MediaGeometry::Align align() const override;
    MediaGeometry::Valign valign() const override;
    std::shared_ptr<IWidget> view() override;

protected:
    virtual void onStarted();
    virtual void onStopped();

private:
    void startTimer(int duration);
    void startAttachedMedia();
    void stopAttachedMedia();

    void applyInTransition();
    void applyOutTransition();

private:
    MediaOptions m_options;
    std::shared_ptr<IWidget> m_view;
    std::unique_ptr<IMedia> m_attachedMedia;
    std::unique_ptr<ITimerProvider> m_timer;
    std::unique_ptr<TransitionExecutor> m_inTransition;
    std::unique_ptr<TransitionExecutor> m_outTransition;
    SignalMediaFinished m_mediaFinished;
    SignalMediaRemoved m_mediaRemoved;

};
