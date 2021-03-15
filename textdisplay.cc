#include "textdisplay.h"
#include "info.h"
#include "subject.h"

TextDisplay::TextDisplay(size_t n) {
    theDisplay.resize(n, std::vector<char>(n, '_')); 
    size = n;
}

std::ostream& operator<<(std::ostream& out, const TextDisplay& td) {
    for (size_t i = 0; i < td.size; ++i) {
        for (size_t j = 0; j < td.size; ++j) {
            out << td.theDisplay[i][j];
        }
        out << std::endl;
    }
    return out;
}

void TextDisplay::notify(Subject& whoNotified) {
    Info i = whoNotified.getInfo();
    if (i.state == State::Alive) theDisplay[i.row][i.col] = AliveChar; 
    else theDisplay[i.row][i.col] = DeadChar;
}