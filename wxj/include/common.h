#pragma once

#include "types.h"

namespace wxj
{
    inline wxBitmap getScaledBitmap(Path path, Size size)
    {
        if (std::filesystem::exists(path))
        {
            auto image = wxImage(path.string());
            auto resized = wxBitmap(image.Scale(size.GetWidth(), size.GetHeight()));
            return resized;
        }

        return wxBitmap();
    }
}