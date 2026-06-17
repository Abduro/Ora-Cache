the query to Google AI: how often mouse notification can be received by a window procedure WinAPI?

AI Overview

In the Windows API, a standard window procedure (WindowProc) receives standard mouse movement messages (WM_MOUSEMOVE) at a rate matching your display's refresh rate (typically 60Hz to 144Hz+), 
or less if the application is busy.
url: https://www.daniweb.com/programming/software-development/threads/183200/generating-window-procedure-mouse-wparam-from-hooks ;

The mechanics behind how often mouse notifications are delivered depend entirely on the type of event and how your message queue processes them.

(1) Mouse Movement (WM_MOUSEMOVE)

Dynamic Generation:
The Windows OS does not flood the message queue with millions of movement updates.
Instead, WM_MOUSEMOVE is treated as a low-priority, synthesized message, similar to WM_PAINT or WM_TIMER.

Coalescing:
As the physical mouse moves, the OS stores the updated position data.
It will only generate a single WM_MOUSEMOVE message inside the thread's message queue when the queue is completely empty of higher-priority events.

Frequency Limit:
Because Windows synthesizes these messages to keep the UI smooth, it caps the delivery rate to match the monitor's vertical sync/refresh rate (e.g., 60 times per second for 60Hz, 144 times per second for 144Hz).

(2) Mouse Clicks (WM_LBUTTONDOWN, WM_RBUTTONUP, etc.)

Strict Delivery: Unlike movement notifications, mouse clicks are never coalesced or dropped.
Frequency Limit: Every single click or button release triggers its own discrete message.
The notification frequency is purely limited by how fast a user can physically click or by simulated software input.

(3) Overcoming the Refresh Rate Limit

If you are building an application that requires high-precision or sub-millisecond mouse data—such as a competitive video game or digital art software,
relying on WM_MOUSEMOVE is insufficient because your high-polling-rate gaming mouse (e.g., 1000Hz to 8000Hz) is being throttled by the window message system.
You can bypass this limitation in two ways:

GetMouseMovePointsEx:
This Win32 function allows you to retrieve a history of up to 64 physical mouse coordinates that occurred between your WM_MOUSEMOVE screen updates,
preserving the high polling rate tracking of the hardware.
url: https://learn.microsoft.com/en-us/windows/win32/inputdev/mouse-input ;
url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmousemovepointsex ;

Raw Input API (WM_INPUT):
By registering your window to receive Raw Input via RegisterRawInputDevices, you tell the OS to send unthrottled, raw data packets directly from the mouse driver.
Through WM_INPUT, your window procedure can receive notifications at the maximum physical rate of the mouse hardware (e.g., up to 1000Hz to 8000Hz),
entirely separate from the display's refresh rate.
url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerrawinputdevices ;

AI Overview

The RegisterRawInputDevices WinAPI function allows applications to receive raw, unfiltered, and high-frequency input directly from hardware devices like mice, keyboards, and gamepads.
By default, Windows does not send raw input; you must explicitly register the device classes your application intends to track.
url: https://ph3at.github.io/posts/Windows-Input/ ;

It is just an example of the code:

RAWINPUTDEVICE Rid;
Rid.usUsagePage = 0x01; // Generic desktop controls
Rid.usUsage = 0x02;     // Mouse
Rid.dwFlags = 0;        // Default: receives raw input when focused
Rid.hwndTarget = hWnd;  // Your window handle

if (!RegisterRawInputDevices(&Rid, 1, sizeof(RAWINPUTDEVICE))) {
    // Registration failed, call GetLastError() to debug
    DWORD error = GetLastError();
}

Key Considerations

Reading the Input:
Once registered, your window procedure (WindowProc) will receive WM_INPUT messages.
You can retrieve the data inside it using GetRawInputData or optimize it with GetRawInputBuffer.

Preventing Legacy Inputs:
Using the RIDEV_NOLEGACY flag in the device structure stops Windows from processing default mouse or keyboard messages (e.g., WM_LBUTTONDOWN or WM_KEYDOWN),
making it perfect for custom game controls.

Unregistering:
To stop listening to a device, pass the RIDEV_REMOVE flag and set hwndTarget to NULL in your RAWINPUTDEVICE struct.
url: https://stackoverflow.com/questions/5313743/winapi-unregister-rawinputdevice ;

and finally:
url: https://stackoverflow.com/questions/19102189/noticable-lag-in-a-simple-opengl-program-with-mouse-input-through-glfw << good descussion;
url: https://github.com/glfw/glfw/pull/1406 ;

