#!/usr/bin/env bash
#启动docker容器的bash脚本；
MONITOR_HOME_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

display=""
if [ -z ${DISPLAY} ];then
    display=":1"
else
    display="${DISPLAY}"
fi

# 判断是否在 WSL 中
is_wsl=false
if [ -n "$WSL_DISTRO_NAME" ]; then
    is_wsl=true
fi

local_host="$(hostname)"
user="${USER}"
uid="$(id -u)"
group="$(id -g -n)"
gid="$(id -g)"


echo "stop and rm docker" 
docker stop linux_monitor > /dev/null 2>&1
docker rm -v -f linux_monitor > /dev/null 2>&1

echo "start docker"
docker run -it -d \
--name linux_monitor \
-e DISPLAY=$display \
--privileged=true \
-e DOCKER_USER="${user}" \
-e USER="${user}" \
-e DOCKER_USER_ID="${uid}" \
-e DOCKER_GRP="${group}" \
-e DOCKER_GRP_ID="${gid}" \
-e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
-e WAYLAND_DISPLAY=$WAYLAND_DISPLAY \
-e PULSE_SERVER=$PULSE_SERVER \
$(if [ "$is_wsl" = true ]; then echo "-v /mnt/wslg:/mnt/wslg -v /mnt/wslg/.X11-unix:/tmp/.X11-unix"; fi) \
-v ${MONITOR_HOME_DIR}:/work \
-v ${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR} \
--net host \
linux:monitor
