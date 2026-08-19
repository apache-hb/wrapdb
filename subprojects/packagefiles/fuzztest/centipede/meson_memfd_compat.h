#pragma once

#include <linux/memfd.h>
#include <sys/syscall.h>
#include <unistd.h>

static inline int meson_memfd_create(const char *name, unsigned int flags) {
  return static_cast<int>(syscall(SYS_memfd_create, name, flags));
}

#define memfd_create meson_memfd_create
