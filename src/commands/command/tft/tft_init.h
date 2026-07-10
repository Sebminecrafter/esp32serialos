#pragma once

#ifdef USE_TFT
extern void initTFT();
extern void clearTFT();
#else
inline void initTFT() {}
inline void clearTFT() {}
#endif
