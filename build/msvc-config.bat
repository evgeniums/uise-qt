IF NOT DEFINED MSVC_ROOT SET MSVC_ROOT=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community
IF NOT DEFINED MSVC_NAME SET MSVC_NAME="Visual Studio 16 2019"
IF NOT DEFINED MSVC_COMPILER SET MSVC_COMPILER=v142
IF NOT DEFINED MSVC_COMPILER_DOTTED SET MSVC_COMPILER_DOTTED=14.2

SET MSVCARGS=%MSVC_ROOT%\VC\Auxiliary\Build\vcvarsall.bat

SET MSVC_ARCH=x64
SET CMAKE_PLATFORM=x64
SET NAME_SUFFIX="_x64"
SET MSVC_TOOLSET="%MSVC_COMPILER%,host=x64"
SET MSVC_FULL_ARCH=x86_64
SET MSVC_BUILD_ARCH=x64

IF NOT DEFINED QT_HOME_MSVC SET QT_HOME_MSVC=C:\Qt\6.0.1\msvc2019_64
SET QT_HOME=%QT_HOME_MSVC%

SET BOOST_ROOT=%DEPS_UNIVERSAL_ROOT%\root-msvc-14.2-x86_64
SET TOOLCHAIN=msvc
