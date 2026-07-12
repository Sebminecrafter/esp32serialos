#include "fs/fsrouter.h"
#include <LittleFS.h>
#include <SD.h>
#include <SPI.h>
#include "config.h"
#include "utilities/utilities.h"

FsMount mounts[] = {
    {"/flash", &LittleFS, false, false},
    {"/sd", &SD, true, false},
};
uint8_t mountCount = sizeof(mounts) / sizeof(mounts[0]);

void initFilesystems()
{
    // --- /flash : LittleFS image built into firmware, read-only ---
    // `false` = do NOT format on mount failure. This is deliberate:
    // we never want a boot-time failure to silently erase flash.
    // If this fails, the image just hasn't been uploaded yet -- run
    // `pio run -t uploadfs` to write the contents of ./data.
    if (LittleFS.begin(false))
    {
        mounts[0].mounted = true;
    }
    else
    {
        mounts[0].mounted = false;
        println("[fs] /flash: no LittleFS image found (run 'pio run -t uploadfs')");
    }

    // --- /sd : external card, read/write, optional ---
#ifdef SD_CS_PIN
    if (SD.begin(SD_CS_PIN))
    {
        mounts[1].mounted = true;
    }
    else
    {
        mounts[1].mounted = false;
        println("[fs] /sd: no card detected");
    }
#else
    mounts[1].mounted = false;
#endif
}

bool resolvePath(const String &path, fs::FS **outFs, String *outRelPath, bool *outWritable)
{
    for (uint8_t i = 0; i < mountCount; i++)
    {
        String prefix = mounts[i].prefix;
        bool matches = path.equals(prefix) || path.startsWith(prefix + "/");
        if (!matches)
            continue;

        if (!mounts[i].mounted)
            return false;

        String rel = path.substring(prefix.length());
        if (rel.length() == 0)
            rel = "/";

        *outFs = mounts[i].fs;
        *outRelPath = rel;
        *outWritable = mounts[i].writable;
        return true;
    }
    return false;
}

void listMounts()
{
    for (uint8_t i = 0; i < mountCount; i++)
    {
        print(mounts[i].prefix);
        print(" - ");
        print(mounts[i].mounted ? "mounted" : "not mounted");
        println(mounts[i].writable ? " (rw)" : " (ro)");
    }
}
