// fs.ts
import { extname, join } from "@tauri-apps/api/path";
import { open } from "@tauri-apps/plugin-dialog";
import { readDir, readTextFile, type DirEntry } from "@tauri-apps/plugin-fs";
import type { EditorView } from "codemirror";
import { writable, type Writable, get } from "svelte/store";
import { addTab } from "../components/EditorPanel/editor_tabs-utils";

export interface DirEntriesWithPathAndExt extends DirEntry {
    path: string;
    ext: string;
}

export const currentFolderItems: Writable<DirEntriesWithPathAndExt[]> = writable([]);

export async function loadFolder(folderPath: string) {
    if (!folderPath) {
        console.log("User cancelled the folder selection.");
        return;
    }

    try {
        const results = await readDir(folderPath);

        const folderEntries = await Promise.all(
            results.map(async (entry) => {
                const fullPath = await join(folderPath, entry.name);
                const extName = await extname(fullPath);
                return {
                    ...entry,
                    path: fullPath,
                    ext: extName
                };
            }),
        );
        currentFolderItems.set(
            folderEntries.sort((a: DirEntriesWithPathAndExt, b: DirEntriesWithPathAndExt) => {
                if (a.isDirectory && !b.isDirectory) {
                    return -1;
                } else if (!a.isDirectory && b.isDirectory) {
                    return 1;
                } else return a.name.localeCompare(b.name);
            }),
        );
        console.log("Folder Items List: ", folderEntries);
    } catch (error) {
        console.error("Error reading directory:", error);
    }
}

export const editorViewStore: Writable<EditorView | null> = writable(null);

export async function loadFile(filePath: string) {
    if (!filePath) {
        console.log("User cancelled reading the file");
        return;
    }

    try {
        addTab(filePath);
    } catch (error) {
        console.error("Error reading file", error);
    }
}