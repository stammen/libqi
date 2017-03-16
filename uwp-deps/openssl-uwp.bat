@echo off

if exist vcpkg (
  rm -rf vcpkg
)

echo Building and installing vcpkg...
git clone https://github.com/Microsoft/vcpkg.git
pushd vcpkg
  echo A | powershell -exec bypass scripts\bootstrap.ps1
  echo Building and installing openssl:uwp-86
  vcpkg install openssl:x86-uwp
popd
echo openssl:x86-uwp installed
