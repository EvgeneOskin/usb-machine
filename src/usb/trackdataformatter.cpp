#include "trackdataformatter.h"

TrackDataFormatter::TrackDataFormatter(frames_t &hiLevelFrames, axis_ranges_t &ranges, QObject *parent) :
    QObject(parent), ranges(ranges) {
    frames_t::iterator it;
    for (it = hiLevelFrames.begin (); it != hiLevelFrames.end (); it++) {
        this->hiLevelFrames.push_back (*it);
    }
    varsStr.push_back (std::string("x"));
    varsStr.push_back (std::string("y"));
    varsStr.push_back (std::string("z"));
    varsStr.push_back (std::string("f"));
}

TrackDataFormatter::~TrackDataFormatter() {}

size_t TrackDataFormatter::formatFrame(
        size_t frameIndex,
        byte pureData[],
        size_t maxSize) {

    if (frameIndex < hiLevelFrames.size ()) {
        frames_t::iterator it = hiLevelFrames.begin ();
        std::advance(it, frameIndex);
        frame_t frame = *it;
        size_t frameSize = calculateFrameSize(frame);
        if (maxSize >= frameSize) {
            return notSafeFormatFrame(frameSize, frame, pureData);
        }
    }
    return 0;
}

size_t TrackDataFormatter::calculateFrameSize(frame_t frame) {
    size_t sum = headerSize();
    foreach (std::string i, varsStr) {
        sum += calculateValueSize(frame->find (i)->second);
    }
    return sum;
}


size_t TrackDataFormatter::calculateValueSize(Value &value) {
    if (value.getType () == value_types_number) {
        return 2;
    } else {
        return 2*value.get_spline ()->get_nodes ().size ();
    }
}


size_t TrackDataFormatter::headerSize() {
    return 2;
}

size_t TrackDataFormatter::notSafeFormatFrame(
        size_t frameSize, frame_t frame, byte pureData[]) {
//    pureData[0] = (byte) (frameSize >> 8) & 0xff;
//    pureData[1] = (byte) frameSize & 0xff;
    size_t size = 0/*2*/;

    foreach (std::string i, varsStr) {
        size += addValue(ranges.find(i)->second,
                         frame->find(i)->second,
                         pureData + size);
    }
    return size;
}

size_t TrackDataFormatter::addValue(
        AxisRange *axisRange, Value &value, byte *pureData) {
    pureData[0] = value.getType () & 0xff;
    if (value.getType () == value_types_number) {
        axisRange->setPositionInRange (value.get_number (), pureData + 1);
        return 3;
    } else {
        spline_nodes_t splineNodes = value.get_spline()->get_nodes ();
        spline_nodes_t::iterator it;
        size_t sum = 1;
        AxisRange aplineXRange((*splineNodes.begin ())->first,
                               (*splineNodes.rend ())->first);
        for (it = splineNodes.begin(); it != splineNodes.end (); it++) {
            aplineXRange.setPositionInRange ((*it)->first, pureData + sum);
            axisRange->setPositionInRange ((*it)->second, pureData + sum + 2);
            sum += 4;
        }
        // Format spline
        return sum;
    }
}


size_t TrackDataFormatter::getFrameCount() {
    return hiLevelFrames.size ();
}
