#!/usr/bin/env bash

function req {
   wget -qo- -O - "$1" 2>/dev/null || curl -fsSL "$1"
}
function get_release() {
  req https://api.github.com/repos/rodrigodornelles/3bc-lang/releases/latest -s | grep "tag_name" | sed 's/[^0-9.]*//g'
}
function get_arch {
  case $(uname -m) in
    x86_64)
      echo "x86_64"
      ;;
    i*86)
      echo "i386"
      ;;
    *)
      echo "x86_64"
      ;;
  esac
}
function get_os() {
  case $(uname) in
    Darwin)
      echo "macos"
      ;;
    Linux)
      echo "linux"
      ;;
  esac
}

function main {
  RELEASE=$(get_release)
  echo "info: installing release ${RELEASE}"
  DOWNLOAD_URL="https://github.com/RodrigoDornelles/3bc-lang/releases/download/${RELEASE}/$(get_os)-$(get_arch)-interpreter-3bc.tar.gz"
  echo "info: downloading ${DOWNLOAD_URL}"
  req "${DOWNLOAD_URL}" | tar -xz -C /usr/local/bin
  chmod +x /usr/local/bin/3bc
  echo "info: 3bc is now installed, great!"
}
# check if user is root
if [ "$(id -u)" != "0" ]; then
   echo "error: this script must be run as root" 1>&2
   exit 1
fi
main


