// Copyright: 2023 Jakub Korytko

#ifndef SRC_PCH_SOURCE_STDAFX_H_
#define SRC_PCH_SOURCE_STDAFX_H_

// must be included first
#include "src/pch_source/targetver.h"

#include <crtdbg.h>  // NOLINT(build/include_order)
#include <stdio.h>  // NOLINT(build/include_order)
#include <stdlib.h>  // NOLINT(build/include_order)
#include <tchar.h>  // NOLINT(build/include_order)

// modules that are used across the files,
// should be reachable from everywhere
#include "src/stack/data_types.h"
#include "src/interface/my_messages.h"
#include "src/stack/function_pointers.h"
#include "src/interface/errors_handler.h"

#endif  // SRC_PCH_SOURCE_STDAFX_H_
