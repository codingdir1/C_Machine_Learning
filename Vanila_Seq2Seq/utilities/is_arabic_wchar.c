#include "include.h"

int is_arabic_wchar(wchar_t ch) {
    if ((ch >= 0x0600 && ch <= 0x06FF) ||  // Core Arabic Block
        (ch >= 0x0750 && ch <= 0x077F) ||  // Arabic Supplement
        (ch >= 0xFB50 && ch <= 0xFDFF) ||  // Presentation Forms-A
        (ch >= 0xFE70 && ch <= 0xFEFF))   // Presentation Forms-B
    {
        return 1;
    }
    return 0;
}
