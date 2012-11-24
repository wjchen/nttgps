#!/sbin/busybox sh

insmod /data/local/tmp/nttgps.ko
sleep 5
chown root.system /sys/class/sec/gps/GPS_PWR_EN/value
chmod 664 /sys/class/sec/gps/GPS_PWR_EN/value


