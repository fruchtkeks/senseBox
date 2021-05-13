#!/bin/bash

case "$1" in

  start)
    /opt/senseBox/senseBox /opt/senseBox/box.config >/dev/null 2>&1 &
    echo "senseBox started"
  ;;

  stop)
    sudo killall senseBox
    echo "senseBox stopped"
  ;;

  *)
    echo "(start|stop)"
    exit 1
  ;;

esac

exit 0