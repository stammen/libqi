@echo off

set "UWP-DEPS=%cd%/uwp-deps"
rem convert all \ to / in UWP-DEPS path
set "UWP-DEPS=%UWP-DEPS:\=/%"
echo %UWP-DEPS%

echo cleaning build-libqi directories...
if exist build-libqi (
  rm -rf build-libqi
)

mkdir build-libqi
pushd build-libqi
  call cmake -G"Visual Studio 14 2015" -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0 ../ -Dqibuild_DIR="D:/GitHub/qibuild/cmake/qibuild" -DBOOST_ROOT="%UWP-DEPS%/boost-1.60.0" -DQI_WITH_TESTS=OFF -DBUILD_EXAMPLES=OFF -DWITH_BOOST_LOCALE=OFF -DOPENSSL_ROOT_DIR="%UWP-DEPS%/vcpkg/installed/x86-uwp"
	call "%VS140COMNTOOLS%vsvars32.bat"
	msbuild INSTALL.vcxproj /p:Configuration="Release" /p:Platform="Win32" /m  
popd

echo libqi build complete.
