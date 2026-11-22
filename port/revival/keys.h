// The keys of EfzRevival.ini's settings, pressed and held (EfzRevival.cpp's updateKeys
// and updateButtons): the keyboard, and the buttons of the controller P1's A is on (or
// P2's, when P1 plays on the keyboard). Read once a real frame, by main.cpp.
#ifndef EFZ_REVIVAL_KEYS_H
#define EFZ_REVIVAL_KEYS_H

namespace efz {
namespace revival {

void UpdateKeys();
// The key (config.h's: a DIK_ code or kButton + n) went down on this frame.
bool Pressed(int key);
bool Held(int key);
// Every key that went down on this frame, in order (keys, then buttons).
int PressedKeys(int* out, int max);

} // namespace revival
} // namespace efz

#endif
