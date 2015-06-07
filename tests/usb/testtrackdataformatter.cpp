#include "testtrackdataformatter.h"
#include "usb/trackdataformatter.h"

typedef std::pair<std::string, Value> line_item;

void TestTrackDataFormatter::test2Points() {
    lines_t lines;
    TYPE_VECTOR(double) maxVelocity = {1.0, 1.0, 1.0, 1.0};
    TYPE_VECTOR(uint16_t) coordinateScale = {1, 1, 1, 1};
    TYPE_VECTOR(uint16_t) velocityScale = {2, 2, 2, 2};
    TYPE_VECTOR(AxisRangePtr) ranges;
    ranges.x = AxisRangePtr(new AxisRange(0.0, 10.0));
    ranges.y = AxisRangePtr(new AxisRange(0.0, 5.0));
    ranges.z = AxisRangePtr(new AxisRange(0.0, 2.0));
    ranges.f = AxisRangePtr(new AxisRange(0.0, 1.0));
    const size_t dataSize = 64;
    uint8_t data[dataSize] = {0};

    line_t line1;
    line_t line2;

    line1.insert (line_item(std::string("x"), Value(0.0)));
    line2.insert (line_item(std::string("x"), Value(5.0)));

    line1.insert (line_item(std::string("y"), Value(0.0)));
    line2.insert (line_item(std::string("y"), Value(2.5)));

    line1.insert (line_item(std::string("z"), Value(0.0)));
    line2.insert (line_item(std::string("z"), Value(1.0)));

    line1.insert (line_item(std::string("f"), Value(0.0)));
    line2.insert (line_item(std::string("f"), Value(0.5)));

    lines.push_back (&line1);
    lines.push_back (&line2);

    TrackDataFormatter formatter(
                &lines, maxVelocity,
                coordinateScale, velocityScale,
                ranges);

    size_t packageCount = formatter.getPackageCount ();

    QVERIFY(packageCount == 4);

    size_t formatedSize0 = formatter.format(0, data, dataSize);
    QVERIFY (formatedSize0 == 6 + 16); // setup message size
    message_t *setupMessage = (message_t *) data;
    QVERIFY (setupMessage->message_type == MESSAGE_TYPE_SETUP);
    QVERIFY (setupMessage->message_id == 0);
    QVERIFY (setupMessage->message_size == 16);
    QVERIFY (setupMessage->message_data.setup_data.x.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.x.velocity_scale == 2);
    QVERIFY (setupMessage->message_data.setup_data.y.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.y.velocity_scale == 2);
    QVERIFY (setupMessage->message_data.setup_data.z.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.z.velocity_scale == 2);
    QVERIFY (setupMessage->message_data.setup_data.f.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.f.velocity_scale == 2);

    size_t formatedSize1 = formatter.format(1, data, dataSize);
    QVERIFY (formatedSize1 == (6+18)); // message with point data
    message_t *firstPointMessage = (message_t *) (data);
    QVERIFY (firstPointMessage->message_type == MESSAGE_TYPE_TRACK_POINT);
    QVERIFY (firstPointMessage->message_id == 1);
    QVERIFY (firstPointMessage->message_size == 18);
    QVERIFY (firstPointMessage->message_data.track_point_data.point_id == 0);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.x.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.x.value ==
             0x0000);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.y.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.y.value ==
             0x0000);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.z.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.z.value ==
             0x0000);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.f.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.f.value ==
             0x0000);

    size_t formatedSize2 = formatter.format(2, data, dataSize);
    QVERIFY (formatedSize2 == (6+18)); // message with point data
    message_t *secondPointMessage = (message_t *) (data);
    QVERIFY (secondPointMessage->message_type == MESSAGE_TYPE_TRACK_POINT);
    QVERIFY (secondPointMessage->message_id == 2);
    QVERIFY (secondPointMessage->message_size == 18);
    QVERIFY (secondPointMessage->message_data.track_point_data.point_id == 5);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.x.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.x.value ==
             0x8000);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.y.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.y.value ==
             0x8000);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.z.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.z.value ==
             0x8000);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.f.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.f.value ==
             0x8000);

    size_t formatedSize3 = formatter.format(3, data, dataSize);
    QVERIFY (formatedSize3 == (6)); // message with point data
    message_t *startMessage = (message_t *) (data);
    QVERIFY (startMessage->message_type == MESSAGE_TYPE_START);
    QVERIFY (startMessage->message_id == 3);
    QVERIFY (startMessage->message_size == 0);

    lines.erase (lines.begin (), lines.end ());
}

