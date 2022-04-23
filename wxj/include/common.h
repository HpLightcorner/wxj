#pragma once

#include "types.h"

namespace wxj
{
    inline wxBitmap getScaledBitmap(Path path, Size size)
    {
        if (std::filesystem::exists(path))
        {
            auto image = wxImage(path.string());
            auto resized = wxBitmap(image.Scale(size.GetWidth(), size.GetHeight(), wxIMAGE_QUALITY_HIGH));
            return resized;
        }

        return wxBitmap();
    }
}