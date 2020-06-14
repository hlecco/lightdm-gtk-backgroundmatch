# lightdm-gtk-backgroundmatch
A simple tool for matching ligthdm-gtk-greeter background to xfce4 background

Gets the last set xfce4 wallpaper for workspace 1 and set as lightdm-gtk-greeter wallpaper.
Files managed are ~/.config/xfce4/xfconf/xfce-perchannel-xml/xfce-desktop.xml and /etc/lightdm/lightdm-gtk-greeter.conf

After installing the package, please $ systemctl enable lightdm-gtk-backgroundmatch
so it updates automatically.
