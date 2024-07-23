#pragma once

#ifdef NDEBUG
#define IN_RELEASE true
#define IN_DEBUG false
#else
#define IN_DEBUG true
#define IN_RELEASE false
#endif // NDEBUG