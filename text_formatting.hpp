#pragma once
#include <QTextCursor>

class TextFormatting {
public:
    static inline void setLineHeight(QTextCursor& cursor, int textSize, int lineHeight = 0) {
        auto blockFormat = cursor.blockFormat();
        blockFormat.setLineHeight(textSize + lineHeight, QTextBlockFormat::LineHeightTypes::FixedHeight);
        cursor.setBlockFormat(blockFormat);
    }
};
