@echo off

set ROOT_DIR=%cd%

echo cleaning Boost directories...
if exist boost-1.60.0 (
  rm -rf boost-1.60.0
)

if exist boost-build (
  rm -rf boost-build
)

mkdir boost-1.60.0
mkdir boost-build
pushd boost-build
  git clone https://github.com/boostorg/boost.git
  pushd boost
    git checkout boost-1.60.0
    git submodule update --init
    pushd boost
      git checkout boost-1.60.0
      pushd libs
        pushd filesystem
          git remote add winrt https://github.com/stammen/filesystem.git
          git fetch winrt winrt-1.60.0
          git checkout winrt-1.60.0
        popd
        pushd thread 
          git remote add winrt https://github.com/stammen/thread.git
          git fetch winrt winrt-1.60.0
          git checkout winrt-1.60.0
        popd
        pushd uuid 
          git remote add winrt https://github.com/stammen/uuid.git
          git fetch winrt winrt-1.60.0
          git checkout winrt-1.60.0
        popd
        pushd program_options  
          git remote add winrt https://github.com/stammen/program_options .git
          git fetch winrt winrt-1.60.0
          git checkout winrt-1.60.0
        popd
      popd
      pushd tools
        pushd build
          git remote add winrt https://github.com/stammen/build.git
          git fetch winrt winrt-1.60.0
          git checkout winrt-1.60.0        
        popd
      popd
      call Bootstrap
      call b2 headers
      call b2 install --prefix=../../boost-1.60.0 --with-chrono --with-filesystem --with-date_time --with-atomic --with-thread --with-system --with-regex --with-atomic --with-program_options toolset=msvc-14.0 windows-api=store link=shared --variant=release
    popd
  popd
echo Boost 1.60.0 installed
popd