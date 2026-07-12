#pragma once
#include <Arduino.h>
#include <FS.h>

// A single mount point: a path prefix backed by a concrete fs::FS
// (LittleFS, SD, etc). Both LittleFS and SD already implement fs::FS
// in the ESP32 Arduino core, so this struct is the entire abstraction
// layer -- no custom IFileSystem needed.
struct FsMount
{
    const char *prefix; // e.g. "/flash", "/sd"
    fs::FS *fs;          // backing filesystem instance
    bool writable;        // false = mounted/treated as read-only
    bool mounted;          // set at runtime by initFilesystems()
};

extern FsMount mounts[];
extern uint8_t mountCount;

// Mounts /flash (LittleFS, read-only) and /sd (SD card, read/write if present).
// Safe to call even if a backend fails/is absent -- it just stays unmounted.
void initFilesystems();

// Resolves a routed path like "/sd/docs/help.txt" into:
//   outFs        -> the fs::FS* to use ("SD" or "LittleFS")
//   outRelPath   -> the path relative to that FS ("/docs/help.txt")
//   outWritable  -> whether writes are allowed on this mount
// Returns false if the prefix doesn't match any mount, or the mount
// isn't currently available.
bool resolvePath(const String &path, fs::FS **outFs, String *outRelPath, bool *outWritable);

// Prints mount status (used by the `mounts` command).
void listMounts();
