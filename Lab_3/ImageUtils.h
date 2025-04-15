#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <opencv2/core.hpp>

// Mouse callback function declaration
void onMouse(int event, int x, int y, int flags, void* userdata);
void onMouseMean(int event, int x, int y, int flags, void* userdata);
void onMouseSegment(int event, int x, int y, int flags, void* userdata);
void onMouseSegmentHSV(int event, int x, int y, int flags, void* userdata);
void onMouseChangeColor(int event, int x, int y, int flags, void* userdata);

#endif // IMAGE_UTILS_H
