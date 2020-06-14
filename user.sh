if [ -z ${SUDO_USER} ]
then
	echo ${USER} >> lightdm-gtk-backgroundmatch.conf
else
	echo ${SUDO_USER} >> lightdm-gtk-backgroundmatch.conf
fi
