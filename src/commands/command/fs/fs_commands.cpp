#include "commands/command/fs/fs_commands.h"
#include "fs/fsrouter.h"
#include "utilities/utilities.h"

// Defaults to /flash so a bare `ls` / `cat` still does something useful.
static String normalizePath(String path)
{
    path.trim();
    if (path.length() == 0)
        path = "/flash";
    if (!path.startsWith("/"))
        path = "/" + path;
    return path;
}

void cmdLs(String arguments)
{
    String path = normalizePath(arguments);
    fs::FS *targetFs;
    String rel;
    bool writable;

    if (!resolvePath(path, &targetFs, &rel, &writable))
    {
        println("ls: cannot access '" + path + "': no such mount, or mount not available");
        return;
    }

    File dir = targetFs->open(rel);
    if (!dir || !dir.isDirectory())
    {
        println("ls: '" + path + "': not a directory");
        return;
    }

    File entry = dir.openNextFile();
    while (entry)
    {
        print(entry.isDirectory() ? "[DIR]  " : "       ");
        print(String(entry.name()));
        if (!entry.isDirectory())
        {
            print("  (");
            print(String((unsigned long)entry.size()));
            print(" bytes)");
        }
        println();
        entry = dir.openNextFile();
    }
}

void cmdCat(String arguments)
{
    String path = normalizePath(arguments);
    fs::FS *targetFs;
    String rel;
    bool writable;

    if (!resolvePath(path, &targetFs, &rel, &writable))
    {
        println("cat: cannot access '" + path + "': no such mount, or mount not available");
        return;
    }

    File f = targetFs->open(rel);
    if (!f || f.isDirectory())
    {
        println("cat: '" + path + "': no such file");
        return;
    }

    while (f.available())
    {
        print((char)f.read());
    }
    println();
    f.close();
}

void cmdMounts(String arguments)
{
    listMounts();
}