void TestTrackDataFormatter::testPointAndSpline() {
    lines_t lines;
    TYPE_VECTOR(double) maxVelocity = {1.0, 1.0, 1.0, 1.0};
    TYPE_VECTOR(uint16_t) coordinateScale = {1, 1, 1, 1};
    TYPE_VECTOR(uint16_t) velocityScale = {2, 2, 2, 2};
    TYPE_VECTOR(AxisRangePtr) ranges;
    ranges.x = AxisRangePtr(new AxisRange(0.0, 10.0));
    ranges.y = AxisRangePtr(new AxisRange(0.0, 5.0));
    ranges.z = AxisRangePtr(new AxisRange(0.0, 2.0));
    ranges.f = AxisRangePtr(new AxisRange(0.0, 1.0));
    const size_t dataSize = 1024;
    uint8_t data[dataSize] = {0};

    line_t line1;
    line_t line2;
    Spline spline1;

    spline1.add_node (0, 1.0);
    spline1.add_node (1, 0.5);
    spline1.add_node (1.5, 1.5);
    spline1.add_node (1.75, 5.0);
    spline1.add_node (2.0, 5.0);
    line1.insert (line_item(std::string("x"), Value(0.0)));
    line2.insert (line_item(std::string("x"), Value(&spline1)));

    line1.insert (line_item(std::string("y"), Value(0.0)));
    line2.insert (line_item(std::string("y"), Value(2.5)));

    line1.insert (line_item(std::string("z"), Value(0.0)));
    line2.insert (line_item(std::string("z"), Value(1.0)));

    line1.insert (line_item(std::string("f"), Value(0.0)));
    line2.insert (line_item(std::string("f"), Value(0.5)));

    lines.push_back (&line1);
    lines.push_back (&line2);

    TrackDataFormatter formatter(
                &lines, maxVelocity,
                coordinateScale, velocityScale,
                ranges);

    size_t packageCount = formatter.getPackageCount ();
    QVERIFY(packageCount == 9);

    size_t formatedSize0 = formatter.format(0, data, dataSize);
    QVERIFY (formatedSize0 == 6 + 16);
    message_t *setupMessage = (message_t *) data;

    QVERIFY (setupMessage->message_type == MESSAGE_TYPE_SETUP);
    QVERIFY (setupMessage->message_id == 0);
    QVERIFY (setupMessage->message_size == 16);
    QVERIFY (setupMessage->message_data.setup_data.x.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.x.velocity_scale == 2);
    QVERIFY (setupMessage->message_data.setup_data.y.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.y.velocity_scale == 2);
    QVERIFY (setupMessage->message_data.setup_data.z.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.z.velocity_scale == 2);
    QVERIFY (setupMessage->message_data.setup_data.f.scale == 1);
    QVERIFY (setupMessage->message_data.setup_data.f.velocity_scale == 2);

    size_t formatedSize1 = formatter.format(1, data, dataSize);
    QVERIFY (formatedSize1 == 6 + 6);
    message_t *firstSplineNode0Message = (message_t *) (data);
    QVERIFY (firstSplineNode0Message->message_type == MESSAGE_TYPE_SPLINE);
    QVERIFY (firstSplineNode0Message->message_id == 1);
    QVERIFY (firstSplineNode0Message->message_size == 6);
    QVERIFY (firstSplineNode0Message->message_data.spline_data.spline_id == 0);
    QVERIFY (firstSplineNode0Message->message_data.spline_data.node.x == 0x0000);
    QVERIFY (firstSplineNode0Message->message_data.spline_data.node.y == 0x199a);

    size_t formatedSize2 = formatter.format(2, data, dataSize);
    QVERIFY (formatedSize2 == 6 + 6);
    message_t *firstSplineNode1Message = (message_t *) (data);
    QVERIFY (firstSplineNode1Message->message_type == MESSAGE_TYPE_SPLINE);
    QVERIFY (firstSplineNode1Message->message_id == 2);
    QVERIFY (firstSplineNode1Message->message_size == 6);
    QVERIFY (firstSplineNode1Message->message_data.spline_data.spline_id == 0);
    QVERIFY (firstSplineNode1Message->message_data.spline_data.node.x == 0x8000);
    QVERIFY (firstSplineNode1Message->message_data.spline_data.node.y == 0x0CCD);

    size_t formatedSize3 = formatter.format(3, data, dataSize);
    QVERIFY (formatedSize3 == 6 + 6);
    message_t *firstSplineNode2Message = (message_t *) (data);
    QVERIFY (firstSplineNode2Message->message_type == MESSAGE_TYPE_SPLINE);
    QVERIFY (firstSplineNode2Message->message_id == 3);
    QVERIFY (firstSplineNode2Message->message_size == 6);
    QVERIFY (firstSplineNode2Message->message_data.spline_data.spline_id == 0);
    QVERIFY (firstSplineNode2Message->message_data.spline_data.node.x == 0xBFFF);
    QVERIFY (firstSplineNode2Message->message_data.spline_data.node.y == 0x2666);

    size_t formatedSize4 = formatter.format(4, data, dataSize);
    QVERIFY (formatedSize4 == 6 + 6);
    message_t *firstSplineNode3Message = (message_t *) (data);
    QVERIFY (firstSplineNode3Message->message_type == MESSAGE_TYPE_SPLINE);
    QVERIFY (firstSplineNode3Message->message_id == 4);
    QVERIFY (firstSplineNode3Message->message_size == 6);
    QVERIFY (firstSplineNode3Message->message_data.spline_data.spline_id == 0);
    QVERIFY (firstSplineNode3Message->message_data.spline_data.node.x == 0xDFFF);
    QVERIFY (firstSplineNode3Message->message_data.spline_data.node.y == 0x8000);

    size_t formatedSize5 = formatter.format(5, data, dataSize);
    QVERIFY (formatedSize5 == 6 + 6);
    message_t *firstSplineNode4Message = (message_t *) (data);
    QVERIFY (firstSplineNode4Message->message_type == MESSAGE_TYPE_SPLINE);
    QVERIFY (firstSplineNode4Message->message_id == 5);
    QVERIFY (firstSplineNode4Message->message_size == 6);
    QVERIFY (firstSplineNode4Message->message_data.spline_data.spline_id == 0);
    QVERIFY (firstSplineNode4Message->message_data.spline_data.node.x == 0xFFFF);
    QVERIFY (firstSplineNode4Message->message_data.spline_data.node.y == 0x8000);

    size_t formatedSize7 = formatter.format(6, data, dataSize);
    QVERIFY (formatedSize7 == 6+18);
    message_t *firstPointMessage = (message_t *) (data);
    QVERIFY (firstPointMessage->message_type == MESSAGE_TYPE_TRACK_POINT);
    QVERIFY (firstPointMessage->message_id == 6);
    QVERIFY (firstPointMessage->message_size == 18);
    QVERIFY (firstPointMessage->message_data.track_point_data.point_id == 0);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.x.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.x.value ==
             0x0000);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.y.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.y.value ==
             0x0000);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.z.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.z.value ==
             0x0000);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.f.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (firstPointMessage->message_data.track_point_data.coordinates.f.value ==
             0x0000);

    size_t formatedSize8 = formatter.format(7, data, dataSize);
    QVERIFY (formatedSize8 == 6+18);
    message_t *secondPointMessage = (message_t *) (data);
    QVERIFY (secondPointMessage->message_type == MESSAGE_TYPE_TRACK_POINT);
    QVERIFY (secondPointMessage->message_id == 7);
    QVERIFY (secondPointMessage->message_size == 18);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.x.type ==
             TRACK_POINT_TYPE_SPLINE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.x.value ==
             0x0000);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.y.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.y.value ==
             0x8000);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.z.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.z.value ==
             0x8000);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.f.type ==
             TRACK_POINT_TYPE_VALUE);
    QVERIFY (secondPointMessage->message_data.track_point_data.coordinates.f.value ==
             0x8000);
    qDebug("%d", secondPointMessage->message_data.track_point_data.point_id);

    //TODO
    //QVERIFY (secondPointMessage->message_data.track_point_data.point_id == 5);

    size_t formatedSize9 = formatter.format(8, data, dataSize);
    QVERIFY (formatedSize9 == 6);
    message_t *startMessage = (message_t *) (data);
    QVERIFY (startMessage->message_type == MESSAGE_TYPE_START);
    QVERIFY (startMessage->message_id == 8);
    QVERIFY (startMessage->message_size == 0);


    lines.erase (lines.begin (), lines.end ());
}

