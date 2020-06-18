# lightdm-gtk-backgroundmatch
A simple tool for matching ligthdm-gtk-greeter background to xfce4 background

Gets the last set xfce4 wallpaper for workspace 1 and set as lightdm-gtk-greeter wallpaper.
Files managed are ~/.config/xfce4/xfconf/xfce-perchannel-xml/xfce-desktop.xml and /etc/lightdm/lightdm-gtk-greeter.conf

Running the binary will set the lightdm-gtk-greeter wallpaper as the current xfce wallpaper.
To do it automatically, go to Session and Startup > Application Autostart and add lightdm-gtk-backgroundmatch. Set the trigger to "on logout". Then, enable the service:
$ systemctl enable lightdm-gtk-backgroundmatch
