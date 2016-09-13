# 4x4 USB Keyboard with Arduino

This is the repository for the 4x4 USB Keyboard using Arduino. I have developed a 3D printed enclosure that fits the keys and an Arduino Pro micro that you can check here: http://www.thingiverse.com/thing:1735255

The macros were chosen to aid my wife when she is using her Wacom tablet to draw, but needs a few shortcuts at hand. But if you need different macros, simply modify the pressMacro and releaseMacro functions accordingly.

This sketch requires NicoHood's excellent HID library, because I make use of media keys for some macros, but if those are not needed, you could use the Arduino's built-in HID keyboard library.

This code is based on this tutorial: https://learn.sparkfun.com/tutorials/cherry-mx-switch-breakout-hookup-guide
From what I understand, the tutorials are released as CC BY-NC-SA 3.0, which then are compatible with CC BY-NC-SA 4.0, which are compatible with GPLv3 (which is my preferred license). I have contacted Sparkfun on this issue and am waiting for a response.
