# Maintainer: saswata <saswatabhunia10@gmail.com>

pkgname=kayos-maintainer
pkgver=1.0
pkgrel=1
pkgdesc="Maintanance application for KayOS"
arch=('any')
url="https://gitlab.com/garuda-linux/applications/garuda-welcome"
license=('GPL3')
depends=('qt5-base' 'xdg-utils' 'alacritty')
optdepends=( 'xorg-xrandr' 'xorg-xinput' 'garuda-assistant' 'garuda-network-assistant' 'qwikaccess' 'garuda-gamer' 'garuda-boot-options')
makedepends=('git')
source=("$pkgname-$pkgver.tar.gz::$url/-/archive/$pkgver/$pkgname-$pkgver.tar.gz")
md5sums=('SKIP')

build() {
	cd "$srcdir/$pkgname-$pkgver"
	qmake-qt5 $pkgname.pro
	make
}

package() {
	cd "$srcdir/$pkgname-$pkgver"
	make INSTALL_ROOT=$pkgdir install
}
