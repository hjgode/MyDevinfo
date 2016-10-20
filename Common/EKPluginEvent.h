
#ifndef EK_EKPLUGEVENT_H
#define EK_EKPLUGEVENT_H

#include "EKTypes.h"

namespace rhoElements {

enum EKPixelFormat
{
    EKPixelFormat_ARGB32
};

struct EKPluginPixMap
{
    uint32_t width; ///< width in pixels
    uint32_t height; ///< height in pixels
    int32_t stride; ///< number of bytes to next row. could be negative.
    uint32_t bitsPerPixel; ///< bits per pixel
    EKPixelFormat pixelFormat; ///< format of pixel data
    uint8_t* buffer; ///< pointer to pixel data
};

struct EKPluginEvent
{
    enum EventType
    {
        Paint
    };

    int version; ///< version of this structure
    EventType type;

    union {
        struct {
            // The plugin must only draw to the area of this pixmap defined
            // by the NPWindow structure in the NPP_SetWindow call.
            EKPluginPixMap pixmap;

            // Dirty rectangle relative to top-left of pixmap.
            int x0;
            int y0;
            int x1;
            int y1;
        } paint;
    };
};

} // namespace


#endif

