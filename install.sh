#!/bin/bash

OS=$(uname)
ARCH=$(uname -m)

LLVM_VERSION=20.1.0

if [[ $OS == "Darwin" ]]; then
  if [[ $ARCH == "x86_64" ]]; then
    TAR_NAME="LLVM-${LLVM_VERSION}-macOS-X64"
  elif [[ $ARCH == "arm64" ]]; then
    TAR_NAME="LLVM-${LLVM_VERSION}-macOS-ARM64"
  fi
elif [[ $OS == "Linux" ]]; then
  if [[ $ARCH == "x86_64" ]]; then
    TAR_NAME="LLVM-${LLVM_VERSION}-Linux-X64"
  fi
fi 

if [[ -z "$TAR_NAME" ]]; then
  echo "Cannot identify the file name :("
  exit
fi

if [[ ! -f "$TAR_NAME.tar.xz" ]]; then
  echo "Download $TAR_NAME from the official LLVM repository..."
  wget "https://github.com/llvm/llvm-project/releases/download/llvmorg-${LLVM_VERSION}/${TAR_NAME}.tar.xz"
fi


if [[ ! -d "llvm" ]]; then
  echo "Extract $TAR_NAME.tar.xz..."
  tar xf "${TAR_NAME}.tar.xz"
  mv "${TAR_NAME}" llvm
fi

BIN_PATH="$(pwd)/llvm/bin"
EXPORT_PATH="export PATH=\"$BIN_PATH:\$PATH\""

if ! grep -Fxq "$EXPORT_PATH" ~/.bashrc; then
  echo "Updating ~/.bashrc to include $BIN_PATH in PATH..."
  echo $EXPORT_PATH >> ~/.bashrc
else
  echo "$BIN_PATH is already in PATH in ~/.bashrc"
fi

LIB_PATH="$(pwd)/llvm/lib"
STDLIB_PATH="$(pwd)/llvm/lib/x86_64-unknown-linux-gnu"

EXPORT_LIB="export LD_LIBRARY_PATH=\"$LIB_PATH:$STDLIB_PATH:\$LD_LIBRARY_PATH\""

if ! grep -Fxq "$EXPORT_LIB" ~/.bashrc; then
  echo "Updating ~/.bashrc to include $LIB_PATH in LD_LIBRARY_PATH..."
  echo $EXPORT_LIB >> ~/.bashrc
else
  echo "$LIB_PATH is already in LD_LIBRARY_PATH in ~/.bashrc"
fi

echo "LLVM is successfully installed!"
