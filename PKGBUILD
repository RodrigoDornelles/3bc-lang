# Maintainer: yxqsnz <yxqsnz@gmail.com>
# Maintainer: Rodrigo Dornelles <rodrigo@dornelles.me> 
pkgname="3bc-git"
pkgver="0.1.1"
license=('GPL3')
pkgrel=1
pkgdesc="Low level language, tiny virtual machine that works on computers and microcontrollers. (Friendly Punched cards)"
source=("3bc::git+https://github.com/RodrigoDornelles/3bc-lang.git#branch=master")
makedepends=(gcc)
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64')
md5sums=("SKIP")

build() {
  cd "${srcdir}/3bc"
  gcc -o 3bc -O2 -lm main.c 
}
package() {
   cd "${srcdir}/3bc" 
   install -Dm755 3bc "${pkgdir}/usr/bin/3bc"
}
